/**
 * \file PopupMenu.hxx
 * \brief Class PopupMenu Header
 * \author Thomas FOURCROY
 * \author Benoit Djerigian
 * \version 0.9
 * \date 14 fevrier 2012
 *
 * Classe Menu contextuel
 *
 */

#ifndef _POPUPMENU_HXX
#define _POPUPMENU_HXX

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>

#include "Menu.hxx"

using namespace sf;

/** \class PopupMenu
 * \brief La classe du menu contextuel
 * Permet la construction de tours
 */
class PopupMenu : public Menu {

private :
	int _x;
	int _y;

public :
  /** \fn    PopupMenu(int x, int y)
   * \brief Le constructeur
   * \param x L'abscisse du coin superieur gauche du menu
   * \param y L'ordonnee du coin superieur gauche du menu
   */
  PopupMenu(int x, int y);
  virtual void Render(RenderTarget& target) const;
  /** \fn   Vector2f GetPosition()
   * \brief Permet d'obtenir la position du menu
   * \return Le vecteur position
   */
  Vector2f GetPosition();
  /** \fn void SetPosition(int x, int y)
   * \brief Permet de definir la position du menu
   * \param x L'abscisse du coin superieur gauche du menu
   * \param y L'ordonnee du coin superieur gauche du menu
   */
  void SetPosition(int x, int y);
};

#endif
