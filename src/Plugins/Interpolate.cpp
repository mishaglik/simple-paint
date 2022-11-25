#include "Interpolate.hpp"
#include <cassert>

KatmulRom::KatmulRom() {}   
KatmulRom::~KatmulRom() {}

void KatmulRom::addPoint(Point pt)
{
    mgm::Vector2f v = pt;

    if(points_ == 4)
    {
        y_[0] = y_[1];
        y_[1] = y_[2];
        y_[2] = y_[3];
        y_[3] = v;
        dy_[0] = dy_[1];
    }
    else {
        for(uint8_t i = points_; i < 4; ++i)
            y_[i] = v;
        points_++;
        dy_[0] =  y_[2];
        dy_[0] -= y_[0];
        dy_[0] *= 0.5;
    }

    dy_[1] =  y_[3];
    dy_[1] -= y_[1];
    dy_[1] *= 0.5;

    a_[0] = y_[1];
    a_[1] = dy_[1];

    a_[3] = y_[1];
    a_[3] -= y_[2];
    a_[3] *= 2;
    a_[3] += dy_[1];
    a_[3] += dy_[0];

    a_[2] = y_[2];
    a_[2] -= a_[0];
    a_[2] -= a_[1];
    a_[2] -= a_[3];
}

void KatmulRom::reset()
{
    points_ = 0;
}

Point KatmulRom::getPoint(double t)
{
    // t += 1;
    double x = 1;
    mgm::Vector2f ans = {};
    for(uint8_t i = 0; i < 4; ++i)
    {
        mgm::Vector2f p = a_[i];
        p *= x;
        ans += p;
        x *= t;
    }
    return ans;
}

void drawLine(booba::Image* image, Point p0, Point p1, uint32_t color)
{
    // if(p1.x < p0.x) std::swap(p0, p1);
    int dx = abs(p1.x - p0.x);
    int sx = p0.x < p1.x ? 1 : -1;
    int dy = -abs(p1.y - p0.y);
    int sy = p0.y < p1.y ? 1 : -1;
    int error = dx + dy;
    int x = p0.x;
    int y = p0.y;
    while(p1 != Point(x, y))
    {
        image->putPixel(x, y, color);
        int e2 = 2 * error;
        if(e2 >= dy)
        {
            if(x == p1.x) break;
            error += dy;
            x += sx;
        }
        if(e2 <= dy)
        {
            if(y == p1.y) break;
            error += dx;
            y += sy;
        }
    }
    image->putPixel(x, y, color);
}


void KatmulRom2::reset()
{
    points_.clear();
    currentStart_ = -1;
}

void KatmulRom2::calcCoef(uint32_t start)
{
    if(start == currentStart_) return;
    assert(start + 3 < size());
    
    coefs_[0] = points_[start + 1]; // p_{i-1}
    
    coefs_[1] = tension_ * (points_[start + 2] - points_[start]); // \tay ( p_{i} - p_{i-2} )

    coefs_[2] = (2 * tension_    ) * points_[start    ] + 
                (tension_ - 3    ) * points_[start + 1] + 
                (3 - 2 * tension_) * points_[start + 2] +
                (-tension_       ) * points_[start + 3];

    coefs_[3] = (-tension_       ) * points_[start    ] + 
                (2 - tension_    ) * points_[start + 1] + 
                (tension_  - 2   ) * points_[start + 2] +
                (tension_        ) * points_[start + 3];
}

Point KatmulRom2::getPoint(double t)
{
    if(size() < 4)
    {
        if(size() == 0) return {};
        // if(size() == 1)
        return {};
    }

    int start = static_cast<int>(t) - 1;
    if(start < 0) start = 0;
    if(start > size() - 4) start = size() - 4;
    calcCoef(start);

    t -= start + 1;

    return coefs_[0] + t * coefs_[1] + t*t * coefs_[2] + t*t*t * coefs_[3];
}

