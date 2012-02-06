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
#include "Building.hxx"

using namespace sf;

RenderWindow window(VideoMode(800, 600), "SFML window");


bool play=false;
std::vector<Particle *> part;
std::vector<Mob *> mobs;
std::vector<Building *> tows;

bool isPopped=false;
PopupMenu popup(0,0);

Music music;
SoundBuffer sbuffer;

int score;
int waveNbr;

void GenWave()
{
  int mobNbr = (waveNbr+1) * 1.30;
  std::cout<<"nb :"<<mobNbr<<endl;
  
  waveNbr++;
  
  for (int i=1; i<=mobNbr;i++)
    {
      int zone = rand()%4;
      int x,y;
      
      switch(zone)
	{
	case 0:
	  x = rand()%790+5;
	  y = rand()%20+5;
	  break;
	  
	case 1:
	  x = rand()%20+770;
	  y = rand()%590+5;
	  break;
	  
	case 2:
	  x = rand()%790+5;
	  y = rand()%590+5;
	  break;
	  
	case 3:
	  x = rand()%20+5;
	  y = rand()%590+5;
	}
      
      Vector2f v(x,y);
      mobs.insert(mobs.end(),new Mob(window,v,i));
    }
  
}


int init()
{
  score = 5000;
  waveNbr = 0;
  GenWave();
  srand(time(NULL));
  
  music.Stop();
  
  if (!music.OpenFromFile("src/ressources/sounds/DP_Tron_Derezzed_chiptune.ogg"))
    return EXIT_FAILURE;
  music.Play();
  music.SetLoop(true);
  
  
  if (!sbuffer.LoadFromFile("src/ressources/sounds/laser.ogg"))
    return EXIT_FAILURE;

  // Tests
  Vector2f p1(200,230);
  Vector2f p2(450,430);
  Vector2f p3(700,500);
  play =true;
  
  //  mobs.insert(mobs.end(),new Mob(window,p3));

  //  tows.insert(tows.end(), new Tower(window,p1,1,1));
  //tows.insert(tows.end(), new Tower(window,p2,2,2));

}

  

void updateParticles() 
{
  // Thread Update position des projectiles
  std::cout<<"Update"<<std::endl;
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
		      part.erase(partIt);	
		      continue;
		    }
		  
		  else if ((*partIt)->IsDone()) 
		    {
		      (*mobsIt)->Hit((*partIt)->GetPower());
		      std::cout<<"hit mob nb: "<<mobNbTmp<<endl;
		      
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




void UpdateTows()
{
  Sound fire;
  fire.SetBuffer(sbuffer);
  int i;

  while(!play);
  
  // Thread Update tours/mobs

  while(play) 
    {
      if (!mobs.empty())
	{

	  for (std::vector<Building *>::iterator TowsIt = tows.begin(); TowsIt != tows.end();TowsIt++) 
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
			  part.insert(part.end(),new Particle(window,p,(*TowsIt)->GetType(),target->GetPosition(),target->GetID()));		      
			  // Le son d'un shoot
			  fire.Play();	
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
			      std::cout<<"aquire target :"<<(*mobsIt)->GetID()<<std::endl;
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
	      (*mobsIt)->Update(i);
	      if ((*mobsIt)->IsDead())
		{
		  std::cout<<"erase"<<std::endl;
		  mobs.erase(mobsIt);
		  // score ++
		  score = score + 5000;
		  

		  continue;
		  
		}
		  
	      ++mobsIt;

	    }
	}
      else 
	{
	  sleep(10);
	  GenWave();
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
  Font font;
  
  if (!font.LoadFromFile("src/ressources/ARCADE_I.TTF"))
    return EXIT_FAILURE;
  Text text("0000", font, 20);
  text.SetPosition(10,10);
  

  while(window.IsOpen()&&play) {
    Event event;
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
    for (std::vector<Building *>::iterator TowsIt = tows.begin(); TowsIt != tows.end();TowsIt++) 
      {

	(*TowsIt)->Render();

      }


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
	text.SetString( oss.str());
      }
    
    
    while (window.PollEvent(event)) {
      // Window closed
      if (event.Type == Event::Closed) window.Close();

      if (event.Type == Event::MouseButtonPressed) 
	{

	  Vector2i pos = Mouse::GetPosition(window);
	  x = pos.x;
	  y = pos.y;

	  // selection case
	  Square* tmp = m.GetSquarePixel(pos.x,pos.y);
	  m.Select(tmp);

	  // si click droit
	  if (event.MouseButton.Button == Mouse::Right) 
	    {
			popup.SetPosition(x,y);
			isPopped=true;
			
	      // ajout cible (pout test)
	      //mobs.insert(mobs.end(),new Mob(window,(Vector2f) pos));
	      //cout<<"menu contex"<<endl;
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
					      if (score >= 2000) 
									{
								  tows.insert(tows.end(), new Tower(window,popup.GetPosition(),1,1));
						  		score = score - 2000;
									}
					      else
						cout<<"not enough money!"<<tmp->number<<endl;
					    }
					  if(popup.button[i].GetString()=="Tour2")
					    { 
					      if (score >= 2000) 
									{
								  tows.insert(tows.end(), new Tower(window,popup.GetPosition(),1,2));
						  		score = score - 2000;
									}
					      else
						cout<<"not enough money!"<<tmp->number<<endl;
					    }
					  
					  //if(popup.button[i].GetString()=="Mob") mobs.insert(mobs.end(),new Mob(window,popup.GetPosition()));
					}
				}
			}
			
			isPopped=false;

	      //	      cout<<"information on case n° "<<tmp->number<<endl;
	      //tows.insert(tows.end(), new Tower(window,(Vector2f) pos,2,2));

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
	      break;
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
}

int main(void) {

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
      // Window closed
      if (event.Type == Event::Closed) window.Close();
      // Button clicked
      if (event.Type == Event::MouseButtonPressed) {

			  
	for(int i=0;i<5;i++) {
	  if(currentMenu->button[i].GetGlobalBounds().Contains(event.MouseButton.X,event.MouseButton.Y)) {
	    if(currentMenu->button[i].GetString()=="Options") currentMenu = &optionMenu;
	    if(currentMenu->button[i].GetString()=="PLAY") {game();
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
	      play = true;
	      game();
	     }

	}

    }
    usleep(30000);
    // Update the window
    window.Clear();
    currentMenu->Render(window);
    window.Display();
  }

  window.Clear();
  window.Close();

  return (EXIT_SUCCESS);
}
