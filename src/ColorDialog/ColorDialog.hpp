#ifndef COLORDIALOG_COLORDIALOG_HPP
#define COLORDIALOG_COLORDIALOG_HPP

#include <Widgets/Dialog.hpp>
#include <Widgets/Button.hpp>

namespace aGL {


    class ColorSelector : public ContainerWidget
    {
        class ColorBoard ;
        class ColorScroll;
        ColorBoard* board_ = nullptr; 
        ColorScroll* scroll_ = nullptr;
        aGL::PushButton* exitbutton = nullptr;
        aGL::Color currentColor_;
    public:
        ColorSelector(aGL::Color start, uint32_t x = 0, uint32_t y = 0, Widget* parent = nullptr);
        EventHandlerState onPaintEvent(const Event* e) override { ContainerWidget::onPaintEvent(e); surface->drawRect({5, 220, 60, 20}, currentColor_); return Accepted;}
        EventHandlerState onKeyPressedEvent(const Event* e) override;
        Signal<aGL::Color> colorSelected; 
        Signal<aGL::Color> finished;
        Signal<> done;
        void setSV(uint8_t s, uint8_t v);
        void setH(uint32_t h);
        void finish()
        {
            finished.emit(currentColor_);
            done.emit();
        }
    };

    class ColorSelector::ColorBoard : public Widget
    {
        uint32_t hue_;
        uint8_t sSel_ = 0, vSel_ = 0;
        bool pressed_ = false;
    public:
        ColorBoard(aGL::Color start, uint32_t x = 0, uint32_t y = 0, Widget* parent = nullptr);
        EventHandlerState onPaintEvent(const Event*) override;
        EventHandlerState onMouseButtonPressEvent(const Event*) override;
        EventHandlerState onMouseMoveEvent(const Event* ) override;
        EventHandlerState onMouseButtonReleaseEvent(const Event*) override;
        EventHandlerState onMouseLeaveEvent(const Event* e) override {pressed_ = false; return aGL::Widget::onMouseLeaveEvent(e);}
        void setHue(uint32_t h);
        Signal<uint8_t, uint8_t> selected;
    };

    class ColorDialog : public Dialog
    {
    public:
        ColorDialog(const char* title = "Enter color", aGL::Color startC = aGL::Colors::Yellow)
            : Dialog(300, 300, title)
        {
            ColorSelector* selector = new ColorSelector(startC, 0, 0, this);
            selector->finished     .addResender(this, &ColorDialog::finished);
            selector->done         .connect<ColorDialog>(this, &ColorDialog::quit);
            selector->colorSelected.addResender(this, &ColorDialog::colorSelected);
            backgroundColor_ = 0x454545ff;
        }
        Signal<Color> colorSelected; 
        Signal<Color> finished;
    private:
    };

    class ColorSelector::ColorScroll : public Widget
    {
        uint32_t hue_ = 0;
        bool pressed_ = false;
    public:
        ColorScroll(uint32_t x = 0, uint32_t y = 0, uint32_t hue = 0, Widget* parent = nullptr) : Widget({x, y, 20,200}, parent), hue_(hue) {}
        EventHandlerState onPaintEvent(const Event* ) override;
        EventHandlerState onMouseButtonPressEvent(const Event* ) override;
        EventHandlerState onMouseButtonReleaseEvent(const Event* ) override;
        EventHandlerState onMouseMoveEvent(const Event* ) override;
        EventHandlerState onMouseLeaveEvent(const Event* e) override;
        Signal<uint32_t> hueChanged;
    };

}

#endif /* COLORDIALOG_COLORDIALOG_HPP */
