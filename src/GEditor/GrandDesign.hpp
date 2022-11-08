#ifndef GEDITOR_GRANDDESIGN_HPP
#define GEDITOR_GRANDDESIGN_HPP

#include <cstdint>
#include "AbstractGL/AWindow.hpp"
namespace mge {
    namespace Design {
            using aGL::Rect;
            const uint32_t MinSpacing = 1;

            namespace Window {
                const uint32_t W = 1300;
                const uint32_t H = 750;
                static const char* TITLE = "Grand designed image manipulator";
            }

            namespace Menu {
                const Rect RECT
                {
                    0,
                    0,
                    Window::W,
                    30
                };
                const uint32_t letterSize = 20;

                namespace MenuEntry {
                    const uint32_t W = 100;
                }
            }

            namespace LeftPanel {
                const uint32_t X = 0;
                const uint32_t Y = Menu::RECT.x + Menu::RECT.w;
                const uint32_t W = 210;
                const uint32_t H = Window::H - Y;

                namespace LOGO {
                    const Rect RECT
                    {
                        X, Y, W, 29
                    };
                }

                namespace Toolbox {
                    
                    namespace ToolboxButton {
                        const uint32_t W = 35, H = 35;
                    }
                    const uint32_t N_IN_ROW   = LeftPanel::W / ToolboxButton::W;
                    const uint32_t MAX_IN_COL = 5;

                    const Rect RECT
                    {
                        X, Y, 
                        N_IN_ROW   * ToolboxButton::W, 
                        MAX_IN_COL * ToolboxButton::H
                    };
                }

            }

            namespace MainWidget {
                const Rect RECT 
                {
                    LeftPanel::X + LeftPanel::W + MinSpacing,
                    Menu::RECT.y + Menu::RECT.h,
                    880 - 2 * MinSpacing,
                    Window::H - Menu::RECT.h - Menu::RECT.y
                };
            }

            namespace RightPanel {
                const uint32_t W = 210;
                const uint32_t H = Window::H - Menu::RECT.h;
                const uint32_t X = Window::W - W;
                const uint32_t Y = Window::H;
            }

    }
}

#endif /* GEDITOR_GRANDDESIGN_HPP */
