/*
 * \file MainMenu.hxx
 * \brief Class MainMenu Header
 * \author Thomas FOURCROY
 * \author Benoit Djerigian
 * \version 0.9
 * \date 14 fevrier 2012
 *
 * Classe Menu principal
 * 
 */

#ifndef _MAINMENU_HXX
#define _MAINMENU_HXX

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>

#include "Menu.hxx"

using namespace sf;

/** \class MainMenu
 * \brief La classe du menu principal
 */
class MainMenu : public Menu {

public :
  /** \fn MainMenu()
   * \brief Le constructeur
   */
    MainMenu();
    virtual void Render(RenderTarget& target) const;
};

#endif
