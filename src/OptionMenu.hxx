/*
 * \file OptionMenu.hxx
 * \brief Class OptionMenu Header
 * \author Thomas FOURCROY
 * \author Benoit Djerigian
 * \version 0.9
 * \date 14 fevrier 2012
 *
 * Classe Menu Options
 * 
 */

#ifndef _OPTIONMENU_HXX
#define _OPTIONMENU_HXX

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>

#include "Menu.hxx"

using namespace sf;

/** \class OptionMenu
 * \brief La classe du menu Option
 */
class OptionMenu : public Menu {

public :
  /** \fn OptionMenu()
   * \brief Le constructeur */
    OptionMenu();
    virtual void Render(RenderTarget& target) const;
};

#endif
