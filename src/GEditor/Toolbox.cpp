#include "Toolbox.hpp"

namespace mge {
    Toolbox::Toolbox(const aGL::Rect& rect, const uint32_t bSize, aGL::Widget* parent) :
        aGL::ContainerWidget(rect, parent), buttonSize_(bSize)
    {

    }

    void Toolbox::addTool(Tool* tool)
    {
        ToolboxButton* button = new ToolboxButton({(buttonCnt_ % 4) * buttonSize_, (buttonCnt_ / 4) * buttonSize_ , buttonSize_, buttonSize_}, tool, this);
        button->chosen.connect(this, &Toolbox::selectTool);
        if(selected_ == nullptr) button->select();
        buttonCnt_++;
    }

    Tool* Toolbox::getSelectedTool() const
    {
        if(selected_ == nullptr) return nullptr;
        return selected_->getTool();
    }

    void Toolbox::selectTool(ToolboxButton* button)
    {
        if(selected_ == button) return;
        if(selected_) selected_->disselect();
        selected_ = button;
    }

    Toolbox::ToolboxButton::ToolboxButton(const aGL::Rect& rect, Tool* tool, aGL::Widget* parent) : 
        aGL::AbstractButton(rect, false, parent), tool_(tool)
    {
        clicked.connect(this, &ToolboxButton::select);
    }

    Toolbox::ToolboxButton::~ToolboxButton()
    {
        delete tool_;
    }

    Tool* Toolbox::ToolboxButton::getTool() const
    {
        return tool_;
    }

    aGL::EventHandlerState Toolbox::ToolboxButton::onPaintEvent(const aGL::Event*)
    {
        if(skinned())
        {
            surface->drawSprite({}, sm_->getTexture(texId_));
            if(isSelected_) surface->drawRect({0, 0, rect_.w, rect_.h}, 0x00000080);
            if(hovered_) surface->drawRect({0, 0, rect_.w, rect_.h}, 0x00000040);
        } else {
            surface->clear(aGL::Colors::White);
            if(isSelected_)
                surface->clear(aGL::Colors::Gray);
            else if (hovered_)
                surface->clear(aGL::Colors::LGray);
        }

        needsRepaint_ = false;
        return aGL::Accepted;
    }

    void Toolbox::ToolboxButton::onSkinChange()
    {
        if(texId_ == aGL::NoTexture && sm_)
        {
            texId_ = sm_->findTextureId(tool_->getSkinName());
        }
        needsRepaint_ = true;
    }

    void Toolbox::ToolboxButton::select()
    {
        isSelected_ = true;
        chosen.emit(this);
        needsRepaint_ = true;
    }

    void Toolbox::ToolboxButton::disselect()
    {
        isSelected_ = false;
        needsRepaint_ = true;
    }
}
