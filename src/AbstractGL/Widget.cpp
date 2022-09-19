#include "Widget.hpp"

namespace aGL {
    
void Widget::render(const Window&){

}

void Widget::resize(uint32_t w, uint32_t h){
    rect_.w = w;
    rect_.h = h;
}

void Widget::resize(const mgm::Vector2u& v){
    rect_.w = v.x;
    rect_.h = v.y;
}

}
