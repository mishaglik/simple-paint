#ifndef WIDGETS_COLLAPSIBLECONTAINER_HPP
#define WIDGETS_COLLAPSIBLECONTAINER_HPP

#include <Widgets/ContainerWidget.hpp>

namespace aGL {
    class CollapsibleContainer : public ContainerWidget
    {
    public:
        CollapsibleContainer(const Rect& rect, uint32_t colH, Widget* parent = nullptr)
            : ContainerWidget(rect, parent), maxH_(rect.h), colH_(colH)
        {
            resize(rect.w, colH_);
        }

        Signal<bool> collapsedChanged;

        virtual EventHandlerState onPaintEvent(const Event* e) override
        {
            if(skinned())
            {
                surface->clear(aGL::Colors::Gray);
                surface->drawSprite({}, Sprite(sm_->getTexture(texId_), {0, focused_ ? colH_ : 0, rect_.w, rect_.h}));
            }
            return ContainerWidget::onPaintEvent(e);
        }
        virtual EventHandlerState onGainFocusEvent(const Event* e) override
        {
            resize(rect_.w, maxH_);
            collapsedChanged.emit(true);
            return ContainerWidget::onGainFocusEvent(e);
        }

        virtual EventHandlerState onLoseFocusEvent(const Event* e) override
        {
            resize(rect_.w, colH_);
            collapsedChanged.emit(false);
            return ContainerWidget::onLoseFocusEvent(e);
        }
        
        virtual EventHandlerState onMouseButtonPressEvent(const Event* e) override 
        { 
            EventHandlerState res = ContainerWidget::onMouseButtonPressEvent(e);
            return (e->mbed.button == MouseButton::Left) ? Accepted : res;
        }

    private:
        uint32_t maxH_, colH_;
    };
}

#endif /* WIDGETS_COLLAPSIBLECONTAINER_HPP */
