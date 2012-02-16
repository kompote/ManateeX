/*
 * \file Menu.hxx
 * \brief Class Menu Header
 * \author Thomas FOURCROY
 * \author Benoit Djerigian
 * \version 0.9
 * \date 14 fevrier 2012
 *
 * Classe mere pour les menus
 * 
 */

#ifndef _MENU_HXX
#define _MENU_HXX

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>

using namespace sf;
/** \class Menu
 * \brief Classe mere pour les menus
 */
class Menu {

protected :
  /** \brief Le srpite d'arriere plan */
  Sprite bgSprite;
  /** \brief La texture utiliser par le sprite
   * \see bgSrpite */
  Texture bgTexture;
  /** \brief La police utilisee */
  Font font;
  /** \brief Le texte du Titre */
  Text title;

public :
  /** \brief Les different bouton (representer par leur texte) */
  Text button[5];
  /** \fn Menu()
   * \brief Le constructeur */
  Menu();
  /** \fn virtual void Render(RenderTarget& target) const=0
   * \brief Dessine le menu 
   * \param target Le contexte sur lequel dessiner
   */
  virtual void Render(RenderTarget& target) const=0;
};

#endif
