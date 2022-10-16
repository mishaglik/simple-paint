#include "Menubar.hpp"

namespace aGL {

    Menubar::Menubar(uint32_t x, uint32_t y, uint32_t w, uint32_t h) :
        ContainerWidget({x, y, w, h})
    {

    }

    Menubar::~Menubar()
    {
        for(Menu* menu : menus_)
            delete menu;
    }

    size_t Menubar::addMenuEntry(const char* name)
    {
        uint32_t x = menus_.empty() ? 0 : menus_.back()->getRect().getCornerGL().x;
        Menu* newMenu = new Menu(x, rect_.y, 100, rect_.h, name, &emanager_); //TODO: auto w
        menus_.push_back(newMenu);
        subscribe(newMenu);
        newMenu->activated.connect(this, &Menubar::setActiveMenu);
        newMenu->deactivated.connect(this, &Menubar::setNoActiveMenu);
        return menus_.size() - 1;
    }
    
    bool Menubar::hasEventPoint(const Point& pt)
    {
        return ContainerWidget::hasEventPoint(pt) || (activeMenu ? activeMenu->hasEventPoint(pt) : false);
    }

    void Menubar::render(const Window& w) const
    {
        for(Menu* menu : menus_)
            menu->render(w);
    }

    Menubar::Menu::Menu(uint32_t x, uint32_t y, uint32_t w, uint32_t h, const char* name, EventManager* mgr) :
        Widget({x, y, w, h}, nullptr), emgr_(mgr)
    {
        mainButton = new MenuButton(x, y, w, h, name);
        emgr_->subscribe(mainButton);
        mainButton->clicked.connect<Menu>(this, &Menu::toggle);
    }

    Menubar::Menu::~Menu()
    {
        for(MenuButton* bt : buttons_)
            delete bt;
        delete mainButton;
    }

    EventHandlerState Menubar::Menu::onPaintEvent(const Event* e)
    {
        mainButton->onPaintEvent(e);
        for(MenuButton* bt : buttons_)
            bt->onPaintEvent(e);
        return Accepted;
    }

    void Menubar::Menu::render(const Window& w) const
    {
        mainButton->render(w);
        if(isActive_)
        {
            for(MenuButton* bt : buttons_)
                bt->render(w);
        }
    }
    

    void Menubar::setActiveMenu(Menu* menu)
    {
        if(activeMenu && activeMenu != menu) 
            activeMenu->hide();
        activeMenu = menu;
    }


    size_t Menubar::Menu::addMenuEntry(const char* text)
    {
        MenuButton* mb = new MenuButton(rect_.x, rect_.y + rect_.h * static_cast<uint32_t>(buttons_.size() + 1), rect_.w, rect_.h, text);
        emgr_->subscribe(mb);
        mb->clicked.connect(this, &Menu::hide);
        buttons_.push_back(mb);
        return buttons_.size() - 1;
    }

    bool Menubar::Menu::hasEventPoint(const Point& pt)
    {
        if(!isActive_) return false;
        return 
            pt.x >= static_cast<int> (rect_.x)             &&
            pt.x <= static_cast<int> (rect_.x + rect_.w)   &&
            pt.y >= static_cast<int> (rect_.y + rect_.h)   &&
            pt.y <= static_cast<int> (rect_.y + rect_.h * (buttons_.size() + 1));
    }
    
    

    Menubar::MenuButton::MenuButton(uint32_t x, uint32_t y, uint32_t w, uint32_t h, const char* text)
        : AbstractButton({x, y, w, h},text)
    {
        text_.setCharacterSize(3 * h / 4);
    }

    EventHandlerState Menubar::MenuButton::onPaintEvent(const Event*)
    {
        if(!needsRepaint_) return Accepted;

        static constexpr Color defaultColor_ = 0x232323ff;
        static constexpr Color hoveredColor_ = 0x3a3a2aff;
        static constexpr Color pressedColor_ = 0x353535ff;

        Color drawColor = defaultColor_;
        if(hovered_) drawColor = hoveredColor_;
        if(pressed_) drawColor = pressedColor_;

        surface->drawRect({0, 0, rect_.w, rect_.h}, drawColor);
        
        int w = static_cast<int>(rect_.w);
        int h = static_cast<int>(rect_.h);

        surface->drawLine({0, 0}, {0, h}, (focused_ || hovered_) ? Colors::Red : Colors::LGray);
        surface->drawLine({0, h}, {w, h}, (focused_ || hovered_) ? Colors::Red : Colors::LGray);
        surface->drawLine({w, h}, {w, 0}, (focused_ || hovered_) ? Colors::Red : Colors::LGray);
        surface->drawLine({w, 0}, {0, 0}, (focused_ || hovered_) ? Colors::Red : Colors::LGray);
        
        surface->drawText(text_);
        needsRepaint_ = false;
        return Accepted;
    }

}
