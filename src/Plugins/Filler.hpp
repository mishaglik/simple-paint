#include "tools.hpp"
#include "Color.hpp"

using namespace booba;

class Filler : public Tool
{
public:
    Filler() {}
    ~Filler() override {}
    void apply(Image* image, const Event* event) override;
    const char* getTexture() override { return "Filler.png";} 
    void buildSetupWidget() override {}
    void fill(Image* image, int startX, int startY, Color fillColor);
};
