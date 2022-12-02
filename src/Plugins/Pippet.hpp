#include "Elpstd/tools.hpp"


using namespace booba;

class Pippet : public Tool
{
public:
    Pippet() {}
    ~Pippet() override {}
    void apply(Image* image, const Event* event) override;
    const char* getTexture() override { return "Pippet.png";} 
    void buildSetupWidget() override {}
};

