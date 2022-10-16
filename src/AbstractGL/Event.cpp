#include "Event.hpp"
namespace aGL {
    mlg::Logger& operator<<(mlg::Logger& log, Event& event)
    {
        log << "Event {";
        switch (event.type) {
        case EventType::ERROR:
        return log << mlg::ConsoleLogger::CoStyle::BRed << "ERROR}";
        case EventType::MouseButtonPressed:
            log << "MouseButtonPressed, "  << static_cast<int>(event.mbed.button) << ' ' << event.mbed.point << "}";
            break;
        case EventType::MouseButtonReleased:
            log << "MouseButtonReleased, "  << static_cast<int>(event.mbed.button) << ' ' << event.mbed.point << "}";
            break;
        case EventType::MouseMoved:
            log << "MouseButtonMoved, "  << event.mmed.point << "}";
            break;
        case EventType::MouseWheeled:
        case EventType::KeyPressed:
        case EventType::KeyReleased:
        case EventType::TimerTicked:
        case EventType::Paint:
        case EventType::Quited:
        case EventType::UserMin:
        case EventType::UserMax:
        case EventType::Other:
            log << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA}";
          break;
        case EventType::TextEntered:
            log << "Text entered:" << event.text;
          break;
        }
        return log;
    }
}
