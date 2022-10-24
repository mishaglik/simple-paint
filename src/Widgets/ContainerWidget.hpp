#ifndef WIDGETS_CONTAINERWIDGET_HPP
#define WIDGETS_CONTAINERWIDGET_HPP
#include <Widgets/Widget.hpp>
#include <AbstractGL/EventManager.hpp>
namespace aGL {
    class ContainerWidget : public Widget
    {
    protected:
        EventManager emanager_;
        EventManager* parEvManager_ = nullptr;
    public:
        explicit ContainerWidget(Widget* parent) : Widget(parent), emanager_() { parEvManager_ = evMgr_; evMgr_ = &emanager_; }
        explicit ContainerWidget(const Rect& rect, Widget* parent = nullptr) : Widget(rect, parent), emanager_(rect.getCornerLL()) { parEvManager_ = evMgr_; evMgr_ = &emanager_; }
        ContainerWidget(const Rect& rect, RenderSurface* surf, Widget* parent = nullptr) : Widget(rect, surf, parent), emanager_(rect.getCornerLL()) { parEvManager_ = evMgr_; evMgr_ = &emanager_; }


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

        virtual ContainerWidget& setEventManager(EventManager* em) override 
        {
            if(parEvManager_)
            {
                MLG_UIMPLEMENTED //TODO: Implement
                return *this;
            }
            parEvManager_ = em;
            if(em)
                em->subscribe(this);
            return *this;
        }

    };
}

#endif /* WIDGETS_CONTAINERWIDGET_HPP */
