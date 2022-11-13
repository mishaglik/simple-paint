#ifndef GEDITOR_CENTRALWIDGET_HPP
#define GEDITOR_CENTRALWIDGET_HPP

#include "GEditor/Canvas.hpp"
#include "Widgets/ContainerWidget.hpp"
#include "Widgets/Scrollbar.hpp"
    
namespace mge {

    class CentralWidget : public aGL::ContainerWidget
    {
        Canvas* canvas_ = nullptr;
        aGL::Scrollbar* xScroll_ = nullptr; 
        aGL::Scrollbar* yScroll_ = nullptr; 
        public:
            CentralWidget(const aGL::Rect& rect, aGL::Widget* parent = nullptr);
    };
}

#endif /* GEDITOR_CENTRALWIDGET_HPP */
