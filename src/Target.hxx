/**
 * \file Target.hxx
 * \brief Class Target Header
 * \author Thomas FOURCROY
 * \author Benoit Djerigian
 * \version 0.9
 * \date 14 fevrier 2012
 *
 * Classe de l'objectif
 *
 */

#ifndef TAR_H
#define TAR_H

#include <SFML/Graphics.hpp>
#include "Building.hxx"

using namespace sf;

using namespace std;

/** \class Target
 * \brief La classe de l'objectif
 */
class Target : public Building
{

public:
  /** \fn  Target(RenderWindow& aWindow)
   * \brief Le constructeur
   * \param aWindow Le contexte graphique
   */
  Target(RenderWindow& aWindow);  
  /** \fn  void Hit(int damage)
   * \brief Infige des domages
   * \param damage La quantite de domages
   */
  void Hit(int damage);
  /** \fn   bool IsDead()
   * \brief Permet de savoir si l'objectif est mort
   * \return Vrai ou faux
   */
  bool IsDead();
  /** \fn  int GetHP()
   * \brief Permet d'obtenir les points de vie actuels
   * \return HP
   */
  int GetHP();
};

#endif
