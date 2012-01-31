#include "MainMenu.hxx"

MainMenu::MainMenu() {

  //	font.LoadFromFile("/usr/share/fonts/truetype/freefont/FreeMonoBold.ttf");
  font.LoadFromFile("src/ressources/ARCADE_N.TTF");	
	title.SetString("ManateeX Project");
	title.SetFont(font);
	title.SetCharacterSize(60);
	title.SetPosition(400-title.GetGlobalBounds().Width/2,20);
	title.SetColor(Color::Black);

	button[0].SetString("PLAY");
	button[0].SetFont(font);
	button[0].SetCharacterSize(40);
	button[0].SetPosition(400-button[0].GetGlobalBounds().Width/2,350);
	button[0].SetColor(Color::Black);

	button[1].SetString("Options");
	button[1].SetFont(font);
	button[1].SetPosition(400-button[1].GetGlobalBounds().Width/2,450);
	button[1].SetColor(Color::Black);

	button[2].SetString("Quitter");
	button[2].SetFont(font);
	button[2].SetPosition(400-button[2].GetGlobalBounds().Width/2,550);
	button[2].SetColor(Color::Black);
}

void MainMenu::Affiche(RenderTarget& target) const {
    target.Draw(bgSprite);
	target.Draw(title);
	for(int i=0;i<5;i++) target.Draw(button[i]);
}
