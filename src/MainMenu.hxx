#ifndef _MAINMENU_HXX
#define _MAINMENU_HXX

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>

#include "Menu.hxx"

using namespace sf;

class MainMenu : public Menu {

public :
    MainMenu();
    virtual void Render(RenderTarget& target) const;
};

#endif
