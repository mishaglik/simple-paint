#include "BrezLine.hpp"

BrezLine::BrezLine(const Point& p0, const Point& p1) :
    start_(p0), finish_(p1), 
    dx_(+abs(p1.x - p0.x)), sx_(p0.x < p1.x ? 1 : -1), 
    dy_(-abs(p1.y - p0.y)), sy_(p0.y < p1.y ? 1 : -1), 
    error_(dx_ + dy_) 
{
    
}

BrezLine::BrezLineIter BrezLine::begin() const
{
    return BrezLineIter{start_, finish_, dx_, sx_, dy_, sy_, error_};
}

BrezLine::BrezLineIter BrezLine::end() const
{
    return BrezLineIter{finish_, finish_, dx_, sx_, dy_, sy_, error_};
}

BrezLine::BrezLineIter& BrezLine::BrezLineIter::operator++()
{
    int e2 = 2 * error_;
    if(e2 >= dy_)
    {
        if(start.x == finish.x)
        {
            start = finish;
            return *this;
        }
        error_ += dy_;
        start.x += sx;
    }
    
    if(e2 <= dy_)
    {
        if(start.y == finish.y)
        {
            start = finish;
            return *this;
        }

        error_ += dx;
        start.y += sy;
    }
    return *this;
}
