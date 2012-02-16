/*
 * \file building.hxx
 * \brief Class Building Header
 * \author Thomas FOURCROY
 * \author Benoit Djerigian
 * \version 0.9
 * \date 14 fevrier 2012
 *
 * Classe mere Building representant une construction
 * 
 */

#ifndef BUILD_H
#define BUILD_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "Mob.hxx"

using namespace sf;
using namespace std;

/** \class Building
 * \brief La classe mere des constructions
 */
class Building
{
public:
  /** \brief La fenetre du contexte */
  RenderWindow& window;
  /** \brief Le chemin vers la texture */
  string texturePath;
  /** \brief La texture */
  Texture texture;
  /** \brief Le Sprite utilisé */
  Sprite sprite;
  /** \brief Son ID */
  int number;
  /** \brief Ses points de vie */
  int hp;
  /** \brief Drapeau d'etat */
  bool dead;
  /** \brief Le vecteur position */
  Vector2f position;

  /** \fn   Building(RenderWindow& aWindow)
   * \brief Le constructeur
   * \param aWindow Le contexte graphique
   */
  Building(RenderWindow& aWindow);
  /** \fn   Vector2f GetPos()
   * \brief Recupere la position
   * \return Le vecteur position
   */
  Vector2f GetPos();
  /** \fn  void Select()
   * \brief Met en surbrillance le batiment
   */
  void Select();
  /** \fn   void UnSelect()
   * \brief Enleve la surbrillance
   */
  void UnSelect();
  /** \fn  void Render()
   * \brief dessine le batiment
   */
  void Render();  
};

#endif
