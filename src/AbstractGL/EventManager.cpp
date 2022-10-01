#include "EventManager.hpp"
#include "Widget.hpp"
#include "AObject.hpp"

namespace aGL {

    EventManager::Subscriber::Subscriber(Widget* widget, EventType _type) :
        isWidget(true), object(widget), type(_type) 
    {

    }

    EventManager::Subscriber::Subscriber(AObject* _object) :
        isWidget(false), object(_object), type(EventType::ERROR)
    {

    }

    EventManager::EventManager()
    {

    }
    
    EventManager::~EventManager()
    {

    } 

    int EventManager::registerUserEvent()
    {
        if(curUserEvent_ > static_cast<int>(EventType::UserMax))
        {
            return -1;
        }
        return curUserEvent_++;
    }

    bool EventManager::subscribeOn(EventType eventType, Widget* widget)
    {
        //TODO: Implement checks
        subscibers_.push_back(Subscriber{widget, eventType});
        return true;
    }

    bool EventManager::subscribe(AObject* object)
    {
        //TODO: Implement checks
        subscibers_.push_back(Subscriber{object});
        return true;
    }

    EventHandlerState EventManager::handleEvent(const Event* event) const
    {
        EventHandlerState state = EventHandlerState::Dropped;
        auto it = subscibers_.begin();
        mAssert(!(it != it));
        for (const Subscriber& subs : subscibers_) {
            EventHandlerState resp;
            if(!subs.isWidget)
            {
                resp = subs.object->handleEvent(event); 
            }
            else /* isWidget */{
                Widget* w = static_cast<Widget*>(subs.object);
                switch (event->type) {

                case EventType::ERROR:
                    mError << "EventHandler: ERROR event was passed.\n";
                    return EventHandlerState::Dropped;

                case EventType::MouseButtonPressed:
                case EventType::MouseButtonReleased:
                    resp = w->onMouseClickEvent(event);
                    break;
                case EventType::MouseMoved:
                    resp = w->onMouseMoveEvent(event);
                    break;
                case EventType::MouseWheeled:
                    resp = w->onMouseScrollEvent(event);
                    break;
                case EventType::KeyPressed:
                case EventType::KeyReleased:
                    resp = w->onKeyboardEvent(event);
                    break;
                case EventType::TimerTicked:
                    resp = w->onTimerEvent(event);
                    break;
                case EventType::Paint:
                    resp = w->onPaintEvent(event);
                    break;
                case EventType::Quited:
                case EventType::UserMin:
                case EventType::UserMax:
                case EventType::Other:
                default:
                    resp = subs.object->handleEvent(event);
                }
            }
            if(resp == EventHandlerState::Owned) return resp;
            if(resp != EventHandlerState::Dropped)
                    state = resp;
        }
        return state;
    }
}
