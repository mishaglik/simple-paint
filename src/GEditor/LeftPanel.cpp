#include "LeftPanel.hpp"
#include "GrandDesign.hpp"

namespace mge {

    LeftPanel::LeftPanel(const aGL::Rect& rect,const mvc::Vector<Tool* >& tools, aGL::Widget* widget) :
        aGL::ContainerWidget(rect, widget)
    {
        using namespace Design::LeftPanel::Toolbox;
        toolbox_ = new Toolbox(RECT, ToolboxButton::W, tools, this);
    }


}
