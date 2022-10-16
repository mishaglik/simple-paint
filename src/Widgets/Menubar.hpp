#ifndef WIDGETS_MENUBAR_HPP
#define WIDGETS_MENUBAR_HPP
#include <Widgets/ContainerWidget.hpp>
#include <Widgets/Button.hpp>

namespace aGL {

    class Menubar : public ContainerWidget
    {
    public:
        class MenuButton;
        class Menu;

        Menubar(uint32_t x, uint32_t y, uint32_t w, uint32_t h);
        ~Menubar() override;

        size_t addMenuEntry(const char* name);
        
        const mvc::Vector<Menu*>& entries() const {return menus_;}

        Menu* operator[](size_t i) const { return menus_[i]; }

        bool hasEventPoint(const Point& pt) override;
        virtual void render(const Window& ) const override;


    private:
        mvc::Vector<Menu*> menus_;
        Menu* activeMenu = nullptr;

        void setActiveMenu(Menu* menu);
        void setNoActiveMenu() {activeMenu = nullptr;}
    };

    class Menubar::Menu : public Widget
    {
    public:
        Menu(uint32_t x, uint32_t y, uint32_t w, uint32_t h, const char* name, EventManager* mgr);
        ~Menu() override;

        EventHandlerState onPaintEvent(const Event* ) override;
        virtual void render(const Window& ) const override;
        
        void show() { if(!isActive_) activated.emit(this); isActive_ = true; }
        void hide() { isActive_ = false; deactivated.emit(); }
        void toggle() { isActive_ = !isActive_; (isActive_ ? activated.emit(this) : deactivated.emit()); }

        bool hasEventPoint(const Point& pt) override;

        const mvc::Vector<MenuButton*>& buttons() const {return buttons_;}

        size_t addMenuEntry(const char* text);

        Signal<Menu*> activated;
        Signal<> deactivated;

    private:
        EventManager* emgr_ = nullptr;
        bool isActive_ = false;

        MenuButton* mainButton = nullptr;
        mvc::Vector<MenuButton* > buttons_; 
        
    };
    

    class Menubar::MenuButton : public AbstractButton
    {
    public:
        MenuButton(uint32_t x, uint32_t y, uint32_t w, uint32_t h, const char* text);
        virtual EventHandlerState onPaintEvent(const Event*) override;
    private:
    };

}

#endif /* WIDGETS_MENUBAR_HPP */
