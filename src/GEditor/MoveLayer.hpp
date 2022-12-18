#ifndef GEDITOR_MOVELAYER_HPP
#define GEDITOR_MOVELAYER_HPP

#include "Tool.hpp"

namespace mge {
    class MoveLayer : public Tool
    {
    public:
        MoveLayer() {}
        void onMousePress  (const ToolAction& action) override;
        void onMouseRelease(const ToolAction& action) override;
        void onMouseMove   (const ToolAction& action) override;
        void onMouseLeave  (const ToolAction& action) override;
        void onTimerEvent  (const ToolAction&) override {}
        virtual void onImageChange() override {}
        virtual const char* getTexture() const override { return "Arrow.png"; }
        virtual void createPanel() override { if(!panel_) panel_ = new aGL::Widget({0,0,10,10}, nullptr, nullptr); }
    private:
        bool captured_ = false;
        aGL::Point prevPosition_ = {};
    };
}

#endif /* GEDITOR_MOVELAYER_HPP */
