#ifndef RAYTRACER_SCENEEDITOR_HPP
#define RAYTRACER_SCENEEDITOR_HPP

#include "Raytracer/Scene.hpp"
#include "Widgets/ContainerWidget.hpp"
#include "Widgets/Scrollbar.hpp"

class SceneEditor : public aGL::ContainerWidget
{
    Scene* scene_ = nullptr;
    aGL::Scrollbar* scrollbar_ = nullptr;
    int start_ = 0;
    mvc::Vector<aGL::Widget* > editorEntries_;
public:
    SceneEditor(Scene* scene, uint32_t x, uint32_t y, uint32_t w, uint32_t h, aGL::Widget* parent = nullptr);
    ~SceneEditor() override {}

    aGL::EventHandlerState onPaintEvent(const aGL::Event *event) override;
private:
    void setStart(int y);
};

#endif /* RAYTRACER_SCENEEDITOR_HPP */
