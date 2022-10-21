#include "SceneEditor.hpp"


SceneEditor::SceneEditor(Scene* scene, uint32_t x, uint32_t y, uint32_t w, uint32_t h, aGL::Widget* parent) :
    aGL::ContainerWidget({x, y, w, h}, parent), scene_(scene)
{
    scrollbar_ = new aGL::Scrollbar(w - 20, 0, 20, h, aGL::Scrollbar::Vertical, this);
    scrollbar_->valueChanged.connect(this, &SceneEditor::setStart);

    int i = 0;
    for(RTObjs::RenderObject* obj : scene->objects())
    {
        if(i++ == 3) break;
        editorEntries_.push_back(obj->getEditorWidget(w - 20, this));
    }
    setStart(0); // We update size's of all elements;
}

void SceneEditor::setStart(int y)
{
    start_ = y;
    y = - y;
    for(size_t i = 0; i < editorEntries_.size(); ++i)
    {
        editorEntries_[i]->setPoisition(0, y);
        y += editorEntries_[i]->getRect().h;
    }
}

aGL::EventHandlerState SceneEditor::onPaintEvent(const aGL::Event *event)
{
    surface->clear(0);
    return aGL::ContainerWidget::onPaintEvent(event);
}
