#include "Menu.hxx"

Menu::Menu() {
	bgTexture.LoadFromFile("fondmenu.png");

    bgSprite.SetTexture(bgTexture);
    bgSprite.SetPosition(0,0);
}
