#include "EventManager.hpp"
#include "Widgets/Widget.hpp"

namespace aGL {

    EventManager::EventManager() {}

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
            for(size_t i = subscibers_.size(); i > 0; --i)
            {
                Widget* w = subscibers_[i-1];
                if(w->hasEventPoint(prevMousePosition_) && !w->hasEventPoint(event->mmed.point))
                {
                    w->onMouseLeaveEvent(nullptr);
                    break;
                }
            }

            for(size_t i = subscibers_.size(); i > 0; --i)
            {
                Widget* w = subscibers_[i-1];
                if(!w->hasEventPoint(prevMousePosition_) && w->hasEventPoint(event->mmed.point))
                {
                    w->onMouseEnterEvent(nullptr);
                    break;
                }
            }

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
            break;

        case EventType::MouseWheeled:
            for(size_t i = subscibers_.size(); i > 0; --i)
            {
                Widget* w = subscibers_[i-1];
                eventPointTransform(event, w->getEventCorner());
                EventHandlerState resp = (w->onMouseMoveEvent(event));
                eventPointTransformR(event, w->getEventCorner());
                if(resp == EventHandlerState::Accepted) return resp;
            }
            break;

        case EventType::KeyPressed:
            if(focused_->onKeyPressedEvent(event)) return Accepted;
            return spreadEvent(event, &Widget::onKeyPressedEvent);

        case EventType::KeyReleased:
            if(focused_->onKeyReleasedEvent(event)) return Accepted;
            return spreadEvent(event, &Widget::onKeyReleasedEvent);

        case EventType::TimerTicked:
            return spreadEvent(event, &Widget::onTimerEvent, true);

        case EventType::Paint:
            return spreadEvent(event, &Widget::onPaintEvent, true);

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
        for(Widget* w : subscibers_)
        {
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
            e->mbed.point -= mgm::asVector(pt);
            break;
        case EventType::MouseMoved:
            e->mmed.point -= mgm::asVector(pt);
            break;
        case EventType::MouseWheeled:
            e->mwed.point -= mgm::asVector(pt);
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
            mError << "Inappropriate usage of EventPointTransform\n";
          break;
        }
    }

    void EventManager::eventPointTransformR(Event* e, const Point& pt)
    {
        switch (e->type) {

        case EventType::MouseButtonPressed:
        case EventType::MouseButtonReleased:
            e->mbed.point += mgm::asVector(pt);
            break;
        case EventType::MouseMoved:
            e->mmed.point += mgm::asVector(pt);
            break;
        case EventType::MouseWheeled:
            e->mwed.point += mgm::asVector(pt);
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
            mError << "Inappropriate usage of EventPointTransform\n";
          break;
        }
    }

    void EventManager::setFocused(Widget* w)
    {   
        focused_ = w;
    }

} // namespace aGL
