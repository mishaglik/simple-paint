#ifndef GEDITOR_TOOLPANEL_HPP
#define GEDITOR_TOOLPANEL_HPP

#include "Widgets/ContainerWidget.hpp"

namespace mge {
    class ToolPanel : public aGL::ContainerWidget
    {
        aGL::Text text_;        
    public:
        aGL::ContainerWidget* containter = nullptr;

        ToolPanel(const aGL::Rect& rect, const char* title, aGL::Widget* parent);

        aGL::EventHandlerState onPaintEvent(const aGL::Event* ) override;
        void afterPaint() const override;
        void onSkinChange() override;
    };
}

#endif /* GEDITOR_TOOLPANEL_HPP */
