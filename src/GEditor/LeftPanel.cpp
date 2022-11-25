#include "LeftPanel.hpp"
#include "GEditor/ToolPanel.hpp"
#include "GrandDesign.hpp"

namespace mge {

    LeftPanel::LeftPanel(const aGL::Rect& rect,const mvc::Vector<Tool* >& tools, aGL::Widget* widget) :
        aGL::ContainerWidget(rect, widget)
    {
        using namespace Design::LeftPanel::Toolbox;
        toolbox_ = new Toolbox(RECT, ToolboxButton::W, tools, this);

        colSel_ = new ColorSelector(Design::LeftPanel::ColorSelector::RECT, this);

        toolPanel_ = new ToolPanel(Design::LeftPanel::ToolPanel::RECT, "Tool", this);
    }


}
