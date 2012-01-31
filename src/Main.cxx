#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "Map.hxx"
#include "Particle.hxx"
#include "Menu.hxx"
#include "MainMenu.hxx"
#include "OptionMenu.hxx"

#include "Mob.hxx"
#include "Tower.hxx"
#include "Batiment.hxx"

using namespace sf;

RenderWindow window(VideoMode(800, 600), "SFML window");


bool play=false;
std::vector<Particle *> part;
std::vector<Mob *> mobs;
std::vector<Batiment *> tows;


Music music;
SoundBuffer sbuffer;


int init()
{
  if (!sbuffer.LoadFromFile("src/ressources/sounds/laser.ogg"))
    return EXIT_FAILURE;
  Vector2f p1(200,230);

  Vector2f p2(450,430);

  Vector2f p3(700,500);
  
  //  part.insert(part.end(),new Particle(window,p1,1));
  //part.insert(part.end(),new Particle(window,p2,2));

  mobs.insert(mobs.end(),new Mob(window,p3));

  tows.insert(tows.end(), new Tower(window,p1,1,1));
  tows.insert(tows.end(), new Tower(window,p2,2,2));

}

  

void updateParticles() 
{
  // Thread update position des projectiles
  std::cout<<"update"<<std::endl;
  while(play) 
    {
      if (!part.empty())
	{
	  
	  for (std::vector<Particle *>::iterator partIt = part.begin(); partIt != part.end();) 
	    {
	      if ((*partIt)->isDone()){
		if(!mobs.empty())
		  mobs[(*partIt)->GetCibleNbr()]->Hit((*partIt)->GetPower());
		delete *partIt;
		part.erase(partIt);
		continue;
	      }
	      else 
		{
		  (*partIt)->update();
		  ++partIt;
		}
	      
	    }
	}
      
      usleep(5000);
      
    }
}

void updateMobs() 
{
  Sound fire;
  fire.SetBuffer(sbuffer);
  int i;
  
  // Thread update position des mob
  while(play) 
    {
      if (!mobs.empty())
	{
	  
	  i=0;
      
	  for (std::vector<Mob *>::iterator mobsIt = mobs.begin(); mobsIt != mobs.end();) 
	    {
	      if ((*mobsIt)->IsDead())
		{
		  delete *mobsIt;
		  mobs.erase(mobsIt);
		  std::cout<<"died"<<std::endl;
		  
		  continue;
		}
	      else 
		{
		  (*mobsIt)->update();
		  // TODO:
		  // for each tower
		  // if mob in range()
		  // insert new tower.particle
		  for (std::vector<Batiment *>::iterator TowsIt = tows.begin(); TowsIt != tows.end();TowsIt++) 
		    {
		      if ((*TowsIt)->InRange((*mobsIt)->getPosition()))
			{
			  Vector2f p = (*TowsIt)->GetPos();
			  part.insert(part.end(),new Particle(window,p,(*TowsIt)->GetType(),(*mobsIt)->getPosition(),i));		      
			  fire.Play();

			}
		      
		    }
		  i++;

		  

		  

		  ++mobsIt;
		  
		}
	      
	    }
	}
      
      usleep(250000);
	
      
    }
}


int game (void) {
  
  Map m;
  int x,y;

  init();
  
  // threads
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
	if (! (*MobsIt)->IsDead())
	  (*MobsIt)->render();

      }
    //dessine les towers
    for (std::vector<Batiment *>::iterator TowsIt = tows.begin(); TowsIt != tows.end();TowsIt++) 
      {

	(*TowsIt)->render();

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
	      mobs.insert(mobs.end(),new Mob(window,(Vector2f) pos));
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
  if (!music.OpenFromFile("src/ressources/sounds/toto.ogg"))
    return EXIT_FAILURE;
  music.Play();
  music.SetLoop(true);
  
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
