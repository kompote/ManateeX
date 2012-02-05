#include "PopupMenu.hxx"

using namespace sf;

PopupMenu::PopupMenu(int x, int y) {

	this->x = x;
	this->y = y;

	bgTexture.LoadFromFile("fondpopup.png");

    bgSprite.SetTexture(bgTexture);
    bgSprite.SetPosition(x,y);

    font.LoadFromFile("/usr/share/fonts/truetype/freefont/FreeMonoBold.ttf");
  	//font.LoadFromFile("ARCADE_N.TTF");	
	title.SetString("Action");
	title.SetFont(font);
	title.SetCharacterSize(16);
	title.SetPosition(x+40-title.GetGlobalBounds().Width/2,y+5);
	title.SetColor(Color::Black);

	button[0].SetString("PLAY");
	button[0].SetFont(font);
	button[0].SetCharacterSize(12);
	button[0].SetPosition(x+40-button[0].GetGlobalBounds().Width/2,y+30);
	button[0].SetColor(Color::Black);

	button[1].SetString("Options");
	button[1].SetFont(font);
	button[1].SetCharacterSize(12);
	button[1].SetPosition(x+40-button[1].GetGlobalBounds().Width/2,y+50);
	button[1].SetColor(Color::Black);

	button[2].SetString("Quitter");
	button[2].SetFont(font);
	button[2].SetCharacterSize(12);
	button[2].SetPosition(x+40-button[2].GetGlobalBounds().Width/2,y+70);
	button[2].SetColor(Color::Black);
}

void PopupMenu::Affiche(RenderTarget& target) const {
    target.Draw(bgSprite);
	target.Draw(title);
	for(int i=0;i<5;i++) target.Draw(button[i]);
}

Vector2i PopupMenu::getPosition() {
	Vector2i *vec = new Vector2i(x,y);
	return *vec;
}

void PopupMenu::setPosition(int x, int y) {
	this->x=x;
	this->y=y;

	bgSprite.SetPosition(x,y);
	title.SetPosition(x+40-title.GetGlobalBounds().Width/2,y+5);
	for(int i=0;i<5;i++) button[i].SetPosition(x+40-button[i].GetGlobalBounds().Width/2,y+30+15*i);
}
