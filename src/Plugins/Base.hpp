#include "tools.hpp"


namespace basa {
    using namespace booba;

    class Pen : public Tool
    {
    public:
        Pen() {}
        ~Pen() override {}
        void apply(Image* image, const Event* event) override;
        const char* getTexture() override { return "Pen";} 
        void buildSetupWidget() override;
    };
}
