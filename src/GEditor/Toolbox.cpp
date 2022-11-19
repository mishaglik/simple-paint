#include "Toolbox.hpp"
#include "GEditor.hpp"
#include "GrandDesign.hpp"

namespace mge {
    Toolbox::Toolbox(const aGL::Rect& rect, const uint32_t bSize, const mvc::Vector<Tool* >& tools, aGL::Widget* parent) :
        aGL::ContainerWidget(rect, parent), tools_(tools), buttonSize_(bSize)
    {
        aGL::connect(GEditor::app, &GEditor::toolChanged, this, &Toolbox::select);
        aGL::connect(this, &Toolbox::selectedChanged, GEditor::app, &GEditor::setCurrentTool);
    }

    void Toolbox::addButton()
    {
        ToolboxButton* button = new ToolboxButton({(buttonCnt_ % 4) * buttonSize_, (buttonCnt_ / 4) * buttonSize_ , buttonSize_, buttonSize_}, 
                                                        tools_, buttonCnt_, this);
        tools_[buttonCnt_]->createPanel(parent_, Design::LeftPanel::ToolPanel::RECT);
        tools_[buttonCnt_]->getPanel()->hide();
        button->chosen.connect(this, &Toolbox::selectTool);
        if(selected_ == nullptr) button->select();
        buttonCnt_++;
    }

    void Toolbox::select(Tool* tool)
    {
        if(selected_ && selected_->getTool() == tool) return;
        for(ToolboxButton* button : buttons_)
        {
            if(button->getTool() == tool)
            {
                if(selected_ == button) return;
                if(selected_) selected_->disselect();
                selected_ = button;
                selected_->select();
            }
        }
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
        selectedChanged.emit(selected_->getTool());
    }

    Toolbox::ToolboxButton::ToolboxButton(const aGL::Rect& rect, const mvc::Vector<Tool* >& tools, size_t index, aGL::Widget* parent) : 
        aGL::AbstractButton(rect, false, parent), tools_(tools), index_(index)
    {
        clicked.connect(this, &ToolboxButton::select);
        onSkinChange();
    }

    Tool* Toolbox::ToolboxButton::getTool() const
    {
        return tools_[index_];
    }

    void Toolbox::update()
    {
        if(tools_.size() < buttonCnt_) 
        {
            MLG_UIMPLEMENTED
            return;
        }
        
        while (tools_.size() > buttonCnt_) {
            addButton();
        }
    }
    

    aGL::EventHandlerState Toolbox::ToolboxButton::onPaintEvent(const aGL::Event*)
    {
        surface->clear(GEditor::app->context.foregroundColor);
        if(skinned())
        {
            surface->drawSprite({}, {sm_->getTexture(texId_), {isSelected_ ? rect_.w : 0u, 0u, rect_.w, rect_.h}});
            // if(isSelected_) surface->drawRect({0, 0, rect_.w, rect_.h}, 0x00000080);
            if(hovered_) surface->drawRect({0, 0, rect_.w, rect_.h}, 0x00000040);
        } else {
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
        Tool* tool = tools_[index_];
        mAssert(tool);
        if(texId_ == aGL::NoTexture && sm_)
        {
            texId_ = sm_->loadTexture(tool->getTexture());
            mInfo << "Tex found: " << texId_ << '\n';
        }
        needsRepaint_ = true;
    }

    void Toolbox::ToolboxButton::select()
    {
        tools_[index_]->getPanel()->show();
        isSelected_ = true;
        chosen.emit(this);
        needsRepaint_ = true;
    }

    void Toolbox::ToolboxButton::disselect()
    {
        tools_[index_]->getPanel()->hide();
        isSelected_ = false;
        needsRepaint_ = true;
    }
}
