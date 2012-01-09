#ifndef CASE_H
#define CASE_H

#include <string>
using namespace std;

class Case {

	private:
		bool constructible;
		int content;
		string texturePath;
		
	public:
		Case();
		bool isConstructible();
		int getContent();
		string getTexturePath();
};

#endif
