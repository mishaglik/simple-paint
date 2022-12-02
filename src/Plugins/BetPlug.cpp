#include "BetPlug.hpp"
#include <cassert>
#include <iostream>

namespace bp
{
    Canvas::Canvas(int32_t x, int32_t y, int32_t w, int32_t h, BTool* parent) :
        id_(booba::createCanvas(x, y, w, h)), w_(w), h_(h)
    {
        parent->addCanvas(this);
    }

    void Canvas::setPixel (Point pt, Color color)
    {
        if(pt.x < 0 || pt.x >= w_) return;
        if(pt.y < 0 || pt.y >= h_) return;
        booba::setPixel(id_, pt.x, pt.y, color);
    }

    void Canvas::clear(Color color)
    {
        // for(int x = 0; x < w_; ++x)
        //     for(int y = 0; y < h_; ++y)
        //         booba::setPixel(id_, x, y, color);
        booba::cleanCanvas(id_, color);
    }


    void Canvas::putSprite(Point pt, mgm::Vector2u size, const char* sprite)
    {
        if(pt.x < 0 || pt.x >= w_) return;
        if(pt.y < 0 || pt.y >= h_) return;
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
        buttons_.push_back(new Button{id, {}}); //FIXME: Other allocation system.
        return buttons_.back();
    }

    bool BTool::createLabel(int32_t x, int32_t y, uint32_t w, uint32_t h, const char* name)
    {
        uint64_t id = booba::createLabel(x, y, w, h, name);
        return id;
    }

    Scrollbar* BTool::createScrollbar(int32_t x, int32_t y, uint32_t w, uint32_t h, int32_t maxValue, int32_t startValue)
    {
        uint64_t id = booba::createSlider(x, y, w, h, 0, maxValue, startValue);
        if(!id) return nullptr;
        scrollbars_.push_back(new Scrollbar{id, startValue, {}});
        // scrollbars_.resize(scrollbars_.size() + 1); //WTF ?
        // scrollbars_.back().id_ = id;
        return scrollbars_.back();
    }

    uint64_t BTool::createCanvas(int32_t x, int32_t y, int32_t w, int32_t h)
    {
        uint64_t id = booba::createCanvas(x, y, w, h);
        assert(id);
        return id;
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

        case booba::EventType::SliderMoved:
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
            {
                if(canvas->id_ == event->Oleg.cedata.id)
                {
                    canvas->onMousePress(&event->Oleg.cedata);
                    break;
                }
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

extern "C" booba::GUID booba::getGUID() { return bp::GUID_; }
