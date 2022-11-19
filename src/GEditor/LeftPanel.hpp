#ifndef GEDITOR_LEFTPANEL_HPP
#define GEDITOR_LEFTPANEL_HPP

#include "GEditor/ColorSelector.hpp"
#include "GEditor/GrandDesign.hpp"
#include "GEditor/Toolbox.hpp"
#include "Widgets/ContainerWidget.hpp"

namespace mge {

    class LeftPanel : aGL::ContainerWidget
    {
        Toolbox* toolbox_ = nullptr;
        ColorSelector* colSel_ = nullptr;
    public:
        LeftPanel(const aGL::Rect& rect, const mvc::Vector<Tool* >& tools, aGL::Widget* widget = nullptr);

        Toolbox* getToolbox() { return toolbox_; }

        aGL::EventHandlerState onPaintEvent(const aGL::Event* e) override
        {
            surface->clear(Design::ColorPalete::backgroundColor);
            return aGL::ContainerWidget::onPaintEvent(e);
        }
    };
}

#endif /* GEDITOR_LEFTPANEL_HPP */
