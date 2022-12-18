#include "MoveLayer.hpp"
#include "GEditor.hpp"

namespace mge {
    void MoveLayer::onMousePress  (const ToolAction& action)
    {
        prevPosition_ = action.point;
        prevPosition_.x += GEditor::app->layers_[GEditor::app->selectedLayer_].rect.x;
        prevPosition_.y += GEditor::app->layers_[GEditor::app->selectedLayer_].rect.y;
        captured_ = true;
    }

    void MoveLayer::onMouseRelease(const ToolAction& action)
    {
        captured_ = false;
    }

    void MoveLayer::onMouseMove   (const ToolAction& action)
    {
        if(captured_)
        {
            aGL::Point point = action.point;
            point.x +=  GEditor::app->layers_[GEditor::app->selectedLayer_].rect.x;
            point.y +=  GEditor::app->layers_[GEditor::app->selectedLayer_].rect.y;
            int dx = point.x - prevPosition_.x;
            int dy = point.y - prevPosition_.y;
            GEditor::app->layers_[GEditor::app->selectedLayer_].rect.x += dx;
            GEditor::app->layers_[GEditor::app->selectedLayer_].rect.y += dy;
            prevPosition_.x += dx;
            prevPosition_.y += dy;
        }
    }

    void MoveLayer::onMouseLeave  (const ToolAction& action)
    {
        captured_ = false;
    }
}