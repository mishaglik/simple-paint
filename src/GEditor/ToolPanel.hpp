#ifndef GEDITOR_TOOLPANEL_HPP
#define GEDITOR_TOOLPANEL_HPP

#include "GEditor/Tool.hpp"
#include "Widgets/ContainerWidget.hpp"
#include "Widgets/Scrollbar.hpp"
#include "Widgets/Dialog.hpp"
#include "Widgets/Button.hpp"

namespace mge {
    class ToolPanel : public aGL::ContainerWidget
    {
        aGL::Text text_;        
        aGL::ContainerWidget* cropper_ = nullptr, *uberContainer_ = nullptr;
        aGL::Widget* container_ = nullptr;
    public:
        aGL::Scrollbar* xScroll_ = nullptr;
        aGL::Scrollbar* yScroll_ = nullptr;

        aGL::PushButton* outButton_ = nullptr;

        ToolPanel(const aGL::Rect& rect, const char* title, aGL::Widget* parent);

        aGL::EventHandlerState onPaintEvent(const aGL::Event* ) override;
        void afterPaint() const override;
        void onSkinChange() override;
        
        void onToolChange(Tool* tool);
        
        void moveToWindow();
        void onDialogClose(aGL::WWindow* window);

        void hangPluginWidget(aGL::Widget* widget);
        void setPluginWidget(aGL::Widget* widget);
    private:
        void setWidgetX(int x);
        void setWidgetY(int y);
    };

    class ToolDialog : public aGL::Dialog
    {
        aGL::ContainerWidget* container_ = nullptr;
        
    public:
        ToolDialog(aGL::ContainerWidget* container);

        aGL::ContainerWidget* extractContainer();

        aGL::EventHandlerState onPaintEvent(const aGL::Event* e) override;
    };
}

#endif /* GEDITOR_TOOLPANEL_HPP */
