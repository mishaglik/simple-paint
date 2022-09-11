#ifndef VECTORPLOT_HPP
#define VECTORPLOT_HPP
#include "AbstractGL/AWindow.hpp"
#include "AbstractGL/Widget.hpp"
#include "CoordinateSystem.hpp"
#include "MGeomerty/Point.hpp"
#include "MGeomerty/Vector.hpp"
#include <cstdint>

class VectorPlot : public aGL::Widget, public CoordSystem{
    
    mgm::Vector2f vec_;
    mgm::Point2f startPoint_ = {0, 0};

    void drawBackground(const aGL::Window* window);
    void drawForeground(const aGL::Window* window);

public:
    void render(const aGL::Window& window) override;
    
    VectorPlot(uint32_t x, uint32_t y, uint32_t w, uint32_t h, double minX, double minY, double maxX, double maxY);
    
    ~VectorPlot() override;

    void setVector(const mgm::Vector2f& vec);
    
    const mgm::Vector2f& getVector() const;
    
    mgm::Vector2f& getVectorRef();
};

#endif /* VECTORPLOT_HPP */
