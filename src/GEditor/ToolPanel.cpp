#include "ToolPanel.hpp"
#include "GEditor/GrandDesign.hpp"
#include "Widgets/Decorations.hpp"

namespace mge {

    ToolPanel::ToolPanel(const aGL::Rect& rect, const char* title, aGL::Widget* parent)
        : aGL::ContainerWidget(rect, parent), text_(title, 5, 2)
    {
        text_.setColor(Design::ColorPalete::TextColor);
        text_.setCharacterSize(11);
        text_.setStyle(aGL::Text::Bold);
        cropper_ = new aGL::ContainerWidget({0, Design::LeftPanel::ToolPanel::HEAD.h, 1000, 1000}, this);
        containter_ = new aGL::ContainerWidget({0, 0, rect.w - 10, rect.h -Design::LeftPanel::ToolPanel::HEAD.h - Design::LeftPanel::ToolPanel::FOOT.h }, cropper_);


        xScroll_ = new aGL::Scrollbar(Design::LeftPanel::ToolPanel::FOOT, aGL::Scrollbar::Horizontal, 33, this);
        yScroll_ = new aGL::Scrollbar({rect.w - 10, 16, 10, containter_->getRect().h}, aGL::Scrollbar::Vertical, 33, this);


        xScroll_->setMaxValue(-1000 + containter_->getRect().w);
        yScroll_->setMaxValue(-1000 + containter_->getRect().h);

        xScroll_->valueChanged.connect(this, &ToolPanel::setWidgetX);
        yScroll_->valueChanged.connect(this, &ToolPanel::setWidgetY);
    }

    aGL::EventHandlerState ToolPanel::onPaintEvent(const aGL::Event* e)
    {
        aGL::ContainerWidget::onPaintEvent(e);
        surface->drawRect(Design::LeftPanel::ToolPanel::HEAD, Design::ColorPalete::borderDarkColor);
        surface->drawRect(Design::LeftPanel::ToolPanel::FOOT, Design::ColorPalete::borderDarkColor);
        surface->drawText(text_);
        return aGL::Accepted;
    }

    void ToolPanel::afterPaint() const
    {
        aGL::DecRect(surface).decorate(aGL::Decorations::dBorder, Design::ColorPalete::borderDarkColor, Design::ColorPalete::borderLightColor);
    }

    void ToolPanel::onSkinChange()
    {
        if(sm_)
        {
            text_.setFont(sm_->getFont());
        }
    }

    void ToolPanel::setWidgetX(int x)
    {
        containter_->setPoisition(x, containter_->getRect().y);
    }

    void ToolPanel::setWidgetY(int y)
    {
        containter_->setPoisition(containter_->getRect().x, y);
    }

}
