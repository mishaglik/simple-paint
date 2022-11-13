#ifndef TOOLS_HPP
#define TOOLS_HPP
/**
 * @file tools.hpp
 * @author First standart commitet.
 * @brief Basic plugin header.
 * @version 0.1.0a
 * @date 2022-11-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <cstdint>
namespace booba { // boot of outstanding best api

#ifdef PLUGIN
    /**
     * @brief We require you to implement this;
     * 
     */
    extern "C" void init_module();
#endif

    enum class EventType
    {
        NoEvent        = 0,
        MouseMoved     = 1,
        MousePressed   = 2,
        MouseReleased  = 3,

        ButtonClicked   = 4,
        ScrollbarMoved  = 5,
        CanvasMPressed  = 6,
        CanvasMReleased = 7,
        CanvasMMoved    = 8,

    };

    enum class MouseButton
    {
        Left,
        Right
    };

    struct MotionEventData
    {
        int32_t x, y;
        int32_t rel_x, rel_y;
    };

    struct MouseButtonEventData
    {
        int32_t x, y;
        MouseButton button; 
        bool shift, alt, ctrl;
    };

    struct ButtonClickedEventData
    {
        uint64_t id; 
    };

    struct ScrollMovedEventData
    {
        uint64_t id; 
        int32_t value;
    };


    struct CanvasEventData
    {
        uint64_t id;
        int32_t x, y; 
    };

    class Event
    {
    public:
        EventType type;
        union 
        {
            MotionEventData motion;
            MouseButtonEventData mbedata;
            ButtonClickedEventData bcedata;
            ScrollMovedEventData smedata;
            CanvasEventData cedata;
        } Oleg; //Object loading event group.
    };


    class Image
    {
    public:
        virtual uint32_t getH()     = 0;
        virtual uint32_t getX()     = 0;
        virtual uint32_t getPixel(int32_t x, int32_t y) = 0;
        virtual void putPixel(uint32_t x, uint32_t y, uint32_t color) = 0;        
        virtual uint32_t& operator()(uint32_t x, uint32_t y) = 0;
        virtual const uint32_t& operator()(uint32_t x, uint32_t y) const = 0;
    protected:
        virtual ~Image() = 0;
    };

    struct ApplicationContext
    {
        uint32_t fgColor, bgColor;
    };

    class Tool
    {
    public:
        virtual void apply(Image* image, const Event* event) = 0;
        virtual ~Tool() = 0;
        virtual const char* getTexture() = 0; 
        virtual void buildSetupWidget() = 0;
    };

    // This functions will be given to you;

    extern "C" uint64_t createButton   (int32_t x, int32_t y, uint32_t w, uint32_t h, const char*);
    extern "C" uint64_t createLabel    (int32_t x, int32_t y, uint32_t w, uint32_t h, const char*);
    extern "C" uint64_t createScrollbar(int32_t x, int32_t y, uint32_t w, uint32_t h);
    
    extern "C" uint64_t createCanvas(int32_t x, int32_t y, int32_t w, int32_t h);
    extern "C" uint64_t putPixel (uint64_t canvas, int32_t x, int32_t y, uint32_t color);
    extern "C" uint64_t putSprite(uint64_t canvas, int32_t x, int32_t y, uint32_t w, uint32_t h, const char* texture);
    
    extern "C" void addTool(Tool* tool);
    extern "C" void addFilter(Tool* tool);

    extern ApplicationContext* APPCONTEXT;
}

#endif /* TOOLS_HPP */
