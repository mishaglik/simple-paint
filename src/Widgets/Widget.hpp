#ifndef WIDGETS_WIDGET_HPP
#define WIDGETS_WIDGET_HPP
#include "AbstractGL/ASprite.hpp"
#include "AbstractGL/EventManager.hpp"
#include "Widgets/SkinManager.hpp"
#include <AbstractGL/AWindow.hpp>

namespace aGL {
    class SkinManager;
    using TexId = size_t;
    class Widget : public AObject 
    {
    private:
        bool hidden_ = false;
    protected:
        mvc::Vector<Widget*> childen_;
        EventManager* evMgr_ = nullptr;
        Widget* parent_ = nullptr;
        using Timepoint = Event::Timepoint;
        bool focused_ = false; 
        Rect rect_;
        Surface* surface;
        Sprite sprite_;
        Timepoint time_;
        const SkinManager* sm_ = nullptr;
        TexId texId_ = 0;
        const char* texName_ = nullptr;
    public:
        explicit Widget(Widget* parent = nullptr) : Widget(Rect{100,100,0,0}, parent) {}
        explicit Widget(const Rect& rect, Widget* parent = nullptr) : parent_(parent), rect_(rect), maxW_(rect.w), maxH_(rect.h)
        { 
            if(parent_)
            {
                parent_->addChild(this);
            }
            RenderSurface* surf = new RenderSurface(rect.w, rect.h);
            surface = surf;
            sprite_ = Sprite(surf->getTexture());
        }
        Widget(const Rect& rect, RenderSurface* surf, Widget* parent = nullptr) : 
            parent_(parent), rect_(rect), surface(surf), maxW_(rect.w), maxH_(rect.h)
        { if(parent_)
            {
                parent_->addChild(this);
            } }

    protected:
        virtual ~Widget() 
        { 
            for(Widget* w : childen_) 
            { 
                if(w == this) 
                {
                    mFatal << "Widget: " << w << " == this" << mlg::endl;
                    continue;
                }

                delete w;
            } 
            delete surface;
        }
    public:
        Widget& setSkinManager(const SkinManager* sm_);
        virtual void onSkinChange();
        
        void setTexId(TexId id) { texId_ = id; texName_ = nullptr; }
        void setTexId(const char* name);
        virtual Widget& setEventManager(EventManager* em);
        void addChild(Widget* child); //TODO: Make only container could have children.
        void delChild(Widget* child);

        virtual void render(const Window &window) const;
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

        virtual void setPoisition(uint32_t x, uint32_t y);
        virtual void move(uint32_t x, uint32_t y);

        Signal<uint32_t, uint32_t> resized;

        void show() { hidden_ = false; }
        void hide() { hidden_ = true; }
        bool isHidden() const { return hidden_; }
        bool skinned() const {return texId_ != NoTexture && texId_ != IgnoreTexture;}
        
        const Rect& getRect() const {return rect_;}
        const Point getEventCorner() const { return rect_.getCornerLL(); }
        virtual bool hasEventPoint(const Point& pt) { return hidden_ ? false : mgm::contains(rect_, pt); }
    // Non-copyable declaration.
        Widget(const Widget&)            = delete;
        Widget& operator=(const Widget&) = delete;
    private:
        uint32_t maxW_ = 0, maxH_ = 0;
    };

}

#endif /* WIDGETS_WIDGET_HPP */
