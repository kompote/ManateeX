#include "Menu.hxx"

Menu::Menu() {
	bgTexture.LoadFromFile("src/ressources/images/fondmenu.png");

    bgSprite.SetTexture(bgTexture);
    bgSprite.SetPosition(0,0);
}
