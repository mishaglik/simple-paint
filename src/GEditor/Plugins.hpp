#ifndef GEDITOR_PLUGINS_HPP
#define GEDITOR_PLUGINS_HPP

#include "../Plugins/tools.hpp"
#include "GEditor/GrandDesign.hpp"
#include "Tool.hpp"
#include <Widgets/Button.hpp>
#include <Widgets/Scrollbar.hpp>

namespace mge {
    void importPlugins();
    class PluginButton;
    class PluginScroll;

    class PluginTool : public Tool, public aGL::SignalObject
    {
        booba::Tool* tool_;
        booba::Event ev;
        aGL::Point prevMove_;
        std::string texName_;
    public:
        PluginTool(booba::Tool* tool);
        ~PluginTool() override { delete tool_; tool_ = nullptr; }
        void onMousePress  (const ToolAction& action) override;
        void onMouseRelease(const ToolAction& action) override;
        void onMouseMove   (const ToolAction& action) override;
        void onImageChange() override {}
        const char* getTexture() const override {return texName_.c_str();}
        void createPanel() override;

        void onButtonClick(const PluginButton* button);
        void onScrollMove(int32_t value, const PluginScroll* scroll);
        void onCanvasEvent(const booba::Event ev);

        static PluginTool* currentPlugin;
    private:
        class ToolGuard
        {
        public:
            ToolGuard(PluginTool* tool) { currentPlugin = tool; }
            ~ToolGuard() { currentPlugin = nullptr; }
        };
    };

    class PluginButton : public aGL::AbstractButton
    {
    public:
        PluginButton(const aGL::Rect& rect, const char* text, aGL::Widget* parent) : aGL::AbstractButton(rect, text, parent) 
        {
            aGL::AbstractButton::clicked.connect(this, &PluginButton::clickPtr);
            text_.setColor(Design::ColorPalete::TextColor);
            text_.setCharacterSize(3 * rect.h / 4);
            text_.setPosition(1, 0);
        }

        aGL::Signal<const PluginButton* > clicked;
        void clickPtr() { clicked.emit(this); }
        aGL::EventHandlerState onPaintEvent(const aGL::Event* event) override;

    };

    class PluginScroll : public aGL::Scrollbar
    {
    public:
        PluginScroll(const aGL::Rect& rect, aGL::Widget* parent) : aGL::Scrollbar(rect, aGL::Scrollbar::Horizontal, rect.w / 10, parent) 
        {
            aGL::Scrollbar::valueChanged.connect(this, &PluginScroll::valChangedPtr);
        }

        aGL::Signal<int32_t, const PluginScroll* > valueChangedPtr;
        void valChangedPtr(int32_t val) { valueChangedPtr.emit(val, this); }
        // aGL::EventHandlerState onPaintEvent(const aGL::Event* event) override;

    };

    class PluginCanvas : public aGL::Widget
    {
    public:
        PluginCanvas(const aGL::Rect& rect, aGL::Widget* parent) : aGL::Widget(rect, parent) {}
        aGL::Signal<booba::Event> mousePressed;
        aGL::Signal<booba::Event> mouseReleased;
        aGL::Signal<booba::Event> mouseMoved;

        aGL::EventHandlerState onMouseButtonPressEvent(const aGL::Event* event) override;
        aGL::EventHandlerState onMouseButtonReleaseEvent(const aGL::Event* event) override;
        aGL::EventHandlerState onMouseMoveEvent(const aGL::Event* event) override;

        void putPixel (int32_t x, int32_t y, aGL::Color color);
        void putSprite(int32_t x, int32_t y, uint32_t w, uint32_t h, const char* texture);
        aGL::EventHandlerState onPaintEvent(const aGL::Event*) override { return aGL::Accepted; }
    };

    class PluginImage : public booba::Image
    {
        aGL::Image* image_ = nullptr;
        mutable uint32_t pixel_;
    public:
        PluginImage(aGL::Image* image) : image_(image) {}
        virtual uint32_t getH() override { return image_->getH(); }
        virtual uint32_t getW() override { return image_->getW(); }
        uint32_t getPixel(int32_t x, int32_t y) const 
        {
            if(!isOnImage(x, y))
            {
                mError << "Plugin read out of range: " << x << " " << y << mlg::endl;
                return aGL::Colors::Black;
            }

            return image_->getPixel(x, y); 
        }
        virtual uint32_t getPixel(int32_t x, int32_t y) override 
        {
            if(!isOnImage(x, y))
            {
                mError << "Plugin read out of range: " << x << " " << y << mlg::endl;
                return aGL::Colors::Black;
            }
            return image_->getPixel(x, y); 
        }   
        virtual void putPixel(uint32_t x, uint32_t y, uint32_t color) override 
        {
            if(!isOnImage(x, y))
            {
                mError << "Plugin write out of range: " << x << " " << y << mlg::endl;
                return;
            }
            image_->setPixel(x, y, color); 
        }        
        virtual uint32_t& operator()(uint32_t x, uint32_t y) override { MLG_UIMPLEMENTED  return pixel_;}
        virtual const uint32_t& operator()(uint32_t x, uint32_t y) const override { return pixel_ = getPixel(x, y);}
        bool isOnImage(int x, int y)  const { return x >= 0 && y >=0 && x < image_->getW() && y < image_->getH(); }
    public:
        virtual ~PluginImage() override {}
    };
}

#endif /* GEDITOR_PLUGINS_HPP */
