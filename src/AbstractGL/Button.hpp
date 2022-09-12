#ifndef ABSTRACTGL_BUTTON_HPP
#define ABSTRACTGL_BUTTON_HPP
#include "Widget.hpp"

namespace aGL {

class Button : public Widget{
    using ev_func_t = void (*)(const Event& event);

    const char* text_ = nullptr;
    ev_func_t eventFunction_ = nullptr;
public:
    Button(const char* text, uint32_t x, uint32_t y);

    void setEventFunction(ev_func_t handler);
    
    int handleEvent(const Event& event) override;

    void render(const Window &window) override;

};

}
#endif /* ABSTRACTGL_BUTTON_HPP */
