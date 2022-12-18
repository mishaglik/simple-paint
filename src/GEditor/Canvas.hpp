#ifndef GEDITOR_CANVAS_HPP
#define GEDITOR_CANVAS_HPP

#include "Widgets/Widget.hpp"
#include "Tool.hpp"

namespace mge {
    class Canvas : public aGL::Widget
    {
        // aGL::Image* image_ = nullptr;
        aGL::Texture* imageTexture_ = nullptr;

        aGL::TexId alphaFiller_ = aGL::NoTexture;

        aGL::Vec2i imageStart_ = {};
        bool needsRepaint_ = true;

        aGL::Rect prevDrawnRect = {};
    public:
        Canvas(const aGL::Rect& rect, aGL::Widget* parent = nullptr);
        ~Canvas() override;


    private:
        ToolAction curAction_ = {};
        bool isPointOnImage(aGL::Point);
        void fillRect(bool clear = false);
    public:
        aGL::Signal<const ToolAction&> mousePressed;
        aGL::Signal<const ToolAction&> mouseReleased;
        aGL::Signal<const ToolAction&> mouseMoved;

        aGL::EventHandlerState onPaintEvent(const aGL::Event*) override;
        aGL::EventHandlerState onMouseButtonPressEvent(const aGL::Event*) override;
        aGL::EventHandlerState onMouseButtonReleaseEvent(const aGL::Event*) override;
        aGL::EventHandlerState onMouseLeaveEvent(const aGL::Event*) override;
        aGL::EventHandlerState onKeyPressedEvent(const aGL::Event*) override;
        aGL::EventHandlerState onKeyReleasedEvent(const aGL::Event*) override;
        aGL::EventHandlerState onLoseFocusEvent(const aGL::Event*) override;
        aGL::EventHandlerState onMouseMoveEvent(const aGL::Event*) override;
        
        void update() override;

        void onSkinChange() override;

        void setImageStartX(int x);
        void setImageStartY(int y);
        void moveImage(const aGL::Vec2i& v);
    };
}

#endif /* GEDITOR_CANVAS_HPP */
