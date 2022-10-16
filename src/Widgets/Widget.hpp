#ifndef WIDGETS_WIDGET_HPP
#define WIDGETS_WIDGET_HPP
#include <AbstractGL/AWindow.hpp>

namespace aGL {

    class Widget : public AObject 
    {
    private:
        bool hidden_ = false;
    protected:
        using Timepoint = Event::Timepoint;
        bool focused_ = false; 
        Rect rect_;
        Surface* surface;
        Timepoint time_;

    public:
        Widget() : rect_({0, 0, 100, 100}), surface(new RenderSurface(100, 100)) {}
        Widget(const Rect& rect) : rect_(rect), surface(new RenderSurface(rect.w, rect.h)) {}
        Widget(const Rect& rect, RenderSurface* surf) : rect_(rect), surface(surf) {}
        virtual ~Widget() {}

        virtual void render(const Window &window) const;
        virtual void render(const Window *window) const {render(*window);}
        virtual void render(const Surface *surface) const;

        virtual EventHandlerState handleEvent               (const Event*  ) { return EventHandlerState::Dropped;}
        virtual EventHandlerState onPaintEvent              (const Event*  ) { return EventHandlerState::Accepted;}
        virtual EventHandlerState onKeyPressedEvent         (const Event*  ) { return EventHandlerState::Dropped;}
        virtual EventHandlerState onKeyReleasedEvent        (const Event*  ) { return EventHandlerState::Dropped;}
        virtual EventHandlerState onTextEnteredEvent        (const Event*  ) { return EventHandlerState::Dropped;}
        virtual EventHandlerState onShortcutEvent           (const Event*  ) { return EventHandlerState::Dropped;}
        virtual EventHandlerState onMouseMoveEvent          (const Event*  ) { return EventHandlerState::Dropped;}
        virtual EventHandlerState onMouseButtonPressEvent   (const Event* e) { if(e->mbed.button == aGL::MouseButton::Left) return EventHandlerState::Accepted; else return EventHandlerState::Dropped;}
        virtual EventHandlerState onMouseButtonReleaseEvent (const Event* e) { if(e->mbed.button == aGL::MouseButton::Left) return EventHandlerState::Accepted; else return EventHandlerState::Dropped;}
        virtual EventHandlerState onMouseScrollEvent        (const Event*  ) { return EventHandlerState::Dropped;}
        virtual EventHandlerState onMouseEnterEvent         (const Event*  ) { return EventHandlerState::Accepted;}
        virtual EventHandlerState onMouseLeaveEvent         (const Event*  ) { return EventHandlerState::Accepted;}
        virtual EventHandlerState onGainFocusEvent          (const Event*  ) { focused_ = true;  return EventHandlerState::Accepted;}
        virtual EventHandlerState onLoseFocusEvent          (const Event*  ) { focused_ = false; return EventHandlerState::Accepted;}
        virtual EventHandlerState onTimerEvent              (const Event* e) { time_ = e->time; update(); return EventHandlerState::Dropped;}
        
        virtual void update() {}
        virtual void resize(uint32_t w, uint32_t h);
        virtual void resize(const mgm::Vector2u& v);

        void show() { hidden_ = false; }
        void hide() { hidden_ = true; }
        bool isHidden() const { return hidden_; }
        
        const Rect& getRect() const {return rect_;}
        const Point getEventCorner() const { return rect_.getCornerLL(); }
        virtual bool hasEventPoint(const Point& pt) { return hidden_ ? false : mgm::contains(rect_, pt); }

    // Non-copyable declaration.
        Widget(const Widget&)            = delete;
        Widget& operator=(const Widget&) = delete;
    };

}

#endif /* WIDGETS_WIDGET_HPP */
