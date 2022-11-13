#include "ColorSelector.hpp"
#include "GEditor.hpp"
#include <Widgets/Decorations.hpp>
#include "ColorDialog/ColorDialog.hpp"
namespace mge {
    ColorSelector::ColorSelector(const aGL::Rect& rect, aGL::Widget* parent) :
        aGL::Widget(rect, parent)
    {
        uint32_t size = std::min(rect.w, rect.h);
        uint32_t subsize = size / 2 + size / 10;
        foreRect_ = {0, 0, subsize, subsize};
        backRect_ = {size - subsize, size - subsize, subsize, subsize};
        
        uint32_t miniSize = subsize / 2;
        uint32_t subminiSize = miniSize / 2 + miniSize / 10;

        foreMiniRect_ = {0, size - miniSize, subminiSize, subminiSize};
        backMiniRect_ = {miniSize - subminiSize, size - subminiSize, subminiSize, subminiSize};
        
        arrowRect_ = {subsize, 0, size - subsize, size - subsize};

    }

    aGL::EventHandlerState ColorSelector::onPaintEvent(const aGL::Event*)
    {
        surface->clear(0);
        DrawingContext& context = GEditor::app->context;
        const aGL::Color miniBorderColor = 0xbebebeff;

        surface->drawRect(backRect_, context.backgroundColor);
        aGL::DecRect(surface, backRect_).decorate(aGL::Decorations::dBorder, aGL::Colors::White, aGL::Colors::Black);

        surface->drawRect(foreRect_, context.foregroundColor);
        aGL::DecRect(surface, foreRect_).decorate(aGL::Decorations::dBorder, aGL::Colors::White, aGL::Colors::Black);

        surface->drawRect(backMiniRect_, aGL::Colors::White);
        aGL::DecRect(surface, backMiniRect_).decorate(aGL::Decorations::border, miniBorderColor);
        
        surface->drawRect(foreMiniRect_, aGL::Colors::Black);
        aGL::DecRect(surface, foreMiniRect_).decorate(aGL::Decorations::border, miniBorderColor);
        
        if(skinned()) surface->drawSprite(arrowRect_.getCornerLL(), sm_->getTexture(texId_));

        return aGL::Accepted;
    }

    aGL::EventHandlerState ColorSelector::onMouseButtonPressEvent(const aGL::Event* e) 
    {
        if(e->mbed.button != aGL::MouseButton::Left) return aGL::Dropped;
        
        if(mgm::contains(arrowRect_, e->mbed.point))
        {
            std::swap(GEditor::app->context.foregroundColor, GEditor::app->context.backgroundColor);
            return aGL::Accepted;
        }
        
        if(mgm::contains(foreRect_, e->mbed.point))
        {
            aGL::ColorDialog* dialog = new aGL::ColorDialog("Set Foreground color", GEditor::app->context.foregroundColor);
            dialog->aGL::Window::show();
            dialog->finished.connect(GEditor::app, &GEditor::setFgColor);
            return aGL::Accepted;
        }
        
        if(mgm::contains(backRect_, e->mbed.point))
        {
            aGL::ColorDialog* dialog = new aGL::ColorDialog("Set Background color", GEditor::app->context.backgroundColor);
            dialog->aGL::Window::show();
            dialog->finished.connect(GEditor::app, &GEditor::setBgColor);
            return aGL::Accepted;
        }

        GEditor::app->context.backgroundColor = aGL::Colors::White;
        GEditor::app->context.foregroundColor = aGL::Colors::Black;

        return aGL::Accepted;
    }

}
