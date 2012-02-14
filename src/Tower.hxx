#ifndef TOW_H
#define TOW_H

#include <SFML/Graphics.hpp>
#include "Building.hxx"

using namespace sf;

using namespace std;

class Tower : public Building
{
	public:
	  int type;
		int range;
		bool htarget;
		Mob *target;
		bool canshoot;
		int reloadtime;
		int tries;

		Tower(RenderWindow&,Vector2f,int,int);  

		bool InRange(Vector2f);
		int GetType();
		Mob* GetTarget();
		void SetTarget(Mob*);
		bool HasTarget();
		void ReleaseTarget();
		bool CanShoot();
};

#endif
