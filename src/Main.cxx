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

  // Tests
  Vector2f p1(200,230);
  Vector2f p2(450,430);
  Vector2f p3(700,500);

  //  mobs.insert(mobs.end(),new Mob(window,p3));

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
	      int mobNbTmp;
	      if (!mobs.empty())
		{
		  
		  mobNbTmp = (*partIt)->GetCibleNbr();
		  
		  if(mobs[mobNbTmp]->IsDead()) 
		    {
		      part.erase(partIt);	
		      continue;
		    }
		  
		  else if ((*partIt)->isDone()) 
		    {
		      mobs[mobNbTmp]->Hit((*partIt)->GetPower());
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
	}
      // environ 200 pixels/s
      usleep(5000);
      
    }
}




void UpdateTows()
{
  Sound fire;
  fire.SetBuffer(sbuffer);
  int i;

  // Thread update tours/mobs

  while(play) 
    {
      if (!mobs.empty())
	{

	  for (std::vector<Batiment *>::iterator TowsIt = tows.begin(); TowsIt != tows.end();TowsIt++) 
	    {

	      // doit compter les mob pour que les particules les retrouve
	      if ((*TowsIt)->HasTarget())
		{

		  Mob* target=(*TowsIt)->GetTarget();
	
		  if (target->IsDead())
		    {
		      std::cout<<"release target"<<std::endl;
		      (*TowsIt)->ReleaseTarget();
		    }
		  else 
		    {
		      Vector2f p = (*TowsIt)->GetPos();
		      if ((*TowsIt)->CanShoot()) 
			{
			  // TOFIX:
			  // rate sa cible,
			  // recuperer quelques cases d'avance
			  part.insert(part.end(),new Particle(window,p,(*TowsIt)->GetType(),target->getPosition(),target->GetID()));		      
			  fire.Play();	
			}
		      
		    }
		  
		}
	      else 
		{

		  int i = 0;
		  for (std::vector<Mob *>::iterator mobsIt = mobs.begin(); mobsIt != mobs.end();) 
		    {

		  
		      if ((*TowsIt)->InRange((*mobsIt)->getPosition()))
			{
			  if (!(*mobsIt)->IsDead())
			    {
			      std::cout<<"aquire target"<<std::endl;
			      (*TowsIt)->SetTarget(*mobsIt);
			    }
			  
			}
		      ++mobsIt;
		      i++;
		    }
		}
	      
	    }
	  
	  for (std::vector<Mob *>::iterator mobsIt = mobs.begin(); mobsIt != mobs.end();) 
	    {
	      (*mobsIt)->update(i);
	      if ((*mobsIt)->IsDead())
		{
		  std::cout<<"erase"<<std::endl;
		  mobs.erase(mobsIt);
		  continue;
		  
		}
		  
	      ++mobsIt;

	    }
	}
      // environ 6 pixels/s
      usleep(150000);
    }
}


int game (void) {
  
  Map m;
  int x,y;

  init();
  
  // threads
  Thread partUpd(&updateParticles);
  partUpd.Launch();
  Thread mobUpd(&UpdateTows);
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
	      // ajout cible (pout test)
	      mobs.insert(mobs.end(),new Mob(window,(Vector2f) pos));
	      //cout<<"menu contex"<<endl;
	    }
	  
	  //si click gauche
	  if (event.MouseButton.Button == Mouse::Left)
	    {
	      //	      cout<<"information on case n° "<<tmp->number<<endl;
	      //	      tows.insert(tows.end(), new Tower(window,(Vector2f) pos,2,2));

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
	      // TODO:
	      // Faire pareil avec les tows et mobs
	      std::cout<<"return to main menu"<<endl;
	      
	      return 1;
	    case Keyboard::I:
	      std::cout<<"Tower: "<<tows[0]->GetPos().x<<std::endl;
	      //	      std::cout<<"Test "<<mobs.max_size()<<std::endl;
	      
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
