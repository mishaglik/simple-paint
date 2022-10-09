#ifndef ABSTRACTGL_WIDGET_HPP
#define ABSTRACTGL_WIDGET_HPP
#include <AbstractGL/AWindow.hpp>

namespace aGL {

    class Widget : public AObject 
    {
    private:
    protected:
        Rect rect_;
        RenderSurface* surface;
    public:

        Widget() : rect_({0, 0, 100, 100}), surface(new RenderSurface(100, 100)) {}
        Widget(const Rect& rect) : rect_(rect), surface(new RenderSurface(rect.w, rect.h)) {}
        Widget(const Rect& rect, RenderSurface* surf) : rect_(rect), surface(surf) {}

        virtual void render(const Window &window) const;

        virtual EventHandlerState handleEvent               (const Event* ) override { return EventHandlerState::Dropped;}
        virtual EventHandlerState onPaintEvent              (const Event* ) { return EventHandlerState::Accepted;}
        virtual EventHandlerState onKeyPressedEvent         (const Event* ) { return EventHandlerState::Dropped;}
        virtual EventHandlerState onKeyReleasedEvent        (const Event* ) { return EventHandlerState::Dropped;}
        virtual EventHandlerState onShortcutEvent           (const Event* ) { return EventHandlerState::Dropped;}
        virtual EventHandlerState onMouseMoveEvent          (const Event* ) { return EventHandlerState::Dropped;}
        virtual EventHandlerState onMouseButtonPressEvent   (const Event* ) { return EventHandlerState::Dropped;}
        virtual EventHandlerState onMouseButtonReleaseEvent (const Event* ) { return EventHandlerState::Dropped;}
        virtual EventHandlerState onMouseScrollEvent        (const Event* ) { return EventHandlerState::Dropped;}
        virtual EventHandlerState onTimerEvent              (const Event* ) { update(); return EventHandlerState::Accepted;}
        
        virtual void update() {}
        virtual void resize(uint32_t w, uint32_t h);
        virtual void resize(const mgm::Vector2u& v);
        
        const Rect& getRect() const {return rect_;}

        void handleSignal(int /*signal*/, void* /*data*/ = nullptr) override {}

    // Non-copyable declaration.
        Widget(const Widget&)            = delete;
        Widget& operator=(const Widget&) = delete;
    };

}

#endif /* ABSTRACTGL_WIDGET_HPP */
