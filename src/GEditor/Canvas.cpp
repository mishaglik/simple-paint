#include "Canvas.hpp"
#include "AbstractGL/AImage.hpp"
#include "GEditor.hpp"
#include "GEditor/GrandDesign.hpp"
#include "Tool.hpp"

namespace mge {
    Canvas::Canvas(const aGL::Rect& rect, aGL::Widget* parent)
        : aGL::Widget(rect, parent)
    {
        imageTexture_ = new aGL::Texture;
        image_ = new aGL::Image("Image.jpg");
        curAction_.image = image_;
        if(!image_->isCreated())
        {
            mError << "Failed to open image\n";
        }
    }

    Canvas::~Canvas()
    {
        delete image_;
        delete imageTexture_;
    }


    aGL::EventHandlerState Canvas::onPaintEvent(const aGL::Event*)
    {
        if(!needsRepaint_) return aGL::Accepted;
        surface->clear(Design::ColorPalete::backgroundColor);
        if(alphaFiller_ != aGL::NoTexture && alphaFiller_ != aGL::IgnoreTexture)
        {
            surface->drawSprite(mgm::asPoint(imageStart_), { sm_->getTexture(alphaFiller_), {0, 0, image_->getW(), image_->getH()}});
        }

        if(image_ && image_->isCreated())
        {
            imageTexture_->loadFromImage(*image_);
            surface->drawSprite(mgm::asPoint(imageStart_), *imageTexture_);
        }
        needsRepaint_ = false;
        return aGL::Accepted;
    }

    bool Canvas::isPointOnImage(aGL::Point pt)
    {
        pt -= imageStart_;
        // mInfo << "Contains: "  << mgm::contains({0,0, image_->getW() - 1, image_->getH() - 1}, pt) << mlg::endl;
        return mgm::contains({0,0, image_->getW() - 1, image_->getH() - 1}, pt);
    }


    aGL::EventHandlerState Canvas::onMouseButtonPressEvent(const aGL::Event* e)
    {
        if(!isPointOnImage(e->mbed.point)) return aGL::Dropped;
        if(e->mbed.button == aGL::MouseButton::Left)
        {
            curAction_.point = e->mbed.point;
            curAction_.point -= imageStart_;
            if(!GEditor::app->getCurrentTool()) return aGL::Accepted;
            GEditor::app->getCurrentTool()->onMousePress(curAction_);
            mousePressed.emit(curAction_);
            needsRepaint_ = true;
        }
        return aGL::Widget::onMouseButtonPressEvent(e);
    }

    aGL::EventHandlerState Canvas::onMouseButtonReleaseEvent(const aGL::Event* e)
    {
        if(!isPointOnImage(e->mbed.point)) return aGL::Dropped;
        if(e->mbed.button == aGL::MouseButton::Left)
        {
            curAction_.point = e->mbed.point;
            curAction_.point -= imageStart_;
            if(!GEditor::app->getCurrentTool()) return aGL::Accepted;
            GEditor::app->getCurrentTool()->onMouseRelease(curAction_);
            mouseReleased.emit(curAction_);
            needsRepaint_ = true;
        }
        return aGL::Widget::onMouseButtonReleaseEvent(e);
    }

    aGL::EventHandlerState Canvas::onMouseLeaveEvent(const aGL::Event* e)
    {
        GEditor::app->getCurrentTool()->onMouseLeave(curAction_);
        return aGL::Widget::onMouseLeaveEvent(e);
    }

    void Canvas::update()
    {
        GEditor::app->getCurrentTool()->onTimerEvent(curAction_);
        needsRepaint_ = true;
    }


    aGL::EventHandlerState Canvas::onMouseMoveEvent(const aGL::Event* e)
    {
        if(!isPointOnImage(e->mmed.point)) return aGL::Dropped;
        curAction_.point = e->mmed.point;
        curAction_.point -= imageStart_;
        if(!GEditor::app->getCurrentTool()) return aGL::Accepted;
        GEditor::app->getCurrentTool()->onMouseMove(curAction_);
        mouseMoved.emit(curAction_);
        needsRepaint_ = true;
        return aGL::Accepted;
    }

    void Canvas::onSkinChange()
    {
        if(alphaFiller_ == aGL::NoTexture)
        {

            alphaFiller_ = sm_->findTextureId("AplhaFiller");
            if(alphaFiller_)
            {
                sm_->getTexture(alphaFiller_).setRepeated(true);
            }
        }
        aGL::Widget::onSkinChange();
        needsRepaint_ = true;
    }

    void Canvas::setImageStartX(int x)
    {
        needsRepaint_ = true;
        imageStart_.x = x;
    }

    void Canvas::setImageStartY(int y)
    {
        needsRepaint_ = true;
        imageStart_.y = y;
    }

    aGL::EventHandlerState Canvas::onKeyPressedEvent(const aGL::Event* e)
    {
        if(e->ked.key == aGL::KeyboardKey::LShift)
        {
            curAction_.shift = true;
            return aGL::Accepted;
        }
        
        if(e->ked.key == aGL::KeyboardKey::LControl)
        {
            curAction_.ctrl = true;
            return aGL::Accepted;
        }

        if(e->ked.key == aGL::KeyboardKey::LAlt)
        {
            curAction_.alt = true;
            return aGL::Accepted;
        }

        return aGL::Widget::onKeyPressedEvent(e);
    }

    aGL::EventHandlerState Canvas::onKeyReleasedEvent(const aGL::Event* e)
    {
        if(e->ked.key == aGL::KeyboardKey::LShift)
        {
            curAction_.shift = false;
            return aGL::Accepted;
        }
        
        if(e->ked.key == aGL::KeyboardKey::LControl)
        {
            curAction_.ctrl = false;
            return aGL::Accepted;
        }

         if(e->ked.key == aGL::KeyboardKey::LAlt)
        {
            curAction_.alt = false;
            return aGL::Accepted;
        }

        return aGL::Widget::onKeyReleasedEvent(e);
    }

    aGL::EventHandlerState Canvas::onLoseFocusEvent(const aGL::Event*)
    {
        curAction_.ctrl = false;
        curAction_.shift = false;
        curAction_.alt = false;
        return aGL::Accepted;
    }

    void Canvas::moveImage(const aGL::Vec2i& v)
    {
        needsRepaint_ = true;
        imageStart_ += v;
    }

}
