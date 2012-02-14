/*
 * \file Main.cxx
 * \brief ManateeX Game Core
 * \author Thomas FOURCROY
 * \author Benoit Djerigian
 * \version 0.9
 * \date 14 fevrier 2012
 *
 * Programme pricipal de ManateeX
 * Gere les l'affichage et les deplacements
 *
 */

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <time.h>
#include "Map.hxx"
#include "Particle.hxx"
#include "Menu.hxx"
#include "MainMenu.hxx"
#include "OptionMenu.hxx"
#include "PopupMenu.hxx"
#include "Mob.hxx"
#include "Tower.hxx"
#include "Target.hxx"
#include "Building.hxx"

// Espace de nom SFML
using namespace sf;

// Variables globales
RenderWindow window(VideoMode(800, 600), "SFML window");
bool play=false;
std::vector<Particle *> part;
std::vector<Mob *> mobs;
std::vector<Tower *> tows;
Map m;
bool isPopped=false;
PopupMenu popup(0,0);
Music music;
SoundBuffer sbuffer;
int score;
int waveNbr;
int maxWave;
Target* manatee;

/**
 * \fn void GenerateWave()
 * \brief Genere et initialise les differentes vagues
 *  Genere un certain nombre d'ennemis a des positions aleatoires
 * de plus en plus d'ennemie au fur et a mesure des generations
 */
void GenerateWave()
{
  int mobNbr = (waveNbr+5) * 1.30;
  std::cout<<"init mobs... ";
  waveNbr++;
  srand(time(NULL));  
  for (int i=1; i<=mobNbr;i++)
    {
      int zone = rand()%4;
      std::cout<<"Zone = "<<zone<<" ";
      int x,y;
      switch(zone)
	{
	case 0:
	  x = rand()%790+5;
	  y = rand()%20+35;
	  break;
	case 1:
	  x = rand()%20+770;
	  y = rand()%560+5;
	  break;
	case 2:
	  x = rand()%790+5;
	  y = rand()%560+35;
	  break;
	case 3:
	  x = rand()%20+5;
	  y = rand()%560+35;
	}
      Vector2f v(x,y);
      mobs.insert(mobs.end(),new Mob(window,v,i));
    }
    for (std::vector<Mob *>::iterator MobsIt = mobs.begin(); MobsIt != mobs.end();MobsIt++) 
      {
	(*MobsIt)->AStar(m,40,30);
      }
    std::cout<<"done. nb ="<<mobNbr<<endl;
}

/**
 * \fn int Initiate()
 * \brief initialise les parametre de jeux
 * Initialise le score, le nombre de vagues, la musique et l'objectif  
 * 
 */
int Initiate()
{
  std::cout<<"Initiate game... "<<endl;
  score = 15000;
  waveNbr = 0;
  maxWave = 20;
  srand(time(NULL));
  music.Stop();
  
  if (!music.OpenFromFile("src/ressources/sounds/DP_Tron_Derezzed_chiptune.ogg"))
    return EXIT_FAILURE;
  music.Play();
  music.SetLoop(true);
  
  if (!sbuffer.LoadFromFile("src/ressources/sounds/laser.ogg"))
    return EXIT_FAILURE;
  manatee = new Target(window);
  play =true;
  std::cout<<"done."<<endl;
}

/**
 * \fn void UpdateParticles()
 * \brief Thread de controle les particules (missiles)
 * controle le deplacement des particules et gere la mort des mob.
 * 
 */
void UpdateParticles() 
{
  std::cout<<endl<<"Fire Controller Started."<<std::endl;
  while(!play);
  while(play) 
    {
      if (!part.empty())
	{
	  for (std::vector<Particle *>::iterator partIt = part.begin(); partIt != part.end();) 
	    {
	      int mobNbTmp;
	      if (!mobs.empty())
		{
		  std::vector<Mob *>::iterator mobsIt=mobs.begin();
		  mobNbTmp = (*partIt)->GetTargetNbr();
		  for (; mobsIt != mobs.end();) 
		    {
		      if ((*mobsIt)->GetID()==mobNbTmp)
			break;
		      ++mobsIt;
		    }
		  if((*mobsIt)->IsDead()) 
		    {
		      delete *partIt;
		      part.erase(partIt);	
		      continue;
		    }
		  else if ((*partIt)->IsDone()) 
		    {
		      (*mobsIt)->Hit((*partIt)->GetPower());
		      delete *partIt;
		      part.erase(partIt);
		      continue;
		    }
		  else 
		    {
		      (*partIt)->Update();
		      ++partIt;
		    }
		}
	    }
	}
      // environ 200 pixels/s
      usleep(5000);
    }
}

/**
 * \fn void UpdateTowsAndMobs()
 * \brief Thread de controle les Tours et des Mobs
 * Gere l'acquisition de cible et la mise a feu 
 * 
 */
void UpdateTowsAndMobs()
{
  std::cout<<endl<<"Tower Controller Started."<<std::endl;
  Sound fire;
  fire.SetBuffer(sbuffer);
  int i;
  while(!play);
  while(play) 
    {
      if (!mobs.empty())
	{
	  for (std::vector<Tower *>::iterator TowsIt = tows.begin(); TowsIt != tows.end();TowsIt++) 
	    {
	      if ((*TowsIt)->HasTarget())
		{
		  Mob* target=(*TowsIt)->GetTarget();
		  if (target->IsDead())
		    {
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
			  part.insert(part.end(),new Particle(window,p,(*TowsIt)->GetType(),target->GetPosition(),target->GetID()));		      
			  //			  fire.Play();	
			}
		    }
		}
	      else 
		{
		  int i = 0;
		  for (std::vector<Mob *>::iterator mobsIt = mobs.begin(); mobsIt != mobs.end();) 
		    {
		      if ((*TowsIt)->InRange((*mobsIt)->GetPosition()))
			{
			  if (!(*mobsIt)->IsDead())
			    {
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
	      (*mobsIt)->Update();
	      if ((*mobsIt)->IsDead())
		{
		  delete *mobsIt;
		  mobs.erase(mobsIt);
		  score = score + 1000;
		  continue;
		}
	      if((*mobsIt)->HasArrived())
		{
		  std::cout<<"Oh nooo! Manatee a été mordu!"<<std::endl;
		  manatee->Hit((*mobsIt)->GetHP());
		  delete *mobsIt;
		  mobs.erase(mobsIt);
		  continue;
		}
	      ++mobsIt;
	    }
	}
      else 
	{
	  for (std::vector<Tower *>::iterator TowsIt = tows.begin(); TowsIt != tows.end();TowsIt++) 
	    (*TowsIt)->ReleaseTarget();
	  sleep(10);
	  GenerateWave();
	}
      // environ 6 pixels/s
      usleep(150000);
    }
}

/**
 * \fn int Game (void)
 * \brief Thread Principal
 * Gere l'affichage, les evenements, la construction de tours 
 * 
 */
int Game (void)
{
  int x,y;
  Font font;
  Initiate();
  std::cout<<"Launching Threads... ";
  // threads
  Thread partUpd(&UpdateParticles);
  partUpd.Launch();
  Thread mobUpd(&UpdateTowsAndMobs);
  mobUpd.Launch();
  std::cout<<"Threads Launched."<<endl;
  if (!font.LoadFromFile("src/ressources/Computerfont.ttf"))
    return EXIT_FAILURE;
  Text text("0000", font, 20);
  text.SetPosition(10,5);

  while(window.IsOpen()&&play&&!manatee->IsDead()) {
    Event event;
    window.Clear();
    m.Redraw(window);
    // dessine les projectiles (a mettre en fcontion peut etre)
    for (std::vector<Particle *>::iterator partIt = part.begin(); partIt != part.end();partIt++) 
      {
    	if (!(*partIt)->IsDone())
    	  (*partIt)->Render();
      }
    // Desine les mobs
    for (std::vector<Mob *>::iterator MobsIt = mobs.begin(); MobsIt != mobs.end();MobsIt++) 
      {
	if (! (*MobsIt)->IsDead())
	  (*MobsIt)->Render();
      }
    //dessine les towers
    for (std::vector<Tower *>::iterator TowsIt = tows.begin(); TowsIt != tows.end();TowsIt++) 
      {
	(*TowsIt)->Render();
      }
    // Dessine l'objectif
    manatee->Render();
    // affiche le score    
    if (score>=0) 
      {
	ostringstream oss;
	oss << "Score : ";
	if (score < 10)
	  oss << 0 << 0 << 0 <<score ;
	else if (score<100)
	  oss << 0 << 0 << score;
	else if (score<1000)
	  oss << 0 << score;
	else oss << score;
	oss<<"      Wave: "<<waveNbr<<"/"<<maxWave;
	oss<<"      Manatee's Life : "<<manatee->GetHP();
	text.SetString( oss.str());
      }
    while (window.PollEvent(event)) {
      if (event.Type == Event::Closed) window.Close();
      if (event.Type == Event::MouseButtonPressed) 
	{
	  Vector2i pos = Mouse::GetPosition(window);
	  x = pos.x;
	  y = pos.y;
	  // selection case
	  Square* tmp = m.GetSquarePixel(pos.x,pos.y);
	  Square* tmp2;
	  if(!isPopped) m.Select(tmp);
	  // si click droit
	  if (event.MouseButton.Button == Mouse::Right) 
	    {
	      popup.SetPosition(x,y);
	      isPopped=true;
	      tmp2 = tmp;			
	    }
	  //si click gauche
	  if (event.MouseButton.Button == Mouse::Left)
	    {
	      // test clic sur bouton du menu popup s'il existe
	      if(isPopped) {
		for(int i=0;i<5;i++) {
		  if(popup.button[i].GetGlobalBounds().Contains(event.MouseButton.X,event.MouseButton.Y)) {
		    if(popup.button[i].GetString()=="Tour1")
		      { 
			if(tmp2->IsConstructible())
			  {
			    if (score >= 2000) 
			      {
				tows.insert(tows.end(), new Tower(window,tmp2->GetPosition(),1,1));
				// 9x9 non constructible
				for(int j=-1;j<=1;j++)
				  {
				    for(int k=-1;k<=1;k++)
				      {
					m.GetSquarePixel(tmp2->GetPosition().x + 10*j, tmp2->GetPosition().y + 10*k)->SetConstructible(false);
				      }
				  }
				score = score - 5000;
			      }
			    else
			      cout<<"Not enough money!"<<tmp->number<<endl;
			  }
			else 
			  cout<<"Cannot build here !"<<endl;	
		      }
		    if(popup.button[i].GetString()=="Tour2")
		      { 
			if(tmp2->IsConstructible())
			  {
			    if (score >= 2000) 
			      {
				tows.insert(tows.end(), new Tower(window,tmp2->GetPosition(),1,2));
				// 9x9 non constructible
				for(int j=-1;j<=1;j++)
				  {
				    for(int k=-1;k<=1;k++)
				      {
					m.GetSquarePixel(tmp2->GetPosition().x + 10*j, tmp2->GetPosition().y + 10*k)->SetConstructible(false);
				      }
				  }
				score = score - 5000;
			      }
			    else
			      cout<<"not enough money!"<<tmp->number<<endl;
			  }
			else
			  cout<<"Cannot build here !"<<endl;
		      }
		  }
		}
	      }
	      isPopped=false;
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
	      // Touche debug
	    case Keyboard::I:
	      for (std::vector<Tower *>::iterator TowsIt = tows.begin(); TowsIt != tows.end();TowsIt++) 
		{
		  std::cout<<"Tows : "<<(*TowsIt)->GetPos().x<<":"<<(*TowsIt)->GetPos().y<<"  "<<std::endl;
		}
	      break;
	      // Volume de la musique (keypad)
	    case Keyboard::Subtract:
	      music.SetVolume(music.GetVolume()-10);
	      break;
	    case Keyboard::Add:
	      music.SetVolume(music.GetVolume()+10);
	      break;
	     }
	}
    }
    usleep(20000);
    window.Draw(text);
    if(isPopped) popup.Render(window);
    window.Display();
  }
  play = false;
}

/**
 * \fn int main(void)
 * \brief Thread Principal (menus)
 * Gere l'affichage des menus
 * 
 */
int main(void)
{
  MainMenu mainMenu;
  OptionMenu optionMenu;
  Menu *currentMenu = &mainMenu;
  if (!music.OpenFromFile("src/ressources/sounds/Tron1.ogg"))
    return EXIT_FAILURE;
  music.Play();
  music.SetLoop(true);
  while(window.IsOpen()) {
    Event event;
    while (window.PollEvent(event)) {
      if (event.Type == Event::Closed) window.Close();
      if (event.Type == Event::MouseButtonPressed) {
	for(int i=0;i<5;i++) {
	  if(currentMenu->button[i].GetGlobalBounds().Contains(event.MouseButton.X,event.MouseButton.Y)) {
	    if(currentMenu->button[i].GetString()=="Options") currentMenu = &optionMenu;
	    if(currentMenu->button[i].GetString()=="PLAY") {window.Clear();Game();
	    }
	    if(currentMenu->button[i].GetString()=="Retour") currentMenu = &mainMenu;
	    if(currentMenu->button[i].GetString()=="Quitter") window.Close();
	  }
	}
      }
      if (event.Type == Event::KeyPressed) 
	{
	  switch(event.Key.Code)
	    {
	    case Keyboard::Q:
	      window.Close();
	      break;
	    case Keyboard::O:
	      currentMenu = &optionMenu;
	      break;
	    case Keyboard::P:
	      window.Clear();
	      Game();
	     }
	}
    }
    usleep(30000);
    window.Clear();
    currentMenu->Render(window);
    window.Display();
  }
  window.Clear();
  window.Close();
  return (EXIT_SUCCESS);
}
