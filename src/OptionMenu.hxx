#ifndef _OPTIONMENU_HXX
#define _OPTIONMENU_HXX

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>

#include "Menu.hxx"

using namespace sf;

class OptionMenu : public Menu {

public :
    OptionMenu();
    virtual void Render(RenderTarget& target) const;
};

#endif
