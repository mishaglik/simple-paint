#include "Widget.hpp"
#include "SkinManager.hpp"
#include <typeinfo>
#include <cxxabi.h>
namespace aGL {

    void Widget::resize(uint32_t w, uint32_t h)
    {
        if(w > rect_.w || h > rect_.h)
        {
            MLG_UIMPLEMENTED
            return;
        }

        rect_.w = w;
        rect_.h = h;
        sprite_.setTextureRect({0,0,w,h});
    }

    void Widget::resize(const mgm::Vector2u& v)
    {
        resize(v.x, v.y);
    }

    void Widget::render(const Window& window) const 
    {
        render(static_cast<const Surface*>(&window));
    }

    void Widget::render(const Surface* surf) const 
    {
        if(hidden_) return;
        const Surface* rSurface = surface ? surface : surf;
        for(Widget* child : childen_) child->render(rSurface);

        if(RenderSurface* rs = dynamic_cast<RenderSurface*>(surface)){
            rs->update();
            // sprite_ = Sprite(rs->getTexture());
            surf->drawSprite(rect_.getCornerLL(), sprite_);
        }
    }

    Widget& Widget::setSkinManager(const SkinManager* sm)
    {
        sm_ = sm;
        texId_ = 0;
        if(sm_ != nullptr)
        {
            char* name = nullptr;
            size_t len = 0;
            int res = 0;
            const char* thename = typeid(*this).name();
            name = abi::__cxa_demangle(thename, name, &len, &res);
            if(res || !name)
            {
                mError << "Error: demangling returned " << res << mlg::endl;
                return *this;
            }
            for(char* c = name; *c; c++) if(*c == ':') *c = '_';

            texId_ = sm_->findTextureId(name);
            free(name);
        }
        return *this;
    }

    Widget& Widget::setEventManager(EventManager* em) {
        if(evMgr_ != nullptr || em == nullptr) {
            MLG_UIMPLEMENTED //TODO: Swap logic.
            return *this;
        }
        evMgr_ = em;
        evMgr_->subscribe(this);
        return *this;
    }

    void Widget::addChild(Widget* child) {
        assert(child != this);
        childen_.push_back(child);
        child->setEventManager(evMgr_);
    }
}
