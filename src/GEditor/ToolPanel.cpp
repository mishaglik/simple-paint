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
    }

    aGL::EventHandlerState ToolPanel::onPaintEvent(const aGL::Event* e)
    {
        surface->drawRect(Design::LeftPanel::ToolPanel::HEAD, Design::ColorPalete::borderDarkColor);
        surface->drawRect(Design::LeftPanel::ToolPanel::FOOT, Design::ColorPalete::borderDarkColor);
        surface->drawText(text_);
        return aGL::ContainerWidget::onPaintEvent(e);
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

}
