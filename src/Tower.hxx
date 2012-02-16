/**
 * \file Tower.hxx
 * \brief Class Tower Header
 * \author Thomas FOURCROY
 * \author Benoit Djerigian
 * \version 0.9
 * \date 14 fevrier 2012
 *
 * Classe des Tours
 *
 */

#ifndef TOW_H
#define TOW_H

#include <SFML/Graphics.hpp>
#include "Building.hxx"

using namespace sf;

using namespace std;

/** \class Tower
 * \brief La classe des Tours
 */
class Tower : public Building
{
public:
  /** \brief Le type de tour */
  int type;
  /** \brief La portee de la tour */
  int range;
  /** \brief Drapeau d'indication de cible acquise */
  bool htarget;
  /** \brief Pointeur vers la cible */
  Mob *target;
  /** \brief Drapeau d'indication de la possiblilité de tirer */
  bool canshoot;
  /** \brief Le temps de rechargement entre 2 tirs */
  int reloadtime;

  /** \fn  Tower(RenderWindow& aWindow, Vector2f pos, int i, int t)
   * \brief Le constructeur
   * \param aWindow Le contexte graphique
   * \param pos La postition
   * \param i Le numero de la tour
   * \param t Le type de tour
   */
  Tower(RenderWindow& aWindow, Vector2f pos, int i, int t);  
  /** \fn  bool InRange(Vector2f p)
   * \brief Permet de savoir si un point est a portee
   * \param p Une position
   * \return vrai ou faux
   */
  bool InRange(Vector2f p);
  /** \fn  int GetType()
   * \brief Permet d'obtenir le type de la tour
   * \return Le numero du type
   */
  int GetType();
  /** \fn  Mob* GetTarget()
   * \brief Permet d'obtenir la cible visée
   * \return Un pointeur vers la cible
   */
  Mob* GetTarget();
  /** \fn  void SetTarget(Mob* t)
   * \brief Permet de definir une cible
   * \param t Un pointeur vers uen cible
   */
  void SetTarget(Mob* t);
  /** \fn  bool HasTarget()
   * \brief Permet de savoir si une cible est acquise
   * \return Vrai ou faux
   */
  bool HasTarget();
  /** \fn  void ReleaseTarget()
   * \brief Permet d'indiquer a la tour qu'il faut relacher la cible
   */
  void ReleaseTarget();
  /** \fn  bool CanShoot()
   * \brief Permet de savoir si la tour peut tirer
   * \return Vrai ou faux
   */
  bool CanShoot();
  /** \fn  void FaceTarget()
   * \brief Permet d'ordonner a la tour de s'orienter vers la cible
   */
  void FaceTarget();
private:
  int tries;
};

#endif
