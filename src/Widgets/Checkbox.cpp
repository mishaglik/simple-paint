#include "Checkbox.hpp"

namespace aGL {
    Checkbox::Checkbox(aGL::Rect rect, aGL::Widget* parent) :
        aGL::AbstractButton(rect, true, parent)
    {

    }

    EventHandlerState Checkbox::onPaintEvent(const aGL::Event* event)
    {
        surface->clear(0);

        if(sm_ && texId_ != NoTexture && texId_ != IgnoreTexture)
        {
            surface->drawSprite({}, Sprite(sm_->getTexture(texId_), {state_ ? rect_.w : 0, 0, rect_.w, rect_.h}));
        }
        else
        {
            surface->clear(state_ ? Colors::Red : Colors::Green);
        }
        return Accepted;
    }

}
