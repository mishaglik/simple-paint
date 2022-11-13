#include "CentralWidget.hpp"
#include "GrandDesign.hpp"
#include <Widgets/Decorations.hpp>

namespace mge {
    CentralWidget::CentralWidget(const aGL::Rect& rect, aGL::Widget* parent)
        : aGL::ContainerWidget(rect, parent)
    {
        using namespace Design::MainWidget;
        canvas_  = new Canvas(CanvasD::RECT, this);

        xScroll_ = new aGL::Scrollbar(XScrollbar::RECT, aGL::Scrollbar::Horizontal, XScrollbar::ScrollSize, this);
        xScroll_->setMaxValue(-100);
        xScroll_->setMinValue(100);
        xScroll_->setTexId(XScrollbar::TEXNAME);
        xScroll_->valueChanged.connect(canvas_, &Canvas::setImageStartX);

        yScroll_ = new aGL::Scrollbar(YScrollbar::RECT, aGL::Scrollbar::Vertical,   YScrollbar::ScrollSize, this);
        yScroll_->setMaxValue(-100);
        yScroll_->setMinValue(100);
        yScroll_->setTexId(YScrollbar::TEXNAME);
        yScroll_->valueChanged.connect(canvas_, &Canvas::setImageStartY);
    }

    void CentralWidget::afterPaint() const
    {
        aGL::DecRect(surface).decorate(aGL::Decorations::dBorder, Design::ColorPalete::borderDarkColor, Design::ColorPalete::borderLightColor);
    }

}
