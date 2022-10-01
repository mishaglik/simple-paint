#include "RenderObject.hpp"

namespace RTObjs {
    namespace MaterialCollection {
        const Material Void
        {
            .color     = aGL::Colors::Black,
            .isSource  = true,  // Make sure light wont go out.
            .srcColor  = aGL::Colors::Black,
            .fuzzyness = 0,
            .reflCoef  = 0,
            .diffCoef  = 0,
            .refrCoef  = 0,
            .refrIndex = 0,

        };

        const Material Mirror
        {
            .color     = aGL::Colors::White,
            .isSource  = false,
            .srcColor  = aGL::Colors::Black,
            .fuzzyness = 0,
            .reflCoef  = 0.83,
            .diffCoef  = 0.1,
            .refrCoef  = 0,
            .refrIndex = 0,

        };

        const Material Glass
        {
            .color     = aGL::Colors::White,
            .isSource  = false,
            .srcColor  = aGL::Colors::Black,
            .fuzzyness = 0,
            .reflCoef  = 0.1,
            .diffCoef  = 0.05,
            .refrCoef  = 0.89,
            .refrIndex = 1.5,

        };

        const Material Grass
        {
            .color     = 0x00a520ff,
            .isSource  = false, 
            .srcColor  = aGL::Colors::Black,
            .fuzzyness = 0,
            .reflCoef  = 0.1,
            .diffCoef  = 0.8,
            .refrCoef  = 0,
            .refrIndex = 0,

        };

        const Material Sun
        {
            .color     = aGL::Colors::White,
            .isSource  = true,
            .srcColor  = 0xfffc1aFF,
            .fuzzyness = 0,
            .reflCoef  = 0,
            .diffCoef  = 0,
            .refrCoef  = 0,
            .refrIndex = 0,

        };

        const Material Sky
        {
            .color     = aGL::Colors::Red,
            // .color     = 0xc7defeff,
            .isSource  = true,
            .srcColor  = aGL::Colors::Red,
            // .srcColor  = 0xc7defeff,
            .fuzzyness = 0,
            .reflCoef  = 0,
            .diffCoef  = 0,
            .refrCoef  = 0,
            .refrIndex = 0,

        };
    }
}
