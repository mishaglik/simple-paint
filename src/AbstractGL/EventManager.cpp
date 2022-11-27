#include "EventManager.hpp"
#include "Widgets/Widget.hpp"

namespace aGL {

    EventManager::EventManager(const Point& ) /*: corner_(corner)*/ {}

    EventManager::~EventManager() {}

    int EventManager::registerUserEvent() {
        if (curUserEvent_ > static_cast<int>(EventType::UserMax)) {
            return -1;
        }
        return curUserEvent_++;
    }

    EventHandlerState EventManager::handleEvent(Event *event)
    {
        auto it = subscibers_.end();
        mAssert(!(it != it));
        
        switch (event->type) {

        case EventType::ERROR:
            mFatal << "ERROR event has been handeled\n";
            return EventHandlerState::Dropped;

        case EventType::MouseButtonPressed:
            for(size_t i = subscibers_.size(); i > 0; --i)
            {
                Widget* w = subscibers_[i-1];
                if(w->hasEventPoint(event->mbed.point))
                {
                    eventPointTransform(event, w->getEventCorner());
                    EventHandlerState resp = (w->onMouseButtonPressEvent(event));
                    eventPointTransformR(event, w->getEventCorner());
                    if(resp == EventHandlerState::Accepted){
                        if(focused_ != w)
                        {
                            if(focused_) focused_->onLoseFocusEvent(nullptr);
                            w->onGainFocusEvent(nullptr);
                            focused_ = w;
                        }
                        return resp;
                    }
                }
            }
            break;

        case EventType::MouseButtonReleased:
            if(focused_ != nullptr){
                eventPointTransform(event, focused_->getEventCorner());
                EventHandlerState resp = focused_->onMouseButtonReleaseEvent(event);
                eventPointTransformR(event, focused_->getEventCorner());
                if(resp == EventHandlerState::Accepted) return resp;
            }

            for(size_t i = subscibers_.size(); i > 0; --i)
            {
                Widget* w = subscibers_[i-1];

                if(w != focused_ && w->hasEventPoint(event->mbed.point))
                {
                    eventPointTransform(event, w->getEventCorner());
                    EventHandlerState resp = (w->onMouseButtonReleaseEvent(event));
                    eventPointTransformR(event, w->getEventCorner());
                    if(resp == EventHandlerState::Accepted) return resp;
                }
            }
            break;
        
        case EventType::MouseMoved:
        {
            Widget* curTop = nullptr;
            for(size_t i = subscibers_.size(); i > 0; --i)
            {
                Widget* w = subscibers_[i-1];
                if(w->hasEventPoint(event->mmed.point))
                {
                    curTop = w;
                    break;
                }
            }

            if(top_ != curTop)
            {
                if(top_) top_->onMouseLeaveEvent(event);
                if(curTop) curTop->onMouseEnterEvent(event);
                top_ = curTop;
            }

            prevMousePosition_ = event->mmed.point;
            
            for(size_t i = subscibers_.size(); i > 0; --i)
            {
                Widget* w = subscibers_[i-1];
                if(w->hasEventPoint(event->mmed.point))
                {
                    eventPointTransform(event, w->getEventCorner());
                    EventHandlerState resp = (w->onMouseMoveEvent(event));
                    eventPointTransformR(event, w->getEventCorner());
                    if(resp == EventHandlerState::Accepted) return resp;
                }
            }
        }
        break;

        case EventType::MouseWheeled:
            if(focused_)
            {
                eventPointTransform (event, focused_->getEventCorner());
                EventHandlerState resp = focused_->onMouseScrollEvent(event);
                eventPointTransformR(event, focused_->getEventCorner());
                if(resp == EventHandlerState::Accepted) return resp;
            }

            for(size_t i = subscibers_.size(); i > 0; --i)
            {
                Widget* w = subscibers_[i-1];
                if(w->isHidden() || !w->hasEventPoint(event->mwed.point)) continue;
                eventPointTransform(event, w->getEventCorner());
                EventHandlerState resp = (w->onMouseScrollEvent(event));
                eventPointTransformR(event, w->getEventCorner());
                if(resp == EventHandlerState::Accepted) return resp;
            }
            break;

        case EventType::KeyPressed:
            if(focused_ && focused_->onKeyPressedEvent(event)) return Accepted;
            return spreadEvent(event, &Widget::onKeyPressedEvent);
        
        case EventType::TextEntered:
            if(focused_ && focused_->onKeyPressedEvent(event)) return Accepted;
            return spreadEvent(event, &Widget::onTextEnteredEvent);

        case EventType::KeyReleased:
            if(focused_ && focused_->onKeyReleasedEvent(event)) return Accepted;
            return spreadEvent(event, &Widget::onKeyReleasedEvent);

        case EventType::TimerTicked:
            return spreadEvent(event, &Widget::onTimerEvent, true);

        case EventType::Paint:
            return spreadEvent(event, &Widget::onPaintEvent, true);
            
        case EventType::Reskin:
            return spreadEvent(event, &Widget::onReskinEvent, true);

        case EventType::Quited:
        case EventType::UserMin:
        case EventType::UserMax:
        case EventType::Other:
        default:
            spreadEvent(event, &Widget::handleEvent);
            break;
        }

  
    return EventHandlerState::Dropped;
    }

    EventHandlerState EventManager::spreadEvent(const Event* event, EventHandlerState (Widget::*function)(const Event*), bool forced) const
    {
        // if(subscibers_.size() == 0) mError << mlg::Logger::CoStyle::Red << "Empty subs" << mlg::endl;
        for(size_t i = 0; i < subscibers_.size(); ++i)
        {
            Widget* w = subscibers_[i];
            mAssert(w);
            EventHandlerState resp = (w->*function)(event);
            if(!forced && resp == EventHandlerState::Accepted) return resp;
        }
        return Accepted;
    }

    void EventManager::eventPointTransform(Event* e, const Point& pt)
    {
        switch (e->type) {

        case EventType::MouseButtonPressed:
        case EventType::MouseButtonReleased:
            e->mbed.point -= pt - corner_;
            break;
        case EventType::MouseMoved:
            e->mmed.point -= pt - corner_;
            break;
        case EventType::MouseWheeled:
            e->mwed.point -= pt - corner_;
            break;
        case EventType::ERROR:
        case EventType::KeyPressed:
        case EventType::KeyReleased:
        case EventType::TimerTicked:
        case EventType::Paint:
        case EventType::Quited:
        case EventType::UserMin:
        case EventType::UserMax:
        case EventType::Other:
        case EventType::TextEntered:
            mError << "Inappropriate usage of EventPointTransform\n";
          break;
        }
    }

    void EventManager::eventPointTransformR(Event* e, const Point& pt)
    {
        switch (e->type) {

        case EventType::MouseButtonPressed:
        case EventType::MouseButtonReleased:
            e->mbed.point += pt - corner_;
            break;
        case EventType::MouseMoved:
            e->mmed.point += pt - corner_;
            break;
        case EventType::MouseWheeled:
            e->mwed.point += pt - corner_;
            break;
        case EventType::ERROR:
        case EventType::KeyPressed:
        case EventType::KeyReleased:
        case EventType::TimerTicked:
        case EventType::Paint:
        case EventType::Quited:
        case EventType::UserMin:
        case EventType::UserMax:
        case EventType::TextEntered:
        case EventType::Other:
            mError << "Inappropriate usage of EventPointTransform\n";
          break;
        }
    }

    void EventManager::setFocused(Widget* w)
    {   
        focused_ = w;
    }

    void EventManager::unsubscribe(Widget* widget)
    {
        if(widget == focused_) setFocused(nullptr);
        if(widget == top_) top_ = nullptr;

        for(auto it = subscibers_.begin(); it != subscibers_.end(); it++)
        {
            if(*it == widget)
            {
                subscibers_.erase(it);
                return;
            }
        }
    }


} // namespace aGL
