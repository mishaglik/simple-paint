#ifndef ABSTRACTGL_WIDGET_HPP
#define ABSTRACTGL_WIDGET_HPP
#include "AWindow.hpp"

namespace aGL {

class Widget{
private:
protected:
    Rect rect_;

public:
    Widget() : rect_({0, 0, 100, 100}) {}
    Widget(const Rect& rect) : rect_(rect) {}

    virtual ~Widget() {}
    
    virtual int handleEvent(const Event&){ return 1;}

    virtual void render(const Window &window);
    virtual void update() {}
    
    const Rect& getRect() {return rect_;}

    Widget(const Widget&) = delete;
    Widget& operator=(const Widget&) = delete;
};

}

#endif /* ABSTRACTGL_WIDGET_HPP */
