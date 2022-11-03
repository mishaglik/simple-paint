#ifndef GEDITOR_TOOLBOX_HPP
#define GEDITOR_TOOLBOX_HPP

#include "GEditor/Tool.hpp"
#include "Widgets/ContainerWidget.hpp"
#include "Widgets/Gui.hpp"

namespace mge {
    class Toolbox : public aGL::ContainerWidget
    {
    public:
        Toolbox(const aGL::Rect& rect, const uint32_t bSize, aGL::Widget* parent = nullptr);
        class ToolboxButton;
        void addTool(Tool* tool);
        Tool* getSelectedTool() const;
    private:
        ToolboxButton* selected_ = nullptr;
        uint32_t buttonCnt_  = 0;
        uint32_t buttonSize_ = 0;
        void selectTool(ToolboxButton* button);
    };


    class Toolbox::ToolboxButton : public aGL::AbstractButton
    {
        Tool* tool_;
        bool isSelected_ = false;
    public:
        ToolboxButton(const aGL::Rect& rect, Tool* tool, aGL::Widget* parent = nullptr);
        ~ToolboxButton() override;

        Tool* getTool() const;
        aGL::Signal<ToolboxButton*> chosen;
        void select();
        void disselect();

        aGL::EventHandlerState onPaintEvent(const aGL::Event*) override;

    private:
        void onSkinChange() override;
    };
}

#endif /* GEDITOR_TOOLBOX_HPP */
