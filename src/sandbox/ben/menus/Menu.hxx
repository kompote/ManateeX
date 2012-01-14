#ifndef _MENU_HXX
#define _MENU_HXX

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>

using namespace sf;

class Menu {

protected :
    Sprite bgSprite;
    Texture bgTexture;
	Font font;
	Text title;

public :
	Text button[5];

    Menu();
    virtual void Affiche(RenderTarget& target) const=0;
};

#endif
