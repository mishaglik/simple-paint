#ifndef ABSTRACTGL_AOBJECT_HPP
#define ABSTRACTGL_AOBJECT_HPP
#include <AbstractGL/Signals.hpp>

namespace aGL {
    class Event;
    enum class EventHandlerState;

    class AObject : public SignalObject
    {
    public:
        [[deprecated]] virtual void handleSignal(int signal, void* data = nullptr) = 0;
        virtual EventHandlerState handleEvent(const Event* /*event*/) {return static_cast<EventHandlerState>(0);}
        virtual ~AObject() {}
    };

}
#endif /* ABSTRACTGL_AOBJECT_HPP */
