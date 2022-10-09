#ifndef ABSTRACTGL_AOBJECT_HPP
#define ABSTRACTGL_AOBJECT_HPP
#include <AbstractGL/Signals.hpp>
#include <LogUtils/LogUtils.hpp>
namespace aGL {
    class Event;
    enum class EventHandlerState;

    class AObject : public SignalObject
    {
    public:
        [[deprecated]] virtual void handleSignal(int /*signal*/, void* /*data*/ = nullptr) {MLG_UIMPLEMENTED}
        virtual EventHandlerState handleEvent(const Event* /*event*/) {return static_cast<EventHandlerState>(0);}
        virtual ~AObject() {}
    };

}
#endif /* ABSTRACTGL_AOBJECT_HPP */
