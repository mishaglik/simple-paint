#ifndef WIDGETS_SCROLLBAR_HPP
#define WIDGETS_SCROLLBAR_HPP

#include <Widgets/Widget.hpp>

namespace aGL {
    class Scrollbar : public Widget
    {
    public:
        enum Orientation
        {
            Vertical = 0,
            Horizontal,
        };

        Scrollbar(const aGL::Rect& rect, Orientation orientation = Orientation::Horizontal, uint32_t scrollSize = 33, Widget* parent = nullptr);
        Scrollbar(uint32_t x, uint32_t y, uint32_t w = 200, uint32_t h = 20, Orientation orientation = Orientation::Horizontal, uint32_t scrollSize = 33, Widget* parent = nullptr)
            : Scrollbar({x, y, w, h}, orientation, scrollSize, parent) {}

        void setMaxValue(int value) { maxValue_ = value; needsRepaint = true; }
        void setMinValue(int value) { minValue_ = value; needsRepaint = true; }
        void setValue(int value) { value_ = std::max(minValue_, std::min(maxValue_, value)); valueChanged.emit(value); needsRepaint = true; }

        Signal<int> valueChanged;

        EventHandlerState onPaintEvent(const Event*) override;
        EventHandlerState onMouseButtonPressEvent (const Event*) override;
        EventHandlerState onMouseButtonReleaseEvent (const Event*) override;
        EventHandlerState onMouseMoveEvent (const Event*) override;
        
        void update() override;

    private:
        Orientation orientation_;
        Rect scroll_;
        bool needsRepaint = true;
        bool captured_ = false;
        int maxValue_ = 100, minValue_ = 0;
        int value_ = 20;
        void updateScrollRect();

    };
}

#endif /* WIDGETS_SCROLLBAR_HPP */
