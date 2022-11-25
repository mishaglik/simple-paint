#include "ToolPanel.hpp"
#include "GEditor/GrandDesign.hpp"
#include "GEditor/GEditor.hpp"
#include "Widgets/Decorations.hpp"

namespace mge {

    ToolPanel::ToolPanel(const aGL::Rect& rect, const char* title, aGL::Widget* parent)
        : aGL::ContainerWidget(rect, parent), text_(title, 5, 2)
    {
        text_.setColor(Design::ColorPalete::TextColor);
        text_.setCharacterSize(11);
        text_.setStyle(aGL::Text::Bold);
        cropper_ = new aGL::ContainerWidget({0, 0, rect.w - 10, rect.h -Design::LeftPanel::ToolPanel::HEAD.h - Design::LeftPanel::ToolPanel::FOOT.h }, this);
        uberContainer_ = new aGL::ContainerWidget({0, 0, 1000, 1000}, nullptr, cropper_);
        // containter_ = new aGL::ContainerWidget({0, 0, 1000, 1000}, uberContainer_);


        xScroll_ = new aGL::Scrollbar(Design::LeftPanel::ToolPanel::FOOT, aGL::Scrollbar::Horizontal, 33, this);
        yScroll_ = new aGL::Scrollbar({rect.w - 10, 16, 10, cropper_->getRect().h}, aGL::Scrollbar::Vertical, 33, this);

        xScroll_->setMaxValue(-1000 + cropper_->getRect().w);
        yScroll_->setMaxValue(-1000 + cropper_->getRect().h);

        xScroll_->valueChanged.connect(this, &ToolPanel::setWidgetX);
        yScroll_->valueChanged.connect(this, &ToolPanel::setWidgetY);

        xScroll_->setTexId(aGL::IgnoreTexture);
        yScroll_->setTexId(aGL::IgnoreTexture);

        outButton_ = new aGL::PushButton("v", rect_.w - 15, 0, 15, 20, this);
        outButton_->clicked.connect(this, &ToolPanel::moveToWindow);

        GEditor::app->toolChanged.connect(this, &ToolPanel::onToolChange);
    }

    void ToolPanel::hangPluginWidget(aGL::Widget* widget)
    {
        widget->setParent(uberContainer_);
    }

    void ToolPanel::setPluginWidget(aGL::Widget* widget)
    {
        // if(container_) container_->hide();
        container_ = widget;

        if(widget)
        { 
            if(container_->getParent() != uberContainer_)
            {
                mInfo << "Hanging\n";
                container_->setParent(uberContainer_);
            }
            // container_->show();
        }
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

    void ToolPanel::onToolChange(Tool *tool)
    {
        setPluginWidget(tool->getPanel());
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
        container_->setPoisition(x, container_->getRect().y);
    }

    void ToolPanel::setWidgetY(int y)
    {
        container_->setPoisition(container_->getRect().x, y);
    }

    ToolDialog::ToolDialog(aGL::ContainerWidget* container) :
        aGL::Dialog(400, 300, "Toolbar"), container_(container)
    {
        container_->setParent(this);
        backgroundColor_ = Design::ColorPalete::backgroundColor;
    }

    aGL::ContainerWidget* ToolDialog::extractContainer()
    {
        if(!container_) throw "Bad usage of toolDialog";
        container_->setParent(nullptr);
        aGL::ContainerWidget* w = container_;
        container_ = nullptr;
        return w;
    }

    void ToolPanel::moveToWindow()
    {
        if(!uberContainer_) return;

        ToolDialog* td = new ToolDialog(uberContainer_);
        // uberContainer_ = nullptr;
        
        td->quitedP.connect(this, &ToolPanel::onDialogClose);

        outButton_->hide();
    }

    void ToolPanel::onDialogClose(aGL::WWindow* window)
    {
        if(ToolDialog* td = dynamic_cast<ToolDialog*>(window))
        {
            mAssert(uberContainer_ == td->extractContainer());
            uberContainer_->setParent(cropper_);
            // mInfo << uberContainer_ << '\n';
        }
        else throw "Bad dialog close";
        
        outButton_->show();
    }

    aGL::EventHandlerState ToolDialog::onPaintEvent(const aGL::Event* e)
    {
        // clear(Design::ColorPalete::backgroundColor);
        return aGL::Dialog::onPaintEvent(e);
    }

}
