#include "SFMLWindow.hpp"
#include "AWindow.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <cassert>
#include <iostream>

namespace aGL {

Window_::Window_(uint32_t width, uint32_t height, const char* title): sf::RenderWindow(sf::VideoMode(width, height), title) {}

Window_::~Window_() {}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------


Window::Window(uint32_t width, uint32_t height, const char* title) :
    wp_(new Window_(width, height, title))
{
    assert(wp_ != nullptr);
}

Window::~Window(){
    delete wp_;
    wp_ = nullptr;
}

void Window::resize(uint32_t width, uint32_t height){
    wp_->setSize(sf::Vector2u(width, height));
}

void Window::show(){
    wp_->setVisible(true);
}

void Window::hide(){
    wp_->setVisible(false);
}

void Window::clear(Color color){
    wp_->clear(sf::Color(color));
}

void Window::drawText(const char* text, Point pt, Color color) const{
    sf::Font font;
    if (!font.loadFromFile("/home/gms/progs++/vecplot/FreeMono.otf")){
        assert(0);
    }
    sf::Text txt(text, font);
    txt.setFillColor(sf::Color(color));
    txt.setPosition({static_cast<float>(pt.x), static_cast<float>(pt.y)});
    wp_->draw(txt);
    return;
}

void Window::update(){
    wp_->display();
}

void Window::drawLine(Point p1, Point p2, Color color) const{
    sf::Vertex lines[2] = {};
    lines[0].position = sf::Vector2f(static_cast<float>(p1.x), static_cast<float>(p1.y));
    lines[1].position = sf::Vector2f(static_cast<float>(p2.x), static_cast<float>(p2.y));

    lines[0].color = lines[1].color = sf::Color(color);

    wp_->draw(lines, 2, sf::Lines);
}

void Window::drawRect(const Rect& rect, Color color) const{
    sf::RectangleShape sfRect(sf::Vector2f(static_cast<float>(rect.w), static_cast<float>(rect.h)));
    sfRect.setPosition(static_cast<float>(rect.x), static_cast<float>(rect.y));
    sfRect.setFillColor(sf::Color(color));
    wp_->draw(sfRect);
}
    
void Window::drawPoint(Point p, Color color) const {
    sf::Vertex vertex({
        static_cast<float>(p.x),
        static_cast<float>(p.y)
        }, sf::Color(color));
    wp_->draw(&vertex, 1, sf::Points);
}


static MouseButton getMouseButton(sf::Mouse::Button button){
    switch (button) {

    case sf::Mouse::Left:
        return MouseButton::Left;
    case sf::Mouse::Right:
        return MouseButton::Right;
    case sf::Mouse::Middle:
        return MouseButton::Middle;
    case sf::Mouse::XButton1:
    case sf::Mouse::XButton2:
    case sf::Mouse::ButtonCount:
        return MouseButton::Other;
    }
    assert(0 && "Wrong switch");
}


bool Window::pollEvent(Event& event){
    sf::Event sfEvent;
    if(wp_->pollEvent(sfEvent)){
        switch (sfEvent.type) {

        case sf::Event::KeyPressed:
            event.type = EventType::KeyPressedEvent;
            event.ked = *reinterpret_cast<KeyEventData*>(&sfEvent.key); // I'm personally created very simmilar to SFML prototypes, so I've decided to make reinterperter cast.
            break;

        case sf::Event::KeyReleased:
            event.type = EventType::KeyReleasedEvent;
            event.ked = *reinterpret_cast<KeyEventData*>(&sfEvent.key);
            break;

        case sf::Event::Closed:
            event.type = EventType::Quit;
            break;
            
        case sf::Event::MouseWheelScrolled:
            event.type = EventType::MouseWheeled;
            event.mwed.delta = sfEvent.mouseWheel.delta;
            event.mwed.point = {
                                static_cast<uint32_t>(sfEvent.mouseWheel.x),
                                static_cast<uint32_t>(sfEvent.mouseWheel.y)
                               };
            break;

        case sf::Event::MouseButtonPressed:
            event.type = EventType::MouseButtonPressed;
            event.mbed.button = getMouseButton(sfEvent.mouseButton.button);
            event.mbed.point = {
                                static_cast<uint32_t>(sfEvent.mouseButton.x),
                                static_cast<uint32_t>(sfEvent.mouseButton.y)
                               };
            break;
        case sf::Event::MouseButtonReleased:
            event.type = EventType::MouseButtonReleased;
            event.mbed.button = getMouseButton(sfEvent.mouseButton.button);
            event.mbed.point = {
                                static_cast<uint32_t>(sfEvent.mouseButton.x),
                                static_cast<uint32_t>(sfEvent.mouseButton.y)
                               };
            break;
        case sf::Event::MouseMoved:
            event.type = EventType::MouseMoved;
            event.mmed.point = {
                                static_cast<uint32_t>(sfEvent.mouseMove.x),
                                static_cast<uint32_t>(sfEvent.mouseMove.y)
                               };
            break;
        case sf::Event::MouseWheelMoved:
        case sf::Event::Resized:
        case sf::Event::LostFocus:
        case sf::Event::GainedFocus:
        case sf::Event::TextEntered:
        case sf::Event::MouseEntered:
        case sf::Event::MouseLeft:
        case sf::Event::JoystickButtonPressed:
        case sf::Event::JoystickButtonReleased:
        case sf::Event::JoystickMoved:
        case sf::Event::JoystickConnected:
        case sf::Event::JoystickDisconnected:
        case sf::Event::TouchBegan:
        case sf::Event::TouchMoved:
        case sf::Event::TouchEnded:
        case sf::Event::SensorChanged:
        case sf::Event::Count:
            event.type = EventType::Other;
          break;
        }
        return true;
    }
    return false;
}

}
