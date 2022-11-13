#ifndef GEDITOR_TOOL_HPP
#define GEDITOR_TOOL_HPP

#include "AbstractGL/AImage.hpp"
#include "AbstractGL/Event.hpp"
#include "Widgets/SkinManager.hpp"

namespace mge {

    struct DrawingContext
    {
        aGL::Color foregroundColor = aGL::Colors::Black;
        aGL::Color backgroundColor = aGL::Colors::White;
    };

    struct ToolAction
    {
        aGL::Image* image;
        aGL::Point point;
        bool shift;
        bool ctrl;
    };

    class Tool
    {
    protected:
        DrawingContext* context_;
    public:
        Tool(DrawingContext* context) : context_(context) {}
        virtual ~Tool() {}
        virtual void onMousePress  (const ToolAction& action) = 0;
        virtual void onMouseRelease(const ToolAction& action) = 0;
        virtual void onMouseMove   (const ToolAction& action) = 0;
        virtual void onImageChange() = 0;
        virtual const char* getSkinName() const = 0;
        // virtual aGL::TexId getSkin(const aGL::SkinManager* sm) const = 0;
        virtual aGL::Color getFillColor() const {return aGL::Colors::Black;}
    };
}

#endif /* GEDITOR_TOOL_HPP */
