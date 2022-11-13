#ifndef ABSTRACTGL_SIGNALS_HPP
#define ABSTRACTGL_SIGNALS_HPP
#include <Vector/Vector.hpp>
#include <utility>

namespace aGL {
    //Hello, Yarick! I made Qt Signals))
    class SignalObject{};

    template<class... Args>
    class Signal : SignalObject
    {
        using Callable = void (SignalObject::*)(Args...);
        mvc::Vector<std::pair<SignalObject*, Callable>> slots_;
    public:

        template<class T>
        void addResender(T* obj, Signal<Args...> T::* resender)
        {
            connect(&(obj->*resender), &Signal<Args...>::emit);
        }

        template<class T>
        void remResender(T* obj, Signal<Args...> T::* resender)
        {
            disconnect(&(obj->*resender), &Signal<Args...>::emit);
        }


        template<class T>
        void connect(T* obj, void (T::*f)(Args...))
        {
            slots_.push_back({static_cast<SignalObject*>(obj), static_cast<Callable>(f)});
        }

        template<class T>
        void disconnect(T* discObj, void (T::*discF)(Args...))
        {
            for(auto& [obj, f] : slots_)
            {
                if(obj == discObj && f == discF)
                {
                    obj = nullptr;
                }   
            }
        }
        
        
        void emit(Args... args){ for(auto [obj, f] : slots_) if(obj) (obj->*f)(args...);}

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

    template<class T, class U, typename... Args>
    void disconnect(T* sender, Signal<Args...> T::* signal, U* reciever, void (U::*slot)(Args...))
    {
        mAssert(sender != nullptr);
        mAssert(reciever != nullptr);
        (sender->*signal).disconnect(reciever, slot);
    }

    template<class T, class U, typename... Args>
    void addResender(T* sender, Signal<Args...> T::* signal, U* reciever, Signal<Args...> U::* resender)
    {
        mAssert(sender != nullptr);
        mAssert(reciever != nullptr);
        (sender->*signal).addResender(reciever, resender);
    }

}
#endif /* ABSTRACTGL_SIGNALS_HPP */
