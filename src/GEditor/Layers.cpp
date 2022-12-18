#include "Layers.hpp"
#include "GEditor/GrandDesign.hpp"
#include "GEditor/GEditor.hpp"
#include "Widgets/Checkbox.hpp"
#include "Widgets/Decorations.hpp"
#include <Widgets/Scrollbar.hpp>
namespace mge {
    LayerManager::LayerManager(aGL::Rect rect, aGL::Widget* parent) :
        aGL::ContainerWidget(rect, parent), name_("Layers", 5, 1)
    {
        yScroll_ = new aGL::Scrollbar({rect.w - 10, 16, 10, 400}, aGL::Scrollbar::Vertical, 33, this);
        yScroll_->setMaxValue(-1000 );
        yScroll_->valueChanged.connect(this, &LayerManager::setScrollY);
        yScroll_->setTexId(aGL::IgnoreTexture);

        cropeer_   = new aGL::ContainerWidget({0, 15, rect_.w - 10, rect.h - 45}, this);
        container_ = new aGL::ContainerWidget({0,  0, rect_.w - 10, 1000}   , cropeer_);

        addButton_ = new aGL::PushButton(" +",   0, rect.h - 30, 70, 30, this);
        dupButton_ = new aGL::PushButton(" =",  70, rect.h - 30, 70, 30, this);
        delButton_ = new aGL::PushButton(" x", 140, rect.h - 30, 70, 30, this);

        addButton_->clicked.connect(this, &LayerManager::createLayer);
        dupButton_->clicked.connect(this, &LayerManager::duplicateLayer);
        delButton_->clicked.connect(this, &LayerManager::deleteLayer);

        name_.setColor(Design::ColorPalete::TextColor);
        name_.setCharacterSize(11);
        name_.setStyle(aGL::Text::Bold);
    }

    aGL::EventHandlerState LayerManager::onPaintEvent(const aGL::Event* event)
    {
        aGL::ContainerWidget::onPaintEvent(event);
        surface->clear(Design::ColorPalete::hollowColor);
        surface->drawRect({0, 0, rect_.w, 15}, Design::ColorPalete::borderDarkColor);
        surface->drawText(name_);
        // surface->drawRect({0, rect_.h - 30, rect_.w, 30}, Design::ColorPalete::ScrollHoleColor);
        return aGL::Accepted;
    }

    void LayerManager::setScrollY(int y)
    {
        container_->setPoisition(0, y);
    }

    void LayerManager::afterPaint() const
    {
        aGL::DecRect(surface).decorate(aGL::Decorations::dBorder, Design::ColorPalete::borderDarkColor, Design::ColorPalete::borderLightColor);
    }

    LayerBar::LayerBar(aGL::Rect rect, uint32_t index, aGL::Widget* parent) :
        aGL::ContainerWidget(rect, parent), text_(""), index_(index)
    {
        text_.setPosition(85, 7);
        text_.setCharacterSize(13);

        visibleToggler_ = new aGL::Checkbox({5,5, 20, 20}, this);
        visibleToggler_->toggled.connect(this, &LayerBar::toggleVisibility);

        pbDn_ = new aGL::PushButton("v", rect.w - 15, 16, 10, 10, this);
        pbDn_->clicked.connect(this, &LayerBar::moveDown);

        pbUp_ = new aGL::PushButton("^", rect.w - 15,  5, 10, 10, this);
        pbUp_->clicked.connect(this, &LayerBar::moveUp);
    }

    void LayerBar::moveUp()
    {
        if(index_ == GEditor::app->layers_.size() - 1) return;
        std::swap(GEditor::app->layers_[index_], GEditor::app->layers_[index_ + 1]);
        update();
    }

    void LayerBar::moveDown()
    {
        if(index_ == 0) return;
        std::swap(GEditor::app->layers_[index_], GEditor::app->layers_[index_ - 1]);
        update();
    }


    void LayerBar::onSkinChange()
    {
        if(sm_)
        {
            text_.setFont(sm_->getFont());
            visibleToggler_->setTexId(sm_->findTextureId("VisibleToggler"));
        }
    }

    void LayerBar::update()
    {
        if(GEditor::app->layers_[index_].isHidden != visibleToggler_->getState())
        {
            // visibleToggler_->toggle();
        }
        if(index_ == 0) pbDn_->hide();
        if(index_ == GEditor::app->layers_.size() - 1) pbUp_->hide();
        else pbUp_->show();
    }


    void LayerBar::toggleVisibility(bool tog)
    {
        GEditor::app->layers_[index_].isHidden = tog;
    }



    aGL::EventHandlerState LayerBar::onPaintEvent(const aGL::Event* event)
    {
        aGL::ContainerWidget::onPaintEvent(event);
        // surface->clear(aGL::Colors::Red);
        text_.setColor(aGL::Colors::Black);

        text_.setString(GEditor::app->layers_[index_].name);
        if(index_ == GEditor::app->selectedLayer_)
        {
            surface->clear(Design::ColorPalete::ScrollHoleColor);
            text_.setColor(Design::ColorPalete::TextColor);
        }
        
        imageTexture_.loadFromImage(*GEditor::app->layers_[index_].image);
        aGL::Sprite sprite(imageTexture_);
        sprite.setScale(35. / GEditor::app->layers_[index_].image->getW(), 24. / GEditor::app->layers_[index_].image->getH());
        surface->drawSprite({40, 3}, sprite);
        surface->drawText(text_);
        return aGL::Accepted;
    }

    aGL::EventHandlerState LayerBar::onMouseButtonPressEvent(const aGL::Event* event)
    {
        aGL::EventHandlerState state = aGL::ContainerWidget::onMouseButtonPressEvent(event);
        if(state != aGL::Accepted && event->mbed.button == aGL::MouseButton::Left)
        {
            state = aGL::Accepted;
            GEditor::app->selectedLayer_ = index_;
        }

        return state;
    }


    void LayerManager::update()
    {
        bool needMove = false;
        while(GEditor::app->layers_.size() > layers_.size())
        {
            layers_.push_back(new LayerBar({0, 0, Design::RightPanel::Layers::LBar::W, Design::RightPanel::Layers::LBar::H}, layers_.size(), container_));
            layers_.back()->onSkinChange();
            needMove = true;
        }

        while(GEditor::app->layers_.size() < layers_.size())
        {
            needMove = true;
            container_->delChild(layers_.back());
            delete layers_.back();
            layers_.pop_back();
        }

        if(needMove)
        {
            for(size_t i = 0; i < layers_.size(); ++i)
            {
                layers_[i]->setPoisition(0, Design::RightPanel::Layers::LBar::H * (layers_.size() - 1 - i));
            }
        }
    }  

    void LayerManager::createLayer()
    {
        GEditor::app->layers_.push_back({ {0, 0, GEditor::app->imageW_, GEditor::app->imageH_}, new aGL::Image(GEditor::app->imageW_, GEditor::app->imageH_, 0), "New layer"});
    }

    void LayerManager::duplicateLayer()
    {
        GEditor::app->layers_.push_back(GEditor::app->layers_[GEditor::app->selectedLayer_]);
        GEditor::app->layers_.back().image = new aGL::Image(GEditor::app->layers_.back().rect.w, GEditor::app->layers_.back().rect.h, 0);
    }

    void LayerManager::deleteLayer()
    {
        if(GEditor::app->layers_.size() <= 1) return;
        for(size_t i = GEditor::app->selectedLayer_; i + 1 < GEditor::app->layers_.size(); ++i)
        {
            std::swap(GEditor::app->layers_[i], GEditor::app->layers_[i+1]);
        }
        delete GEditor::app->layers_.back().image;
        GEditor::app->layers_.pop_back();
        if(GEditor::app->selectedLayer_ == GEditor::app->layers_.size()) GEditor::app->selectedLayer_--;
        // if(GEditor::app->selectedLayer_ == GEditor::app->layers_.size())
    }

    void LayerManager::onSkinChange()
    {
        if(sm_)
        {
            name_.setFont(sm_->getFont());
        }
    }

}
