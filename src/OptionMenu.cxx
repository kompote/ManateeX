#include "OptionMenu.hxx"

OptionMenu::OptionMenu() {
	
  //font.LoadFromFile("/usr/share/fonts/truetype/freefont/FreeMonoBold.ttf");
  font.LoadFromFile("src/ressources/ARCADE_N.TTF");
	
	title.SetString("Options");
	title.SetFont(font);
	title.SetCharacterSize(60);
	title.SetPosition(400-title.GetGlobalBounds().Width/2,20);
	title.SetColor(Color::Black);

	button[0].SetString("Retour");
	button[0].SetFont(font);
	button[0].SetPosition(200-button[0].GetGlobalBounds().Width/2,500);
	button[0].SetColor(Color::Black);
}

void OptionMenu::Affiche(RenderTarget& target) const {
    target.Draw(bgSprite);
	target.Draw(title);
	for(int i=0;i<5;i++) target.Draw(button[i]);
}
