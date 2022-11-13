#ifndef GEDITOR_PLUGINS_HPP
#define GEDITOR_PLUGINS_HPP

#include "../Plugins/tools.hpp"
#include "Tool.hpp"

namespace mge {
    void importPlugins();

    class PluginTool : public Tool
    {
        booba::Tool* tool_;
        booba::Event ev;
        aGL::Point prevMove_;
    public:
        PluginTool(booba::Tool* tool) : tool_(tool) {}
        ~PluginTool() override { delete tool_; tool_ = nullptr; }
        void onMousePress  (const ToolAction& action) override;
        void onMouseRelease(const ToolAction& action) override;
        void onMouseMove   (const ToolAction& action) override;
        void onImageChange() override {}
        const char* getTexture() const override {return tool_->getTexture();}
    private:
    };

    class PluginImage : public booba::Image
    {
        aGL::Image* image_ = nullptr;
        mutable uint32_t pixel_;
    public:
        PluginImage(aGL::Image* image) : image_(image) {}
        virtual uint32_t getH() override { return image_->getH(); }
        virtual uint32_t getX() override { return image_->getW(); }
        uint32_t getPixel(int32_t x, int32_t y) const { return image_->getPixel(x, y); }
        virtual uint32_t getPixel(int32_t x, int32_t y) override { return image_->getPixel(x, y); }
        virtual void putPixel(uint32_t x, uint32_t y, uint32_t color) override { image_->setPixel(x, y, color); }        
        virtual uint32_t& operator()(uint32_t x, uint32_t y) override { MLG_UIMPLEMENTED  return pixel_;}
        virtual const uint32_t& operator()(uint32_t x, uint32_t y) const override { return pixel_ = getPixel(x, y);}
    public:
        virtual ~PluginImage() override {}
    };
}

#endif /* GEDITOR_PLUGINS_HPP */
