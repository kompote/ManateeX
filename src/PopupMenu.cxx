#include "PopupMenu.hxx"

using namespace sf;

PopupMenu::PopupMenu(int x, int y) {

	_x = x;
	_y = y;

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

	button[0].SetString("Tour1");
	button[0].SetFont(font);
	button[0].SetCharacterSize(10);
	button[0].SetPosition(x+40-button[0].GetGlobalBounds().Width/2,y+30);
	button[0].SetColor(Color::Black);

	button[1].SetString("Tour2");
	button[1].SetFont(font);
	button[1].SetCharacterSize(10);
	button[1].SetPosition(x+40-button[1].GetGlobalBounds().Width/2,y+30);
	button[1].SetColor(Color::Black);

	// button[2].SetString("Mob");
	// button[2].SetFont(font);
	// button[2].SetCharacterSize(10);
	// button[2].SetPosition(x+40-button[2].GetGlobalBounds().Width/2,y+50);
	// button[2].SetColor(Color::Black);
}

void PopupMenu::Render(RenderTarget& target) const {
    target.Draw(bgSprite);
	target.Draw(title);
	for(int i=0;i<5;i++) target.Draw(button[i]);
}

Vector2f PopupMenu::GetPosition() {
	Vector2f *vec = new Vector2f(_x,_y);
	return *vec;
}

void PopupMenu::SetPosition(int x, int y) {
	_x=x;
	_y=y;

	bgSprite.SetPosition(x,y);
	title.SetPosition(x+40-title.GetGlobalBounds().Width/2,y+5);
	for(int i=0;i<5;i++) button[i].SetPosition(x+40-button[i].GetGlobalBounds().Width/2,y+30+15*i);
}
