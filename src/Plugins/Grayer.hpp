#include "Elpstd/tools.hpp"


using namespace booba;

class Grayer : public Tool
{
public:
    Grayer() {}
    ~Grayer() override {}
    void apply(Image* image, const Event* event) override;
    const char* getTexture() override { return "Grayer.png";} 
    void buildSetupWidget() override {}
};
