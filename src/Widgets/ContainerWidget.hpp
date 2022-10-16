#ifndef WIDGETS_CONTAINERWIDGET_HPP
#define WIDGETS_CONTAINERWIDGET_HPP
#include <Widgets/Widget.hpp>
#include <AbstractGL/EventManager.hpp>
namespace aGL {
    class ContainerWidget : public Widget
    {
    protected:
        EventManager emanager_;
    public:
        ContainerWidget() : Widget(), emanager_() {}
        ContainerWidget(const Rect& rect) : Widget(rect), emanager_(rect.getCornerLL()) {}
        ContainerWidget(const Rect& rect, RenderSurface* surf) : Widget(rect, surf), emanager_(rect.getCornerLL()) {}


        virtual EventHandlerState handleEvent               (const Event* event) override { return emanager_.handleEvent(const_cast<Event*>(event));}
        virtual EventHandlerState onPaintEvent              (const Event* event) override { return emanager_.handleEvent(const_cast<Event*>(event));}
        virtual EventHandlerState onKeyPressedEvent         (const Event* event) override { return emanager_.handleEvent(const_cast<Event*>(event));}
        virtual EventHandlerState onKeyReleasedEvent        (const Event* event) override { return emanager_.handleEvent(const_cast<Event*>(event));}
        virtual EventHandlerState onShortcutEvent           (const Event* event) override { return emanager_.handleEvent(const_cast<Event*>(event));}
        virtual EventHandlerState onMouseMoveEvent          (const Event* event) override { return emanager_.handleEvent(const_cast<Event*>(event));}
        virtual EventHandlerState onMouseLeaveEvent         (const Event* event) override { return emanager_.handleEvent(const_cast<Event*>(event));}
        virtual EventHandlerState onMouseButtonPressEvent   (const Event* event) override { return emanager_.handleEvent(const_cast<Event*>(event));}
        virtual EventHandlerState onMouseButtonReleaseEvent (const Event* event) override { return emanager_.handleEvent(const_cast<Event*>(event));}
        virtual EventHandlerState onMouseScrollEvent        (const Event* event) override { return emanager_.handleEvent(const_cast<Event*>(event));}
        virtual EventHandlerState onTimerEvent              (const Event* event) override { update(); return emanager_.handleEvent(const_cast<Event*>(event));}

        bool subscribe(Widget* object) { return emanager_.subscribe(object); }
    };
}

#endif /* WIDGETS_CONTAINERWIDGET_HPP */
