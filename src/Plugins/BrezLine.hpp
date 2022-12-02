#ifndef PLUGINS_BREZLINE_HPP
#define PLUGINS_BREZLINE_HPP

#include "Vector.hpp"

using Point = mgm::Vector2<int64_t>;

class BrezLine
{
    const Point start_, finish_;
    const int32_t dx_, sx_, dy_, sy_, error_;
public:
    BrezLine(const Point& start, const Point& finish);

    struct BrezLineIter
    {
        Point start;
        const Point finish;
        const int32_t dx, sx, dy_, sy;
        int32_t error_;
    public:
        // BrezLineIter(const Point& point, int32_t dx, int32_t sx, int32_t dy, int32_t sy, int32_t error);
        
        BrezLineIter& operator++();
        
        const Point& operator*() const {return start; }

        bool operator==(const BrezLineIter& oth) const { return start == oth.start; }
        bool operator!=(const BrezLineIter& oth) const { return !(*this == oth); }
    };

    BrezLineIter begin() const;
    BrezLineIter end() const;
};

#endif /* PLUGINS_BREZLINE_HPP */
