#ifndef GEDITOR_GRANDDESIGN_HPP
#define GEDITOR_GRANDDESIGN_HPP

#include <cstdint>
#include "AbstractGL/AWindow.hpp"
namespace mge {
    namespace Design {

            using aGL::Rect;
            using aGL::Color;

            namespace ColorPalete
            {
                const Color backgroundColor  = 0x454545ff;
                const Color borderLightColor = 0x5b5b5bff;
                const Color borderDarkColor  = 0x3b3b3bff;
                const Color hollowColor      = 0x313131ff;
                const Color ScrollHoleColor  = 0x202020ff;
                const Color TextColor        = 0xddddddff;

            };

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
                const uint32_t Y = Menu::RECT.y + Menu::RECT.h;
                const uint32_t W = 210;
                const uint32_t H = Window::H - Y;
                const Rect RECT = {X, Y, W, H};
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

                namespace ColorSelector {
                    const uint32_t size = 40;
                    const Rect RECT 
                    {
                        W / 2 - size / 2,
                        H / 3,
                        size,
                        size
                    };
                }

                namespace ToolPanel {
                    const Rect RECT
                    {
                        0,
                        LeftPanel::RECT.h - 430,
                        LeftPanel::RECT.w,
                        430
                    };

                    const Rect HEAD
                    {
                        0,0, RECT.w, 16
                    };
                    const Rect FOOT
                    {
                        0,
                        RECT.h - 21,
                        RECT.w,
                        21
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

                const uint32_t Spacing = 2;
                const uint32_t BarSize = 15;

                namespace StatusBar {
                    const Rect RECT
                    {
                        0,
                        MainWidget::RECT.h - 30,
                        MainWidget::RECT.w,
                        30
                    };
                }

                namespace LeftRuler {
                    const Rect RECT
                    {
                        Spacing,
                        Spacing + BarSize,
                        BarSize,
                        MainWidget::RECT.h - 2 * (Spacing + BarSize) - StatusBar::RECT.h,
                    };
                }

                namespace TopRuler {
                    const Rect RECT
                    {
                        Spacing + BarSize,
                        Spacing,
                        MainWidget::RECT.w - 2 * (Spacing + BarSize),
                        BarSize,
                    };
                }

                namespace YScrollbar {
                    const Rect RECT
                    {
                        MainWidget::RECT.w - Spacing - BarSize,
                        Spacing + BarSize,
                        BarSize,
                        MainWidget::RECT.h - 2 * (Spacing + BarSize) - StatusBar::RECT.h,
                    };
                    static const char* TEXNAME = "CanvasSrollbar";
                    const uint32_t ScrollSize = 200;
                }

                namespace XScrollbar {
                    const Rect RECT
                    {
                        Spacing + BarSize,
                        MainWidget::RECT.h - Spacing - BarSize - StatusBar::RECT.h,
                        MainWidget::RECT.w - 2 * (Spacing + BarSize),
                        BarSize,
                    };
                    static const char* TEXNAME = "CanvasSrollbar";
                    const uint32_t ScrollSize = 200;
                }

                namespace CanvasD {
                    const Rect RECT
                    {
                        Spacing + BarSize,
                        Spacing + BarSize,
                        MainWidget::RECT.w - 2 * (Spacing + BarSize),
                        MainWidget::RECT.h - 2 * (Spacing + BarSize) - StatusBar::RECT.h,
                    };
                }
            }

            namespace RightPanel {
                const uint32_t W = 210;
                const uint32_t H = Window::H - Menu::RECT.h;
                const uint32_t X = Window::W - W;
                const uint32_t Y = Menu::RECT.h;

                namespace Layers {
                    const Rect RECT
                    {
                        X, Y + H  - 430, W, 430
                    };

                    namespace LBar {
                        const uint32_t W = Layers::RECT.w - 10;
                        const uint32_t X = 0;
                        const uint32_t H = 30;
                    }
                }
            }

    }
}

#endif /* GEDITOR_GRANDDESIGN_HPP */
