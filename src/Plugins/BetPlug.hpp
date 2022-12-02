#ifndef PLUGINS_BETPLUG_HPP
#define PLUGINS_BETPLUG_HPP
#include "Elpstd/tools.hpp"
#include "Signals.hpp"
#include "Color.hpp"
#include "Vector.hpp"

namespace bp {
    using Point = mgm::Vector2<int64_t>;
    
    using booba::GUID;
    using booba::CanvasEventData;
    using booba::MouseButtonEventData;
    using booba::TimerEventData;

    using booba::MouseButton;
    using booba::init_module;
    using booba::Image;
    using booba::MotionEventData;
    using booba::APPCONTEXT;

    class BTool;
    
    extern const GUID GUID_;

    struct Button
    {
        const uint64_t id_; // Buffer 
        Signal<> clicked;
    };

    struct Scrollbar
    {
        const uint64_t id_;
        int32_t value;
        Signal<int> valueChanged;
    };
    
    struct Canvas : public SignalObject
    {
        const uint64_t id_;
        const uint32_t w_, h_;

        Canvas(int32_t x, int32_t y, int32_t w, int32_t h, BTool* parent);
        Canvas(uint64_t id, uint32_t w, uint32_t h) : id_(id), w_(w), h_(h) {}
        
        virtual ~Canvas() {}
        virtual void onMousePress(const CanvasEventData* )   {}
        virtual void onMouseRelease(const CanvasEventData* ) {}
        virtual void onMouseMove(const CanvasEventData* )    {}
        
        void setPixel (Point pt, Color color);
        void putSprite(Point pt, mgm::Vector2u size, const char* sprite);

        void clear(Color color);
    };

    template<class T>
    class Guard
    {
        T& lock_;
        const T& startVal_, endVal_;
    public:
        Guard(T& lock, const T& startVal, const T& endVal = T{}) : lock_(lock), startVal_(startVal), endVal_(endVal) { lock = startVal; }
        ~Guard() { lock_ = endVal_; }
    };

    class BTool : public booba::Tool, public SignalObject
    {
        mvc::Vector<Button*> buttons_;
        mvc::Vector<Scrollbar*> scrollbars_;

    protected:
        mvc::Vector<Canvas* > canvases_;
        Image* image_ = nullptr;
        bool pressed_ = false;
        uint64_t prevMillis_ = 0;

    public:
        BTool() {} 
        ~BTool() override;

        BTool(const BTool&) = delete;
        BTool& operator=(const BTool&) = delete;
        
        virtual void onMouseMove(const MotionEventData* )         {}
        virtual void onMousePress(const MouseButtonEventData* )   {}
        virtual void onMouseRelease(const MouseButtonEventData* ) {}
        virtual void onMouseLeave() {}
        virtual void onTimerTick(const TimerEventData* ) {}
        virtual void buildSetupWidget() override {}

        void addCanvas(Canvas* canvas) { canvases_.push_back(canvas); }

    protected:
        Button* createButton(int32_t x, int32_t y, uint32_t w, uint32_t h, const char* name);
        bool createLabel(int32_t x, int32_t y, uint32_t w, uint32_t h, const char* name);
        Scrollbar* createScrollbar(int32_t x, int32_t y, uint32_t w, uint32_t h, int32_t maxValue, int32_t startValue);    
        uint64_t createCanvas(int32_t x, int32_t y, int32_t w, int32_t h);
        
    private:
        virtual void apply(Image* image, const booba::Event* event) override;
    };

}
#endif /* PLUGINS_BETPLUG_HPP */
