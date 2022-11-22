#include "BetPlug.hpp"

namespace bp
{
    void Canvas::putPixel (Point pt, Color color)
    {
        booba::putPixel(id_, pt.x, pt.y, color);
    }

    void Canvas::putSprite(Point pt, mgm::Vector2u size, const char* sprite)
    {
        booba::putSprite(id_, pt.x, pt.y, size.x, size.y, sprite);
    }

    BTool::~BTool()
    {
        for (Canvas* canvas : canvases_) {
            delete canvas;
        }
        for(auto bt : buttons_) delete bt;
        for(auto sb : scrollbars_) delete sb;
    }

    Button* BTool::createButton(int32_t x, int32_t y, uint32_t w, uint32_t h, const char* name)
    {
        uint64_t id = booba::createButton(x, y, w, h, name);
        if(!id) return nullptr;
        buttons_.push_back(new Button{id, {}}); //WTF ?
        // buttons_.resize(buttons_.size() + 1); //WTF ?
        // buttons_.back().id_ = id;
        return buttons_.back();
    }

    bool BTool::createLabel(int32_t x, int32_t y, uint32_t w, uint32_t h, const char* name)
    {
        uint64_t id = booba::createLabel(x, y, w, h, name);
        return id;
    }

    Scrollbar* BTool::createScrollbar(int32_t x, int32_t y, uint32_t w, uint32_t h, int32_t maxValue, int32_t startValue)
    {
        uint64_t id = booba::createScrollbar(x, y, w, h, maxValue, startValue);
        if(!id) return nullptr;
        scrollbars_.push_back(new Scrollbar{id, startValue, {}});
        // scrollbars_.resize(scrollbars_.size() + 1); //WTF ?
        // scrollbars_.back().id_ = id;
        return scrollbars_.back();
    }

    uint64_t BTool::createCanvas(int32_t x, int32_t y, int32_t w, int32_t h)
    {
        return booba::createCanvas(x, y, w, h);
    }

    void BTool::apply(Image* image, const booba::Event* event)
    {
        Guard<Image* > imgGuard(image_, image, nullptr);
        switch (event->type) {
        case booba::EventType::MouseMoved:
            onMouseMove(&event->Oleg.motion);
        break;
        
        case booba::EventType::MousePressed:
            pressed_ = true;
            onMousePress(&event->Oleg.mbedata);
        break;
        
        case booba::EventType::MouseReleased:
            pressed_ = false;
            onMouseRelease(&event->Oleg.mbedata);
        break;

        case booba::EventType::ButtonClicked:
            for(Button* button : buttons_)
                if(button->id_ == event->Oleg.bcedata.id)
                {
                    button->clicked.emit();
                    break;
                }
        break;

        case booba::EventType::ScrollbarMoved:
            for(Scrollbar* scroll : scrollbars_)
                if(scroll->id_ == event->Oleg.smedata.id)
                {
                    scroll->value = event->Oleg.smedata.value;
                    scroll->valueChanged.emit(event->Oleg.smedata.value);
                    break;
                }
        break;

        case booba::EventType::CanvasMPressed:
            for(Canvas* canvas : canvases_)
                if(canvas->id_ == event->Oleg.cedata.id)
                {
                    canvas->onMousePress(&event->Oleg.cedata);
                    break;
                }
        break;

        case booba::EventType::CanvasMReleased:
        for(Canvas* canvas : canvases_)
                if(canvas->id_ == event->Oleg.cedata.id)
                {
                    canvas->onMouseRelease(&event->Oleg.cedata);
                    break;
                }
        break;

        case booba::EventType::CanvasMMoved:
        for(Canvas* canvas : canvases_)
                if(canvas->id_ == event->Oleg.cedata.id)
                {
                    canvas->onMouseMove(&event->Oleg.cedata);
                    break;
                }
        break;

        case booba::EventType::NoEvent:
          break;
        }
    }

}
