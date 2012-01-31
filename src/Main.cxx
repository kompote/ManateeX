#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "Map.hxx"
#include "Particle.hxx"
#include "Menu.hxx"
#include "MainMenu.hxx"
#include "OptionMenu.hxx"



using namespace sf;

RenderWindow window(VideoMode(800, 600), "SFML window");

std::vector<Particle *> part;
bool play=false;





void init()
{
  // Creer les depart des tirs, cad emplacement des towers

  Vector2f p1(200,230);
  Vector2f p2(450,430);
  
  part.insert(part.end(),new Particle(window,p1,1));
  part.insert(part.end(),new Particle(window,p2,2));
}

  

void updatePos() 
{
  // Thread update position des projectiles
  std::cout<<"update"<<std::endl;
  while(play) 
    {
      for (std::vector<Particle *>::iterator partIt = part.begin(); partIt != part.end();partIt++) 
	{
	  
	  (*partIt)->update();
	  
	}
      usleep(3000);
      
    }
}


int game (void) {
  
  Map m;
  int x,y;

  init();
  

  Thread tt(&updatePos);


  tt.Launch();
  
  while(window.IsOpen()&&play) {
    Event event;
    m.Redraw(window);
    // dessine les projectiles (a mettre en fcontion peut etre)
    for (std::vector<Particle *>::iterator partIt = part.begin(); partIt != part.end();partIt++) 
      {
	(*partIt)->render();

      }

    
    while (window.PollEvent(event)) {
      // Window closed
      if (event.Type == Event::Closed) window.Close();

      if (event.Type == Event::MouseButtonReleased) 
	{

	  Vector2i pos = Mouse::GetPosition(window);
	  x = pos.x;
	  y = pos.y;
	  std::cout<<"("<<pos.x<<":"<<pos.y<<")"<<endl;
	  Case* tmp = m.getCasePixel(pos.x,pos.y);
	  std::cout<<"case n° "<<tmp->number<<endl;
	  m.Select(tmp);

	  // si click droit
	  if (event.MouseButton.Button == Mouse::Right) 
	    {
	      // update cible (pout test)
	      for (std::vector<Particle *>::iterator partIt = part.begin(); partIt != part.end();partIt++) 
		{
		  
		  (*partIt)->Bresenham(x,y);
		}
	      
	      cout<<"menu contex"<<endl;
	    }
	  
	  //si click gauche
	  if (event.MouseButton.Button == Mouse::Left)
	    {
	      cout<<"information on case n° "<<tmp->number<<endl;

	    }
	}

      if (event.Type == Event::KeyPressed) 
	{
	  switch(event.Key.Code)
	    {
	    case Keyboard::Q:
	      play=false;
	      for (std::vector<Particle *>::iterator partIt = part.begin(); partIt != part.end();partIt++) 
		{
		  
		  delete *partIt;
		}
	      part.clear();
	      
	      std::cout<<"return to main menu"<<endl;
	      
	      return 1;
	      
	      
	     
	    case Keyboard::M:

	      
	      break;
	     }

	}

    }

    usleep(20000);

    window.Display();
  }
}

int main(void) {

  //    RenderWindow window(VideoMode(800, 600), "ManateeX Project");

    MainMenu mainMenu;
    OptionMenu optionMenu;
    Menu *currentMenu = &mainMenu;
    

	while(window.IsOpen()) {
		Event event;
		while (window.PollEvent(event)) {
			// Window closed
			if (event.Type == Event::Closed) window.Close();
			// Button clicked
			if (event.Type == Event::MouseButtonPressed) {

			  
				for(int i=0;i<5;i++) {
					if(currentMenu->button[i].GetGlobalBounds().Contains(event.MouseButton.X,event.MouseButton.Y)) {
						if(currentMenu->button[i].GetString()=="Options") currentMenu = &optionMenu;
						if(currentMenu->button[i].GetString()=="PLAY") {play=true;game();
						}
						
						if(currentMenu->button[i].GetString()=="Retour") currentMenu = &mainMenu;
						if(currentMenu->button[i].GetString()=="Quitter") window.Close();
					}
				}
			}
		}
		usleep(10000);
		// Update the window
		window.Clear();
		currentMenu->Affiche(window);
       	window.Display();
	}

	window.Clear();
	window.Close();

    return (EXIT_SUCCESS);
}
