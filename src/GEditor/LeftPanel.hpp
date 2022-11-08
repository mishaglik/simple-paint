#ifndef GEDITOR_LEFTPANEL_HPP
#define GEDITOR_LEFTPANEL_HPP

#include "GEditor/Toolbox.hpp"
#include "Widgets/ContainerWidget.hpp"

namespace mge {

    class LeftPanel : aGL::ContainerWidget
    {
        Toolbox* toolbox_ = nullptr;
    public:
        LeftPanel(const aGL::Rect& rect, aGL::Widget* widget = nullptr);

        Toolbox* getToolbox() { return toolbox_; }
    };
}

#endif /* GEDITOR_LEFTPANEL_HPP */
