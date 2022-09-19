#include "Widget.hpp"

namespace aGL {

void Widget::resize(int32_t w, int32_t h){
    rect_.w = w;
    rect_.h = h;
    
}

void Widget::resize(const mgm::Vector2u& v){
    rect_.w = v.x;
    rect_.h = v.y;
}

void Widget::render(const Window &window) const {
    window.drawSurf(rect_.getCornerLL(), *surface);
}

void Widget::onPaintEvent() const{
    
}


}
