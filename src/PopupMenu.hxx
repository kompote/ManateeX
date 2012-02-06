#ifndef _POPUPMENU_HXX
#define _POPUPMENU_HXX

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>

#include "Menu.hxx"

using namespace sf;

class PopupMenu : public Menu {

private :
	int _x;
	int _y;

public :
    PopupMenu(int x, int y);
    virtual void Render(RenderTarget& target) const;
	Vector2f GetPosition();
	void SetPosition(int x, int y);
};

#endif
