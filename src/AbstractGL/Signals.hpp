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
        template<class T>
        void connect(T* obj, void (T::*f)(Args...))
        {
            slots_.push_back({static_cast<SignalObject*>(obj), static_cast<Callable>(f)});
        }
        
        
        void emit(Args... args){ for(auto [obj, f] : slots_) (obj->*f)(args...);}

        Signal() : slots_() {}
        Signal(const Signal&) = delete;
        Signal& operator= (const Signal&) = delete;
        ~Signal(){}
    };

    template<class T, class U, typename... Args>
    void connect(T* sender, Signal<Args...> T::* signal, U* reciever, void (U::*slot)(Args...))
    {
        mAssert(sender != nullptr);
        mAssert(reciever != nullptr);
        (sender->*signal).connect(reciever, slot);
    }


#endif /* ABSTRACTGL_SIGNALS_HPP */
