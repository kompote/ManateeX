#include "PopupMenu.hxx"

using namespace sf;

PopupMenu::PopupMenu(int x, int y) {

	this->x = x;
	this->y = y;

	bgTexture.LoadFromFile("src/ressources/images/fondpopup.png");

    bgSprite.SetTexture(bgTexture);
    bgSprite.SetPosition(x,y);

    //font.LoadFromFile("/usr/share/fonts/truetype/freefont/FreeMonoBold.ttf");
  	font.LoadFromFile("src/ressources/ARCADE_N.TTF");	
	title.SetString("Creer");
	title.SetFont(font);
	title.SetCharacterSize(12);
	title.SetPosition(x+40-title.GetGlobalBounds().Width/2,y+5);
	title.SetColor(Color::Black);

	button[0].SetString("Tour");
	button[0].SetFont(font);
	button[0].SetCharacterSize(10);
	button[0].SetPosition(x+40-button[0].GetGlobalBounds().Width/2,y+30);
	button[0].SetColor(Color::Black);

	button[1].SetString("Mob");
	button[1].SetFont(font);
	button[1].SetCharacterSize(10);
	button[1].SetPosition(x+40-button[1].GetGlobalBounds().Width/2,y+50);
	button[1].SetColor(Color::Black);
}

void PopupMenu::Affiche(RenderTarget& target) const {
    target.Draw(bgSprite);
	target.Draw(title);
	for(int i=0;i<5;i++) target.Draw(button[i]);
}

Vector2f PopupMenu::getPosition() {
	Vector2f *vec = new Vector2f(x,y);
	return *vec;
}

void PopupMenu::setPosition(int x, int y) {
	this->x=x;
	this->y=y;

	bgSprite.SetPosition(x,y);
	title.SetPosition(x+40-title.GetGlobalBounds().Width/2,y+5);
	for(int i=0;i<5;i++) button[i].SetPosition(x+40-button[i].GetGlobalBounds().Width/2,y+30+15*i);
}
