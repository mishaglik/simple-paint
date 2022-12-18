#ifndef GEDITOR_LAYERS_HPP
#define GEDITOR_LAYERS_HPP
#include "AbstractGL/AImage.hpp"
#include "AbstractGL/Event.hpp"
#include "Vector/Vector.hpp"
#include "Widgets/Checkbox.hpp"
#include "Widgets/ContainerWidget.hpp"
#include "Widgets/Scrollbar.hpp"

namespace mge {
    struct Layer 
    {
        aGL::Rect rect;
        aGL::Image* image;
        const char* name;
        bool isHidden = false;
    };

    class LayerManager;

    class LayerBar : public aGL::ContainerWidget
    {
        aGL::Texture imageTexture_;
        aGL::Text text_;
        aGL::Checkbox* visibleToggler_;
        aGL::PushButton* pbUp_;
        aGL::PushButton* pbDn_;
        
    public:
        bool selected = false;
        uint32_t index_ = 0;
        LayerBar(aGL::Rect, uint32_t index, aGL::Widget* parent);
        aGL::EventHandlerState onPaintEvent(const aGL::Event* event) override;
        aGL::EventHandlerState onMouseButtonPressEvent(const aGL::Event* event) override;
        void onSkinChange() override;
        void update() override;
        void toggleVisibility(bool tog);

        void moveDown();
        void moveUp();

    };

    class LayerManager : public aGL::ContainerWidget 
    {
        mvc::Vector<LayerBar* > layers_;
        aGL::PushButton* addButton_;
        aGL::PushButton* dupButton_;
        aGL::PushButton* delButton_;
        aGL::Text name_;
    public:
        LayerManager(aGL::Rect rect, aGL::Widget* parent);
        aGL::EventHandlerState onPaintEvent(const aGL::Event* event) override;
        void afterPaint() const override;
        void onSkinChange() override;


        aGL::ContainerWidget* cropeer_;
        aGL::ContainerWidget* container_;

        aGL::Scrollbar *yScroll_;
        void update() override;  
    private:
        void createLayer();
        void duplicateLayer();
        void deleteLayer();

        void setScrollY(int y); 
    };
}

#endif /* GEDITOR_LAYERS_HPP */
