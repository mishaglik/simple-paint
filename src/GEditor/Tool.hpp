#ifndef GEDITOR_TOOL_HPP
#define GEDITOR_TOOL_HPP

#include "AbstractGL/AImage.hpp"
#include "AbstractGL/Event.hpp"
#include "GEditor/ToolPanel.hpp"
namespace mge {
    struct DrawingContext;
    struct ToolAction
    {
        aGL::Image* image;
        aGL::Point point;
        bool shift;
        bool ctrl;
        bool alt;
    };

    class Tool
    {
    protected:
        ToolPanel* panel_ = nullptr; 
    public:
        Tool() {}
        virtual ~Tool() {}
        virtual void onMousePress  (const ToolAction& action) = 0;
        virtual void onMouseRelease(const ToolAction& action) = 0;
        virtual void onMouseMove   (const ToolAction& action) = 0;
        virtual void onImageChange() = 0;
        virtual const char* getTexture() const = 0;
        virtual void createPanel(aGL::Widget* parent, const aGL::Rect& rect) { if(!panel_) panel_ = new ToolPanel(rect, "Tool", parent);}
        ToolPanel* getPanel() { return panel_; } 
        
    };
}

#endif /* GEDITOR_TOOL_HPP */
