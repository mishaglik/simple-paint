#ifndef GEDITOR_TOOLPANEL_HPP
#define GEDITOR_TOOLPANEL_HPP

#include "Widgets/ContainerWidget.hpp"
#include "Widgets/Scrollbar.hpp"

namespace mge {

    class ToolPanel : public aGL::ContainerWidget
    {
        aGL::Text text_;        
    public:
        aGL::ContainerWidget* cropper_ = nullptr, *containter_ = nullptr;
        aGL::Scrollbar* xScroll_ = nullptr;
        aGL::Scrollbar* yScroll_ = nullptr;

        ToolPanel(const aGL::Rect& rect, const char* title, aGL::Widget* parent);

        aGL::EventHandlerState onPaintEvent(const aGL::Event* ) override;
        void afterPaint() const override;
        void onSkinChange() override;
    private:
        void setWidgetX(int x);
        void setWidgetY(int y);
    };
}

#endif /* GEDITOR_TOOLPANEL_HPP */
