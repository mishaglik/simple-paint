#ifndef PLUGINS_BRUSHES_HPP
#define PLUGINS_BRUSHES_HPP
#include "Vector.hpp"
#include "Color.hpp"

using Point = mgm::Vector2<int64_t>;

class Brush
{
public:
    struct BrushSettings
    {
        uint32_t size;
        uint32_t hardness; 
        uint8_t opacity;
    };

protected:
    const BrushSettings& settings_;

public:
    Brush(const BrushSettings& settings) : settings_(settings) {}
    virtual ~Brush() {}

    struct BrushPoint
    {
        Point point;
        uint8_t opacity;
    };

    BrushPoint bpt_;

    class Iterator
    {
        Brush* brush_;
        bool finished_;
    public:
        Iterator(Brush* brush, bool end = false) : brush_(brush), finished_(end) {}
        
        Iterator(const Iterator&)            = delete;
        Iterator& operator=(const Iterator&) = delete;

        const BrushPoint& operator* () { return brush_->bpt_;}
        Iterator& operator++() { finished_ = brush_->nextPoint(); return *this;}

        bool operator==(const Iterator& oth) const {return finished_ == oth.finished_; }
        bool operator!=(const Iterator& oth) const {return !(*this == oth); }
    };

    struct ItPair
    {
        Brush* brush;
        Iterator begin() { return brush->getBegin(); }
        Iterator end  () { return brush->getEnd  (); }
    };

    ItPair at(const Point& center) { setCenter(center); return {this}; }
    ItPair operator[](const Point& center) { return at(center); }
    
    virtual void setCenter(const Point& center) = 0;
    virtual bool nextPoint()      = 0;
    virtual Iterator getBegin() { return Iterator(this, false); }
    virtual Iterator getEnd()   { return Iterator(this, true); }
};


#endif /* PLUGINS_BRUSHES_HPP */
