#ifndef ABSTRACTGL_SIGNALS_HPP
#define ABSTRACTGL_SIGNALS_HPP
#include <Vector/Vector.hpp>
#include <utility>

namespace aGL {
    //Hello, Yarick! I made Qt Signals))
    class SignalObject{};

    template<class... Args>
    class Signal{
        using Callable = void (SignalObject::*)(Args...);
        mvc::Vector<std::pair<SignalObject*, Callable>> slots_;
    public:
        void connect(SignalObject* obj, Callable f) {slots_.push_back({obj, f});}
        
        void emit(Args... args){ for(auto [obj, f] : slots_) (obj->*f)(args...);}

        Signal() : slots_() {}
        Signal(const Signal&) : slots_() {}
        Signal& operator= (const Signal&) = delete;
        ~Signal(){}
    };

    template<class T, class U, typename... Args>
    void connect(T* sender, Signal<Args...> T::* signal, U* reciever, void (U::*slot)(Args...))
    {
        (sender->*signal).connect(static_cast<SignalObject*>(reciever), static_cast<void (SignalObject::*)(Args...)>(slot));
    }

}

#endif /* ABSTRACTGL_SIGNALS_HPP */
