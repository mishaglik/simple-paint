#ifndef ABSTRACTGL_EVENTMANAGER_HPP
#define ABSTRACTGL_EVENTMANAGER_HPP

#include "AbstractGL/Event.hpp"
#include "Vector/Vector.hpp"

namespace aGL {
    class Widget;
    class AObject;

    class EventManager
    {

        struct Subscriber
        {
            bool isWidget;
            AObject* object;
            EventType type;

            Subscriber(Widget* widget, EventType _type);
            Subscriber(AObject* _object);
        };

        mvc::Vector<Subscriber> subscibers_;
        int curUserEvent_ = static_cast<int>(EventType::UserMin);
    public:
        EventManager();
        ~EventManager(); 

        int registerUserEvent();
        bool subscribeOn(EventType eventType, Widget* widget);
        bool subscribe(AObject* object);
        EventHandlerState handleEvent(const Event* event) const;

        EventManager(const EventManager&) = delete;
        EventManager& operator=(const EventManager& ) = delete; 
    };

}

#endif /* ABSTRACTGL_EVENTMANAGER_HPP */
