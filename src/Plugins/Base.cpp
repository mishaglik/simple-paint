#include "Base.hpp"
#include <cstdio>

namespace basa {
    void Pen::apply(Image* image, const Event* event)
    {
        if(event->type == booba::EventType::MousePressed)
        {
            image->putPixel(event->Oleg.mbedata.x, event->Oleg.mbedata.y, APPCONTEXT->fgColor);
        }
    }
}

namespace booba {
    extern "C" void init_module()
    {
        addTool(new basa::Pen);
    }
}
