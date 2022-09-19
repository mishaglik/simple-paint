#ifndef ABSTRACTGL_EVENT_HPP
#define ABSTRACTGL_EVENT_HPP
#include <MGeomerty/Geometry.hpp>
namespace aGL {

using Point = mgm::Point2u;

enum class EventType{
    ERROR,
    Quit,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseWheeled,
    KeyPressedEvent,
    KeyReleasedEvent,
    Other,
};


enum class MouseButton{
    Left,
    Right,
    Middle,
    Other
};

struct MouseButtonEventData{

    MouseButton button;
    Point point;
};

struct MouseMoveEventData{
    Point point;
};

struct MouseWheelEventData{
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

struct KeyEventData{
    KeyboardKey key;
    bool alt;     
    bool control; 
    bool shift;   
    bool system;  
};


class Event{
public:
    EventType type;
    union{
        MouseButtonEventData mbed;
        MouseMoveEventData   mmed;
        MouseWheelEventData  mwed;
        KeyEventData          ked;
    };

    Event() : type(EventType::ERROR) {}
};

enum class HandlerState{
    Accepted,
    Dropped,
    Passed,
};

inline Point getRelPoint(const Point& pt, const mgm::Rect2u& rect){
    return Point{
        pt.x - rect.x,
        pt.y - rect.y
    };
}

}

#endif /* ABSTRACTGL_EVENT_HPP */
