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

    void Pen::buildSetupWidget()
    {
        createButton(5, 0, 100, 20, "Hello, button");
        createScrollbar(5, 40, 100, 20, 100, 0);
        uint64_t canvId = createCanvas(5, 80, 100, 20);
        for(uint32_t x = 0; x < 100; ++x)
            for(uint32_t y = 0; y < 20; ++y)
                putPixel(canvId, x, y, 256 * 256 * 2 * x + 256 * 10 * y + 255);
        putSprite(canvId, 0, 10, 100, 10, "Button.png");
    }
}

namespace booba {
    extern "C" void init_module()
    {
        addTool(new basa::Pen);
    }
}
