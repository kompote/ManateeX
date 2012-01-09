#ifndef _MAINMENU_HXX
#define	_MAINMENU_HXX

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>

using namespace sf;

class MainMenu {

private :
    Sprite background;
    Texture imgfond;

public :
    MainMenu();
    void Affiche(RenderTarget& target) const;
};

#endif

