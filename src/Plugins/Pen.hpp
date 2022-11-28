#ifndef PLUGINS_PEN_HPP
#define PLUGINS_PEN_HPP
#include "Interpolate.hpp"
#include "Brushes.hpp"
#include "BetPlug.hpp"
#include "PixArr.hpp"

namespace bp {

    class Pen : public BTool
    {
        Brush::BrushSettings settts_ = {10, 0, 10};
        Brush* brush_;
    protected:
        UsedArr pixarr_;
    public:
        Pen();
        ~Pen() override { delete  brush_; }
        Point prevDrawn_ = {};
        int32_t interval = 10;
        bool keepOpacity = true;

        const char* getTexture() override { return "Pen.png"; } 
        void buildSetupWidget() override;

        void onMousePress  (const MouseButtonEventData* event) override;
        void onMouseRelease(const MouseButtonEventData* event) override;
        void onMouseMove   (const MotionEventData* event) override;
        
        virtual void applyTool(const Brush::BrushPoint& pt);
        virtual void brushDraw(const Point& pt);

    private:
        void usedReset();
        void setBrushSize(int x) {settts_.size = x;}
        void setOpacity  (int x) {settts_.opacity = x;}
        void setInterval (int x) {interval = x;}
    };

bool isOnImage(Image* image, const Point& pt);

}



#endif /* PLUGINS_PEN_HPP */
