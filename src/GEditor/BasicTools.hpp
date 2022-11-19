#ifndef GEDITOR_BASICTOOLS_HPP
#define GEDITOR_BASICTOOLS_HPP
#include "Tool.hpp"
#include "GEditor.hpp"
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
            bool isPressed_ = false;
            aGL::Point prevDrawn_ = {};
            KatmulRom interp_;
        public:
            Pen() : Tool() {}
            ~Pen() override {}

            void onMousePress(const ToolAction& action) override
            {
                action.image->setPixel(action.point.x, action.point.y, GEditor::app->context.foregroundColor);
                if (action.shift)
                {
                    drawLine(action.image, prevDrawn_, action.point, GEditor::app->context.foregroundColor);
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
                    // action.image->setPixel(action.point.x, action.point.y, GEditor::app->context.foregroundColor);
                    interp_.addPoint(action.point);
                    for(int i = 1; i <= 100; ++i)
                    {
                        aGL::Point pt = interp_.getPoint(i / 100.);
                        action.image->setPixel(pt.x, pt.y, GEditor::app->context.foregroundColor);
                    }
                    prevDrawn_ = action.point;
                }
            }

            void onImageChange() override {}
            const char* getTexture() const override { return "modules/Pen.png"; }
            // virtual void createPanel(aGL::Widget* parent, const aGL::Rect& rect) override { panel_ = new ToolPanel(rect, "Pen", parent); }

        };


        class RectFiller : public Tool
        {
            aGL::Point first_;
            bool hasFirst_ = false;
        public:
            RectFiller() : Tool() {}
            virtual void onMousePress  (const ToolAction& action) override;
            virtual void onMouseRelease(const ToolAction&) override {}
            virtual void onMouseMove   (const ToolAction&) override {}
            virtual void onImageChange() override { hasFirst_ = false; }
            virtual const char* getTexture() const override {return "modules/Rect.png";}
            // virtual void createPanel(aGL::Widget* parent, const aGL::Rect& rect) override { panel_ = new ToolPanel(rect, "RectFiller", parent); }
            

        };

        class EllipseFiller : public Tool
        {
            aGL::Point first_;
            bool hasFirst_ = false;
        public:
            EllipseFiller() : Tool() {}
            virtual void onMousePress  (const ToolAction& action) override;
            virtual void onMouseRelease(const ToolAction&) override {}
            virtual void onMouseMove   (const ToolAction&) override {}
            virtual void onImageChange() override { hasFirst_ = false; }
            virtual const char* getTexture() const override {return "modules/Ellipse.png";}
            // virtual void createPanel(aGL::Widget* parent, const aGL::Rect& rect) override { panel_ = new ToolPanel(rect, "EllipseFiller", parent); }
        };

        int cmpColors(const aGL::Color& c1, const aGL::Color c2);

        class Filler : public Tool
        {
        public:
            Filler() : Tool() {}
            virtual void onMousePress  (const ToolAction& action) override;
            virtual void onMouseRelease(const ToolAction&) override {}
            virtual void onMouseMove   (const ToolAction&) override {}
            virtual void onImageChange() override {}
            virtual const char* getTexture() const override {return "modules/Filler.png";}
        };

        class Pippet : public Tool
        {
        public:
            Pippet() : Tool() {}
            virtual void onMousePress  (const ToolAction& action) override { (action.ctrl ? GEditor::app->context.backgroundColor : GEditor::app->context.foregroundColor) = action.image->getPixel(action.point.x, action.point.y);}
            virtual void onMouseRelease(const ToolAction&) override {}
            virtual void onMouseMove   (const ToolAction&) override {}
            virtual void onImageChange() override {}
            virtual const char* getTexture() const override {return "modules/Pippet.png";}
        };

        class Grayer : public Tool
        {
        public:
            Grayer() : Tool() {}
            virtual void onMousePress  (const ToolAction& action) override;
            virtual void onMouseRelease(const ToolAction&) override {}
            virtual void onMouseMove   (const ToolAction&) override {}
            virtual void onImageChange() override {}
            virtual const char* getTexture() const override {return "modules/Grayer.png";}
        };
    }
}

#endif /* GEDITOR_BASICTOOLS_HPP */
