#include "Widget.hpp"
#include "SkinManager.hpp"
#include <typeinfo>
#include <cxxabi.h>
namespace aGL {

    void Widget::resize(uint32_t w, uint32_t h)
    {
        if(w > maxW_ || h > maxH_)
        {
            MLG_UIMPLEMENTED
            return;
        }

        rect_.w = w;
        rect_.h = h;
        sprite_.setTextureRect({0,0,w,h});
        resized.emit(w,h);
    }

    void Widget::resize(const mgm::Vector2u& v)
    {
        resize(v.x, v.y);
    }

    void Widget::render(const Window& window) const 
    {
        render(static_cast<const Surface* >(&window));
    }

    void Widget::render(const Surface* surf) const 
    {
        if(hidden_) return;
        const Surface* rSurface = surface ? surface : surf;
        for(Widget* child : childen_) child->render(rSurface);
        afterPaint();
        if(RenderSurface* rs = dynamic_cast<RenderSurface*>(surface))
        {
            rs->update();
            Point pt = rect_.getCornerLL();
            surf->drawSprite(pt, sprite_);
        }
    }

    Widget& Widget::setSkinManager(SkinManager* sm)
    {
        sm_ = sm;
        onSkinChange();
        for(Widget* child : childen_)
        {
            child->setSkinManager(sm);
        }
        return *this;
    }

    void Widget::onSkinChange()
    {
        if(sm_ != nullptr && texId_ == 0)
        {
            if(texName_ != nullptr)
            {
                texId_ = sm_->findTextureId(texName_);
            }
            else
            {
                char* name = nullptr;
                size_t len = 0;
                int res = 0;
                const char* thename = typeid(*this).name();
                name = abi::__cxa_demangle(thename, name, &len, &res);
                if(res || !name)
                {
                    mError << "Error: demangling returned " << res << mlg::endl;
                    return;
                }
                for(char* c = name; *c; c++) if(*c == ':') *c = '_';

                texId_ = sm_->findTextureId(name);
                free(name);
            }
        }
    }


    void Widget::setTexId(const char* name) 
    {
        texId_ = 0;
        texName_ = name;
        if(!sm_) return;
        texId_ = sm_->findTextureId(name);
    }

    Widget& Widget::setEventManager(EventManager* em) 
    {
        if(evMgr_ != nullptr || em == nullptr) 
        {
            MLG_UIMPLEMENTED //TODO: Swap logic.
            return *this;
        }
        evMgr_ = em;
        evMgr_->subscribe(this);
        return *this;
    }

    void Widget::addChild(Widget* child)
    {
        mAssert(child != this);
        childen_.push_back(child);
        child->setEventManager(evMgr_);
        if(sm_) child->setSkinManager(sm_);
    }

    void Widget::delChild(Widget* child)
    {
        for(size_t i = 0; i < childen_.size(); ++i)
        {
            if(childen_[i] == child) childen_[i] = nullptr;
        }
    }


    void Widget::setPoisition(uint32_t x, uint32_t y)
    {
        rect_.x = x;
        rect_.y = y;
    }

    void Widget::move(uint32_t x, uint32_t y)
    {
        rect_.x += x;
        rect_.y += y;
    }

    EventHandlerState Widget::onPaintEvent(const Event*  )
    {
        if(Surface* s = dynamic_cast<Surface*>(surface))
        {
            s->clear(0);
        }
        return Accepted;
    }

}
