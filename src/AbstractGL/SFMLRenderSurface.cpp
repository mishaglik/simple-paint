#include "SFMLRenderSurface.hpp"
#include "SFMLText.hpp"
#include "ARenderSurface.hpp"
#include "SFMLSprite.hpp"

namespace aGL {

    RenderSurface::RenderSurface(uint32_t w, uint32_t h)
    {
        rsp_ = new RenderSurface_(w, h);
    }

    RenderSurface::~RenderSurface()
    {
        delete rsp_;
    }

    void RenderSurface::drawText(const Text& text) const
    {
        rsp_->draw(*text.tp_);
    }

    void RenderSurface::drawLine(Point p1, Point p2, Color color) const
    {
        sf::Vertex lines[2] = {};
        lines[0].position = sf::Vector2f(static_cast<float>(p1.x), static_cast<float>(p1.y));
        lines[1].position = sf::Vector2f(static_cast<float>(p2.x), static_cast<float>(p2.y));

        lines[0].color = lines[1].color = sf::Color(color);

        rsp_->draw(lines, 2, sf::Lines);
    }

    void RenderSurface::drawPoint(Point p, Color color) const
    {
        sf::Vertex vertex({
            static_cast<float>(p.x),
            static_cast<float>(p.y)
            }, sf::Color(color));
        rsp_->draw(&vertex, 1, sf::Points);
    } 

    void RenderSurface::drawRect(const Rect& rect, Color color) const
    {
        sf::RectangleShape sfRect(sf::Vector2f(static_cast<float>(rect.w), static_cast<float>(rect.h)));
        sfRect.setPosition(static_cast<float>(rect.x), static_cast<float>(rect.y));
        sfRect.setFillColor(sf::Color(color));
        rsp_->draw(sfRect);
    }

    void RenderSurface::drawSurf(Point pt, const RenderSurface& surf) const
    {
        sf::Sprite sprite(surf.rsp_->getTexture());
        sprite.setPosition({
            static_cast<float>(pt.x),
            static_cast<float>(pt.y)
        });
        rsp_->draw(sprite);
    }

    void RenderSurface::drawSurf(Point pt, const RenderSurface& surf, const Rect& rect) const
    {
        sf::Sprite sprite(surf.rsp_->getTexture());
        sprite.setTextureRect({
                    static_cast<int>(rect.x), 
                    static_cast<int>(rect.y), 
                    static_cast<int>(rect.w), 
                    static_cast<int>(rect.h
                )});
        sprite.setPosition({
            static_cast<float>(pt.x),
            static_cast<float>(pt.y)
        });
        rsp_->draw(sprite);
    }

    void RenderSurface::clear(Color color) const 
    {
        rsp_->clear(sf::Color(color));
    }

    void RenderSurface::resize(uint32_t w, uint32_t h)
    {
        auto old = rsp_;
        rsp_ = new RenderSurface_(w, h);
        delete old;
    }

    void RenderSurface::drawSprite(Point pt, const Sprite& sprite) const
    {
        sf::Vector2f origin = sprite.sp_->getOrigin();
        sprite.sp_->setPosition({
            static_cast<float>(pt.x) + origin.x,
            static_cast<float>(pt.y) + origin.y,
        });
        rsp_->draw(*sprite.sp_);
        sprite.sp_->setPosition({0, 0});
    }

    const Texture& RenderSurface::getTexture() const //HACK: Need reference;
    {
        rsp_->display();
        return rsp_->texture;
    }

    void RenderSurface::update() const {
        rsp_->display();
    }
}
