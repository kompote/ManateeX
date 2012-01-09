#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "Map.hxx"
using namespace sf;
int main (void) {

	Map m;

	RenderWindow window(VideoMode(800, 600), "SFML window");

	//Affichage Map
	for(int i=0;i<60;i++) {
		for(int j=0;j<80;j++) {
			//std::cout<<"["<<i<<";"<<j<<"]"<<endl;
			Texture terrain;
			terrain.LoadFromFile(m.getCase(j,i).getTexturePath());
			Sprite caseSprite(terrain);
			caseSprite.SetPosition(j*10,i*10);
			window.Draw(caseSprite);
		}
	}

	while(window->IsOpened()) {
		Event event;
		while (window->PollEvent(event)) {
	  		// Window closed
	  		if (event.Type == Event::Closed) window->Close();
		}

		usleep(10000);
      		// Update the window
      		window->Display();
	}
}
