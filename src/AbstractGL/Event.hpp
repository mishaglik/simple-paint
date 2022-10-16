#ifndef ABSTRACTGL_EVENT_HPP
#define ABSTRACTGL_EVENT_HPP
#include <MGeomerty/Geometry.hpp>
#include <LogUtils/LogUtils.hpp>
#include <chrono>

namespace aGL {

    using Point = mgm::Point2i;

    enum class EventType{
        ERROR,
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        MouseWheeled,
        KeyPressed,
        KeyReleased,
        TextEntered,
        TimerTicked,
        Paint,
        Quited,
        UserMin = 1000,
        UserMax = 2000,
        Other,
    };


    enum class MouseButton{
        Left,
        Right,
        Middle,
        Other
    };

    struct MouseButtonEventData
    {

        MouseButton button;
        Point point;
    };

    struct MouseMoveEventData
    {
        Point point;
    };

    struct MouseWheelEventData
    {
        int delta;
        Point point;
    };

    enum class KeyboardKey{
        Unknown = -1, 
        A = 0,        
        B,            
        C,            
        D,            
        E,            
        F,            
        G,            
        H,            
        I,            
        J,            
        K,            
        L,            
        M,            
        N,            
        O,            
        P,            
        Q,            
        R,            
        S,            
        T,            
        U,            
        V,            
        W,            
        X,            
        Y,            
        Z,            
        Num0,         
        Num1,         
        Num2,         
        Num3,         
        Num4,         
        Num5,         
        Num6,         
        Num7,         
        Num8,         
        Num9,         
        Escape,       
        LControl,     
        LShift,       
        LAlt,         
        LSystem,      
        RControl,     
        RShift,       
        RAlt,         
        RSystem,      
        Menu,         
        LBracket,     
        RBracket,     
        Semicolon,    
        Comma,        
        Period,       
        Quote,        
        Slash,        
        Backslash,    
        Tilde,        
        Equal,        
        Hyphen,       
        Space,        
        Enter,        
        Backspace,    
        Tab,          
        PageUp,       
        PageDown,     
        End,          
        Home,         
        Insert,       
        Delete,       
        Add,          
        Subtract,     
        Multiply,     
        Divide,       
        Left,         
        Right,        
        Up,           
        Down,         
        Numpad0,      
        Numpad1,      
        Numpad2,      
        Numpad3,      
        Numpad4,      
        Numpad5,      
        Numpad6,      
        Numpad7,      
        Numpad8,      
        Numpad9,      
        F1,           
        F2,           
        F3,           
        F4,           
        F5,           
        F6,           
        F7,           
        F8,           
        F9,           
        F10,          
        F11,          
        F12,          
        F13,          
        F14,          
        F15,          
        Pause,        
    };

    struct KeyEventData
    {
        KeyboardKey key;
        bool alt;     
        bool control; 
        bool shift;   
        bool system;  
    };


    class Event //TODO: Make abstract.
    {
    public:
        using Timepoint = std::chrono::system_clock::time_point;
        EventType type;
        union{
            MouseButtonEventData mbed;
            MouseMoveEventData   mmed;
            MouseWheelEventData  mwed;
            KeyEventData          ked;
            uint32_t             text;
            Timepoint            time;
        };

        Event() : type(EventType::ERROR) {}
    };

    enum EventHandlerState : bool{
        Dropped = 0,
        Accepted = 1,
    };

    inline Point getRelPoint(const Point& pt, const mgm::Rect2u& rect)
    {
        return Point{
            pt.x - static_cast<int>(rect.x),
            pt.y - static_cast<int>(rect.y)
        };
    }

    mlg::Logger& operator<<(mlg::Logger& log, Event& event);

}

#endif /* ABSTRACTGL_EVENT_HPP */
