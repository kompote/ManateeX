#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "Map.hxx"
#include "Particle.hxx"
#include "Menu.hxx"
#include "MainMenu.hxx"
#include "OptionMenu.hxx"

#include "Mob.hxx"


using namespace sf;

RenderWindow window(VideoMode(800, 600), "SFML window");


bool play=false;
std::vector<Particle *> part;
std::vector<Mob *> mobs;




void init()
{

  Vector2f p1(200,230);

  Vector2f p3(700,500);
  
  //  part.insert(part.end(),new Particle(window,p1,1));
  //part.insert(part.end(),new Particle(window,p2,2));

  mobs.insert(mobs.end(),new Mob(window,p3));
}

  

void updateParticles() 
{
  // Thread update position des projectiles
  std::cout<<"update"<<std::endl;
  while(play) 
    {
      if (!part.empty())
	{
	  
	  for (std::vector<Particle *>::iterator partIt = part.begin(); partIt != part.end();partIt++) 
	    {
	      if ((*partIt)->isDone()){delete *partIt; part.erase(partIt); continue;
	      }
	      (*partIt)->update();
	  
	    }
	}
      
      usleep(5000);
      
    }
}

void updateMobs() 
{
  // Thread update position des mob
  //  std::cout<<"update"<<std::endl;
  Vector2f p2(450,430);
  while(play) 
    {
      for (std::vector<Mob *>::iterator mobsIt = mobs.begin(); mobsIt != mobs.end();mobsIt++) 
	{
	  
	  (*mobsIt)->update();
	  //std::cout<<(*mobsIt)->getPosition().x<<endl;//(*mobsIt)->getPosition().y);
	  part.insert(part.end(),new Particle(window,p2,2,(*mobsIt)->getPosition()));

	}
      usleep(250000);
      
    }
}


int game (void) {
  
  Map m;
  int x,y;

  init();
  

  Thread partUpd(&updateParticles);
  partUpd.Launch();
  Thread mobUpd(&updateMobs);
  mobUpd.Launch();
  
  while(window.IsOpen()&&play) {
    Event event;
    m.Redraw(window);
    // dessine les projectiles (a mettre en fcontion peut etre)
    for (std::vector<Particle *>::iterator partIt = part.begin(); partIt != part.end();partIt++) 
      {
    	if (!(*partIt)->isDone())
    	  (*partIt)->render();

      }
    // Desine les mobs
    for (std::vector<Mob *>::iterator MobsIt = mobs.begin(); MobsIt != mobs.end();MobsIt++) 
      {
	(*MobsIt)->render();

      }

    
    while (window.PollEvent(event)) {
      // Window closed
      if (event.Type == Event::Closed) window.Close();

      if (event.Type == Event::MouseButtonReleased) 
	{

	  Vector2i pos = Mouse::GetPosition(window);
	  x = pos.x;
	  y = pos.y;

	  // selection case
	  Case* tmp = m.getCasePixel(pos.x,pos.y);
	  m.Select(tmp);

	  // si click droit
	  if (event.MouseButton.Button == Mouse::Right) 
	    {
	      // update cible (pout test)
	      
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
	      // q pour retourner au menu
	      play=false;
	      for (std::vector<Particle *>::iterator partIt = part.begin(); partIt != part.end();partIt++) 
		{
		  
		  delete *partIt;
		}
	      part.clear();
	      
	      std::cout<<"return to main menu"<<endl;
	      
	      return 1;

	     }

	}

    }

    usleep(20000);

    window.Display();
  }
}

int main(void) {

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
    usleep(30000);
    // Update the window
    window.Clear();
    currentMenu->Affiche(window);
    window.Display();
  }

  window.Clear();
  window.Close();

  return (EXIT_SUCCESS);
}
