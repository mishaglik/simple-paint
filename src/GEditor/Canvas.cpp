#include "Canvas.hpp"
#include "AbstractGL/AImage.hpp"
#include "GEditor.hpp"
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
        surface->clear(aGL::Colors::White);
        if(alphaFiller_ != aGL::NoTexture && alphaFiller_ != aGL::IgnoreTexture)
        {
            surface->drawSprite({}, { sm_->getTexture(alphaFiller_), {0, 0, rect_.w, rect_.h}});
        }

        if(image_ && image_->isCreated())
        {
            imageTexture_->loadFromImage(*image_);
            surface->drawSprite(mgm::asPoint(imageStart_), *imageTexture_);
        }
        needsRepaint_ = false;
        return aGL::Accepted;
    }

    aGL::EventHandlerState Canvas::onMouseButtonPressEvent(const aGL::Event* e)
    {
        if(e->mbed.button == aGL::MouseButton::Left)
        {
            curAction_.point = e->mbed.point;
            curAction_.point -= imageStart_;
            GEditor::app->getCurrentTool()->onMousePress(curAction_);
            mousePressed.emit(curAction_);
            needsRepaint_ = true;
        }
        return aGL::Widget::onMouseButtonPressEvent(e);
    }

    aGL::EventHandlerState Canvas::onMouseButtonReleaseEvent(const aGL::Event* e)
    {
        if(e->mbed.button == aGL::MouseButton::Left)
        {
            curAction_.point = e->mbed.point;
            curAction_.point -= imageStart_;
            GEditor::app->getCurrentTool()->onMouseRelease(curAction_);
            mouseReleased.emit(curAction_);
            needsRepaint_ = true;
        }
        return aGL::Widget::onMouseButtonReleaseEvent(e);
    }

    aGL::EventHandlerState Canvas::onMouseMoveEvent(const aGL::Event* e)
    {
        curAction_.point = e->mmed.point;
        curAction_.point -= imageStart_;
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

        return aGL::Widget::onKeyReleasedEvent(e);
    }

    aGL::EventHandlerState Canvas::onLoseFocusEvent(const aGL::Event*)
    {
        curAction_.ctrl = false;
        curAction_.shift = false;
        return aGL::Accepted;
    }

    void Canvas::moveImage(const aGL::Vec2i& v)
    {
        needsRepaint_ = true;
        imageStart_ += v;
    }

}
