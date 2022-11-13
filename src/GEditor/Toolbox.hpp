#ifndef GEDITOR_TOOLBOX_HPP
#define GEDITOR_TOOLBOX_HPP

#include "GEditor/Tool.hpp"
#include "Widgets/ContainerWidget.hpp"
#include "Widgets/Gui.hpp"

namespace mge {
    class Toolbox : public aGL::ContainerWidget
    {
        const mvc::Vector<Tool* >& tools_;
    public:
        Toolbox(const aGL::Rect& rect, const uint32_t bSize, const mvc::Vector<Tool* >& tools_, aGL::Widget* parent = nullptr);
        class ToolboxButton;
        Tool* getSelectedTool() const;
        aGL::Signal<Tool* > selectedChanged;
        void select(Tool* tool);
    private:
        ToolboxButton* selected_ = nullptr;
        mvc::Vector<ToolboxButton* > buttons_;
        uint32_t buttonCnt_  = 0;
        uint32_t buttonSize_ = 0;
        void addButton();
        void deleteButton();
        void selectTool(ToolboxButton* button);

        void update() override;
    };


    class Toolbox::ToolboxButton : public aGL::AbstractButton
    {
        const mvc::Vector<Tool* >& tools_;      // May be better tool**. UPD: No. Vector realloc will break it;
        const size_t index_;
        bool isSelected_ = false;
    public:
        ToolboxButton(const aGL::Rect& rect, const mvc::Vector<Tool* >& tools, size_t index, aGL::Widget* parent);

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
