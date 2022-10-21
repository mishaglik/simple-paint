#ifndef WIDGETS_WINDOWWIDGET_HPP
#define WIDGETS_WINDOWWIDGET_HPP
#include <Widgets/ContainerWidget.hpp>
#include <AbstractGL/AWindow.hpp>

namespace aGL {
    class WWindow: public Window, public ContainerWidget
    {
    public:
        WWindow(uint32_t w, uint32_t h, const char* title):
            Window(w, h, title), ContainerWidget({0, 0, w, h}, nullptr, nullptr) {}

        Signal<> quited;
        void quit() { quited.emit(); }
        virtual EventHandlerState handleEvent(const Event* event) override 
        {
            if(event->type == EventType::Quited)
            {
                quited.emit();
                return EventHandlerState::Accepted;
            }
            return ContainerWidget::handleEvent(event);
        }

        void render(const Window &) const override { mFatal << "Window is tried to be drawn\n"; }
        void render() const 
        { 
            if(skinned())
            {
                drawSprite({}, sm_->getTexture(texId_));
            }
            else {
                clear(0x999999ff);
            }
            
            ContainerWidget::render(this);
        }

        void update() override 
        {
            Event event = {};
            while(pollEvent(event))
            {
                handleEvent(&event);
            }
            Window::update();
        }
    };
}

#endif /* WIDGETS_WINDOWWIDGET_HPP */
