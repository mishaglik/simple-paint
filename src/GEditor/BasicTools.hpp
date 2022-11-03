#ifndef GEDITOR_BASICTOOLS_HPP
#define GEDITOR_BASICTOOLS_HPP
#include "Tool.hpp"

namespace mge {
    namespace tools {

        class Interpolator
        {
        public:
            virtual ~Interpolator() {}
            virtual void addPoint(aGL::Point pt) = 0;
            virtual void reset() = 0;
            virtual aGL::Point getPoint(double t) = 0; 
        };

        class KatmulRom final : public Interpolator
        {
            mgm::Vector2f  y_[4] = {};
            mgm::Vector2f dy_[2] = {};
            mgm::Vector2f  a_[4] = {};
            uint8_t points_ = 0;
        public:
            KatmulRom();

            ~KatmulRom() override final;

            void addPoint(aGL::Point pt) override final;

            void reset() final;

            aGL::Point getPoint(double t) final;
        
        };


        void drawLine(aGL::Image* image, aGL::Point start, aGL::Point end, aGL::Color color);

        class Pen : public Tool
        {
            aGL::Color color_ = aGL::Colors::Red;
            bool isPressed_ = false;
            aGL::Point prevDrawn_ = {};
            KatmulRom interp_;
        public:
            Pen(DrawingContext* context) : Tool(context) {}
            Pen(DrawingContext* context, const aGL::Color& color) : Tool(context), color_(color) {}
            ~Pen() override {}

            void onMousePress(const ToolAction& action) override
            {
                action.image->setPixel(action.point.x, action.point.y, color_);
                if (action.shift)
                {
                    drawLine(action.image, prevDrawn_, action.point, color_);
                }
                prevDrawn_ = action.point;
                isPressed_ = true;
            }

            void onMouseRelease(const ToolAction& ) override
            {
                interp_.reset();
                isPressed_ = false;
            }

            void onMouseMove   (const ToolAction& action) override 
            {
                if(isPressed_)
                {
                    // action.image->setPixel(action.point.x, action.point.y, color_);
                    interp_.addPoint(action.point);
                    for(int i = 1; i <= 100; ++i)
                    {
                        aGL::Point pt = interp_.getPoint(i / 100.);
                        action.image->setPixel(pt.x, pt.y, color_);
                    }
                    prevDrawn_ = action.point;
                }
            }

            void onImageChange() override {}
            const char* getSkinName() const override { return "Pen"; }
        };


        class RectFiller : public Tool
        {
            aGL::Point first_;
            bool hasFirst_ = false;
        public:
            RectFiller(DrawingContext* context) : Tool(context) {}
            virtual void onMousePress  (const ToolAction& action) override;
            virtual void onMouseRelease(const ToolAction&) override {}
            virtual void onMouseMove   (const ToolAction&) override {}
            virtual void onImageChange() override { hasFirst_ = false; }
            virtual const char* getSkinName() const override {return "RectFiller";}
        };

        class EllipseFiller : public Tool
        {
            aGL::Point first_;
            bool hasFirst_ = false;
        public:
            EllipseFiller(DrawingContext* context) : Tool(context) {}
            virtual void onMousePress  (const ToolAction& action) override;
            virtual void onMouseRelease(const ToolAction&) override {}
            virtual void onMouseMove   (const ToolAction&) override {}
            virtual void onImageChange() override { hasFirst_ = false; }
            virtual const char* getSkinName() const override {return "EllipseFiller";}
        };

        int cmpColors(const aGL::Color& c1, const aGL::Color c2);

        class Filler : public Tool
        {
        public:
            Filler(DrawingContext* context) : Tool(context) {}
            virtual void onMousePress  (const ToolAction& action) override;
            virtual void onMouseRelease(const ToolAction&) override {}
            virtual void onMouseMove   (const ToolAction&) override {}
            virtual void onImageChange() override {}
            virtual const char* getSkinName() const override {return "Filler";}
        };

        class Pippet : public Tool
        {
        public:
            Pippet(DrawingContext* context) : Tool(context) {}
            virtual void onMousePress  (const ToolAction& action) override { (action.ctrl ? context_->backgroundColor : context_->foregroundColor) = action.image->getPixel(action.point.x, action.point.y);}
            virtual void onMouseRelease(const ToolAction&) override {}
            virtual void onMouseMove   (const ToolAction&) override {}
            virtual void onImageChange() override {}
            virtual const char* getSkinName() const override {return "Pippet";}
        };
    }
}

#endif /* GEDITOR_BASICTOOLS_HPP */
