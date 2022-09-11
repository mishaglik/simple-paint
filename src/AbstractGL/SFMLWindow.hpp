#ifndef ABSTRACTGL_SFMLWINDOW_HPP
#define ABSTRACTGL_SFMLWINDOW_HPP
#include <SFML/Graphics.hpp>
#include <cstdint>

namespace aGL {
    // using Window_ = sf::RenderWindow;
    class Window_ : public sf::RenderWindow{
    
    public:
        Window_(uint32_t widht, uint32_t height, const char* title);
    };

}

#endif

