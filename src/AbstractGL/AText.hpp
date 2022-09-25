#ifndef ABSTRACTGL_ATEXT_HPP
#define ABSTRACTGL_ATEXT_HPP

#include <MGeomerty/Geometry.hpp>
#include "Color.hpp"

namespace aGL {

    using Rect  = mgm::Rect2u;
    using Point = mgm::Point2u;

    class Text
    {

    public:
        enum styleFlags{
            Normal        = 0,
            Bold          = 1 << 0,
            Italic        = 1 << 1,
            Underlined    = 1 << 2,
            Strikethrough = 1 << 3,
        };

    private:
        class Text_;
        Text_* tp_;
    
        
        Rect rect_;
        unsigned charSize_   = 30;
        unsigned styleFlags_ = styleFlags::Normal;
        Color color_ = Colors::Black;
        const char* text_ = nullptr;

        friend class Window;            //Allow both Window & RenderSurface to acess private tp_
        friend class RenderSurface;

    public:
        Text(const char* fontName, const char* text, uint32_t x = 0, uint32_t y = 0);
        ~Text();
        
        void setPosition(uint32_t x, uint32_t y);
        void setPosition(const Point& pt);

        void setColor(const Color& color);
        void setStyle(uint32_t style);
        void setCharacterSize(unsigned size);

        Rect getRect() const;
    };

}
#endif /* ABSTRACTGL_ATEXT_HPP */
