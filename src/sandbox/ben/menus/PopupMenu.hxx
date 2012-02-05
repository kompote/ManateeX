#ifndef _POPUPMENU_HXX
#define _POPUPMENU_HXX

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>

#include "Menu.hxx"

using namespace sf;

class PopupMenu : public Menu {

private :
	int x;
	int y;

public :
    PopupMenu(int x, int y);
    virtual void Affiche(RenderTarget& target) const;
	Vector2i getPosition();
	void setPosition(int x, int y);
};

#endif
