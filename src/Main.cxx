#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "Map.hxx"
#include "Case.hxx"
#include "Mob.hxx"
#include "Proj.hxx"

using namespace sf;

//create map
Map m;

//tests
Mob* enn[10];
Proj* toto[10];

bool run = true;
RenderWindow window;


void disp() 
{
  window.Create(VideoMode(800, 600), "SFML window");
  window.SetFramerateLimit(30);

  while(run)
    {
      window.Clear();

      for(int i=0;i<60;i++) {
	for(int j=0;j<80;j++) {
	  Case* tmp = m.getCase(j,i);
	  window.Draw(tmp->sprite);
	}
      }
      // update ennemies
      if ((enn[0])&&(!enn[0]->IsDead()))
	window.Draw(enn[0]->SpriteMob);
      //update projectiles
      if ((toto[0])&&(!enn[0]->IsDead()))
	window.Draw(toto[0]->SpriteProj);

       // Update the window
      window.Display();
      usleep(10000);
      
    }
}

void garbage() 
{
  if ((enn[0])&&(enn[0]->IsDead())) {
    delete enn[0];
    enn[0]=NULL;
    
    
    std::cout<<"Dead."<<endl;
  }
  if ((toto[0])&&(enn[0]->IsDead())) 
    {
      delete toto[0];
      
      toto[0]=NULL;
    }
  
}

void fire()
{


  toto[0] = new Proj(1,30,400,100);

  int gotox = enn[0]->GetPosX();
  int gotoy = enn[0]->GetPosY();
  
  toto[0]->Move(gotox,gotoy);

  enn[0]->Hit(toto[0]->GetPV());
  toto[0] = NULL;
  
}




int main (void) {

  int x,y;
	
  Thread ttt(&disp);
  //  Thread* pp;
  ttt.Launch();
  usleep(50000);

  Case* last = NULL;
  enn[0]= new Mob(1,400,300,1000);
  
  while(window.IsOpened()) {
    Event event;
    while (window.PollEvent(event)) {

      if (event.Type == Event::Closed) window.Close();

      if (event.Type == Event::MouseButtonReleased) 
	{
	  // Select case
	  cout<<"catching mouse event\033[32m"<<endl;
	  Vector2i pos = Mouse::GetPosition(window);
	  x = pos.x;
	  y = pos.y;
	  std::cout<<"("<<pos.x<<":"<<pos.y<<")"<<endl;
	  Case* tmp = m.getCasePixel(pos.x,pos.y);
	  std::cout<<"case n° "<<tmp->number<<" selected"<<endl;
	  // highlight
	  tmp->Select();
	  if (last)
	    last->UnSelect();
	  last = tmp;

	  // si click droit
	  if (event.MouseButton.Button == Mouse::Right) 
	    {
	      cout<<"menu contex"<<endl;
	    }
	  
	  //si click gauche
	  if (event.MouseButton.Button == Mouse::Left)
	    {
	      cout<<"information on case n° "<<tmp->number<<endl;

	      //marche pas!!
	      tmp->SetTexturePath("src/ressources/images/tower1.png",false);
	      

	    }
	  
	  cout<<"\033[0mReprise event watch"<<endl;
	}

      if (event.Type == Event::KeyPressed) 
	{
	  switch(event.Key.Code)
	    {
	      // info sur la derniere case selectionnee (debug)
	    case Keyboard::I:
	      {
		
		Case* tmp2 = m.getCasePixel(x,y);
		std::cout<<tmp2->getTexturePath()<<" for case n° "<<tmp2->number<<" "<<tmp2->isConstructible()<<endl;
		if (tmp2->isConstructible()) 
		  std::cout<<"true"<<endl;
		break;
	      }
	      
	      // kill the star
	    case Keyboard::K:
	      if ((enn[0])&&(!enn[0]->IsDead()))	      
		{
		  enn[0]->Hit(100);
		  std::cout<<"Hit! still "<<enn[0]->GetPV()<<"PV"<<endl;
		  break;
		}
	      else 
		{
		  std::cout<<"no star no more"<<endl;
		}
	    case Keyboard::F:
	      if (enn[0]) 
		{
		  
		  std::cout<<"Fire"<<endl;
		  Thread pp(&fire);	  
		  pp.Launch();
		  //	  std::cout<<"Fire"<<endl;
		}
	      
	      //	      fire();
	      
	    }
	}
    }
    garbage();
    
    usleep(20000);
  }
  run = false;
}


