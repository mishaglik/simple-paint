#ifndef ABSTRACTGL_WIDGET_HPP
#define ABSTRACTGL_WIDGET_HPP
#include "AWindow.hpp"

namespace aGL {

class Widget : public AObject {
private:
protected:
    Rect rect_;

public:
    Widget() : rect_({0, 0, 100, 100}) {}
    Widget(const Rect& rect) : rect_(rect) {}
    
    virtual int handleEvent(const Event&){ return 1;}

    virtual void render(const Window &window);
    virtual void update() {}
    virtual void resize(uint32_t w, uint32_t h);
    virtual void resize(const mgm::Vector2u& v);
    
    const Rect& getRect() {return rect_;}

    void handleSignal(int /*signal*/, void* /*data*/ = nullptr) override {}

// Non-copyable declaration.
    Widget(const Widget&)            = delete;
    Widget& operator=(const Widget&) = delete;
};

}

#endif /* ABSTRACTGL_WIDGET_HPP */
