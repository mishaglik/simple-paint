#include "SFMLWindow.hpp"
#include "AWindow.hpp"
#include "SFMLText.hpp"
#include "SFMLRenderSurface.hpp"
#include "SFMLSprite.hpp"

#include <LogUtils/LogUtils.hpp>
#include <SFML/Graphics.hpp>
#include <cstdint>
#include <cassert>
#include <iostream>

namespace aGL {

    Window_::Window_(uint32_t width, uint32_t height, const char* title): sf::RenderWindow(sf::VideoMode(width, height), title) {}

    Window_::~Window_() {}

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------


    Window::Window(uint32_t width, uint32_t height, const char* title) :
        wp_(new Window_(width, height, title))
    {
        mAssert(wp_ != nullptr);
    }

    Window::~Window()
    {
        delete wp_;
        wp_ = nullptr;
    }

    void Window::resize(uint32_t width, uint32_t height)
    {
        wp_->setSize(sf::Vector2u(width, height));
    }

    void Window::show()
    {
        wp_->setVisible(true);
    }

    void Window::hide()
    {
        wp_->setVisible(false);
    }

    void Window::clear(Color color) const
    {
        wp_->clear(sf::Color(color));
    }

    void Window::drawText(const Text& text) const
    {
        wp_->draw(*text.tp_);
    }

    void Window::update() const
    {
        wp_->display();
    }

    void Window::drawLine(Point p1, Point p2, Color color) const
    {
        sf::Vertex lines[2] = {};
        lines[0].position = sf::Vector2f(static_cast<float>(p1.x), static_cast<float>(p1.y));
        lines[1].position = sf::Vector2f(static_cast<float>(p2.x), static_cast<float>(p2.y));

        lines[0].color = lines[1].color = sf::Color(color);

        wp_->draw(lines, 2, sf::Lines);
    }

    void Window::drawRect(const Rect& rect, Color color) const
    {
        sf::RectangleShape sfRect(sf::Vector2f(static_cast<float>(rect.w), static_cast<float>(rect.h)));
        sfRect.setPosition(static_cast<float>(rect.x), static_cast<float>(rect.y));
        sfRect.setFillColor(sf::Color(color));
        wp_->draw(sfRect);
    }
        
    void Window::drawPoint(Point p, Color color) const
    {
        sf::Vertex vertex({
            static_cast<float>(p.x),
            static_cast<float>(p.y)
            }, sf::Color(color));
        wp_->draw(&vertex, 1, sf::Points);
    }


    void Window::drawSurf(Point pt, const RenderSurface &surf) const
    {
        sf::Sprite sprite(surf.rsp_->getTexture());
            sprite.setOrigin(0, static_cast<float>(sprite.getTextureRect().height));
            sprite.setScale(1, -1);
            sprite.setPosition({
                static_cast<float>(pt.x),
                static_cast<float>(pt.y)
            });
            wp_->draw(sprite);
    }

    void Window::drawSurf(Point pt, const RenderSurface &surf, const Rect& rect) const
    {
        sf::Sprite sprite(surf.rsp_->getTexture());
            sprite.setTextureRect({
                    static_cast<int>(rect.x), 
                    static_cast<int>(rect.h/2 - rect.y), 
                    static_cast<int>(rect.w), 
                    static_cast<int>(rect.h)
                });
            sprite.setOrigin(0, static_cast<float>(rect.h));
            sprite.setScale(1, -1);
            sprite.setPosition({
                static_cast<float>(pt.x),
                static_cast<float>(pt.y)
            });
            wp_->draw(sprite);
    }

    static MouseButton getMouseButton(sf::Mouse::Button button)
    {
        switch (button) {

        case sf::Mouse::Left:
            return MouseButton::Left;
        case sf::Mouse::Right:
            return MouseButton::Right;
        case sf::Mouse::Middle:
            return MouseButton::Middle;
        case sf::Mouse::XButton1:
        case sf::Mouse::XButton2:
        case sf::Mouse::ButtonCount:
            return MouseButton::Other;
        }
        assert(0 && "Wrong switch");
    }


    bool Window::pollEvent(Event& event)
    {
        sf::Event sfEvent;
        if(wp_->pollEvent(sfEvent))
        {
            switch (sfEvent.type) {

            case sf::Event::KeyPressed:
                event.type = EventType::KeyPressed;
                event.ked = *reinterpret_cast<KeyEventData*>(&sfEvent.key); // I'm personally created very simmilar to SFML prototypes, so I've decided to make reinterperter cast.
                break;

            case sf::Event::KeyReleased:
                event.type = EventType::KeyReleased;
                event.ked = *reinterpret_cast<KeyEventData*>(&sfEvent.key);
                break;

            case sf::Event::Closed:
                event.type = EventType::Quited;
                break;
                
            case sf::Event::MouseWheelMoved:
                event.type = EventType::MouseWheeled;
                event.mwed.delta = sfEvent.mouseWheel.delta;
                event.mwed.point = {
                                    sfEvent.mouseWheel.x,
                                    sfEvent.mouseWheel.y
                                };
                break;

            case sf::Event::MouseButtonPressed:
                event.type = EventType::MouseButtonPressed;
                event.mbed.button = getMouseButton(sfEvent.mouseButton.button);
                event.mbed.point = {
                                    (sfEvent.mouseButton.x),
                                    (sfEvent.mouseButton.y)
                                };
                break;
            case sf::Event::MouseButtonReleased:
                event.type = EventType::MouseButtonReleased;
                event.mbed.button = getMouseButton(sfEvent.mouseButton.button);
                event.mbed.point = {
                                    (sfEvent.mouseButton.x),
                                    (sfEvent.mouseButton.y)
                                };
                break;
            case sf::Event::MouseMoved:
                event.type = EventType::MouseMoved;
                event.mmed.point = {
                                    (sfEvent.mouseMove.x),
                                    (sfEvent.mouseMove.y)
                                };
                break;
            case sf::Event::Resized:
            {
                sf::View view = wp_->getDefaultView();
                view.setSize({
                        static_cast<float>(sfEvent.size.width),
                        static_cast<float>(sfEvent.size.height)
                });
                view.reset(sf::FloatRect(0, 0, static_cast<float>(sfEvent.size.width), static_cast<float>(sfEvent.size.height)));
                wp_->setView(view);
            }
                return false; //TODO: Add resize event;
            case sf::Event::MouseWheelScrolled:
            case sf::Event::LostFocus:
            case sf::Event::GainedFocus:
            case sf::Event::TextEntered:
                event.type = EventType::TextEntered;
                event.text = sfEvent.text.unicode;
                break;
            case sf::Event::MouseEntered:
            case sf::Event::MouseLeft:
            case sf::Event::JoystickButtonPressed:
            case sf::Event::JoystickButtonReleased:
            case sf::Event::JoystickMoved:
            case sf::Event::JoystickConnected:
            case sf::Event::JoystickDisconnected:
            case sf::Event::TouchBegan:
            case sf::Event::TouchMoved:
            case sf::Event::TouchEnded:
            case sf::Event::SensorChanged:
            case sf::Event::Count:
                // event.type = EventType::Other;
                mDebug << "Other event: " << sfEvent.type << mlg::endl;
                return false; //TODO: Implement
            }
            return true;
        }
        return false;
    }

    void Window::drawSprite  (Point pt, const Sprite& sprite) const
    {
        sprite.sp_->move({
            static_cast<float>(pt.x),
            static_cast<float>(pt.y)
        });
        wp_->draw(*sprite.sp_);
        sprite.sp_->move({
            -static_cast<float>(pt.x),
            -static_cast<float>(pt.y)
        });
    }

    void Window::setActive(bool active) const
    {
        wp_->setActive(active);
    }

    aGL::Rect Window::getSurfRect() const 
    {
        sf::Vector2u v = wp_->getSize();
        return {0, 0, v.x, v.y};
    }

}
