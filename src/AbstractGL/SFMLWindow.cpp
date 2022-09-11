#include "SFMLWindow.hpp"
#include "AWindow.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <cassert>
#include <iostream>

namespace aGL {

Window_::Window_(uint32_t width, uint32_t height, const char* title): sf::RenderWindow(sf::VideoMode(width, height), title) {}


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

void Window::clear(ColorARGB color){
    wp_->clear(sf::Color(color.color));
}

void Window::drawText(const char* text){
    sf::Font font;
    if (!font.loadFromFile("/home/gms/progs++/vecplot/FreeMono.otf")){
        assert(0);
    }
    sf::Text txt(text, font);
    txt.setPosition(300, 400);
    wp_->draw(txt);
    return;
}

void Window::update(){
    wp_->display();
}

void Window::drawLine(Point p1, Point p2, ColorARGB color) const{
    sf::Vertex lines[2] = {};
    lines[0].position = sf::Vector2f(static_cast<float>(p1.x), static_cast<float>(p1.y));
    lines[1].position = sf::Vector2f(static_cast<float>(p2.x), static_cast<float>(p2.y));

    lines[0].color = lines[1].color = sf::Color(color.color);

    wp_->draw(lines, 2, sf::Lines);
}

void Window::drawRect(const Rect& rect, ColorARGB color) const{
    sf::RectangleShape sfRect(sf::Vector2f(static_cast<float>(rect.w), static_cast<float>(rect.h)));
    sfRect.setPosition(static_cast<float>(rect.x), static_cast<float>(rect.y));
    sfRect.setFillColor(sf::Color(color.color));
    wp_->draw(sfRect);
}
    
    void drawPoint   ();
    void drawTexture ();



bool Window::pollEvent(Event& event){
    sf::Event sfEvent;
    if(wp_->pollEvent(sfEvent)){
        if(sfEvent.type == sf::Event::Closed){
            event.type = EventType::Exit;
        }
        else event.type = EventType::Other;  
        return true;
    }
    return false;
}

}
