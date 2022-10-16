#ifndef ABSTRACTGL_EVENTMANAGER_HPP
#define ABSTRACTGL_EVENTMANAGER_HPP

#include "AbstractGL/Event.hpp"
#include "Vector/Vector.hpp"

namespace aGL {
    class Widget;

    class EventManager
    {
        EventHandlerState spreadEvent(const Event* event, EventHandlerState (Widget::*function)(const Event*), bool forced = false) const;
        mvc::Vector<Widget* > subscibers_;
        int curUserEvent_ = static_cast<int>(EventType::UserMin);
        Point prevMousePosition_ = {-1, -1};
        Widget* focused_ = nullptr;
        Widget* top_ = nullptr;
        void eventPointTransform(Event* e, const Point& pt);
        void eventPointTransformR(Event* e, const Point& pt);

        Point corner_;
    public:
        EventManager(const Point& corner = {0, 0});
        ~EventManager(); 

        int registerUserEvent();
        bool subscribe(Widget* object) {subscibers_.push_back(object); return true;}
        EventHandlerState handleEvent(Event* event);

        void setFocused(Widget* w);

        EventManager(const EventManager&) = delete;
        EventManager& operator=(const EventManager& ) = delete; 
    };

}

#endif /* ABSTRACTGL_EVENTMANAGER_HPP */
