/**
 * \file Particle.hxx
 * \brief Class Particle Header
 * \author Thomas FOURCROY
 * \author Benoit Djerigian
 * \version 0.9
 * \date 14 fevrier 2012
 *
 * Classe Particle representant les projectiles
 * possede les fonctions de calcul de trajectoires
 *
 */

#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <cmath>

using namespace sf;

/** \class Particle
 * \brief La classe des projectiles
 * Possede les fcondtions de calcul de trajectoires
 */
class Particle {
public:
  /** \fn  Particle(RenderWindow& aWindow, Vector2f position, int t, Vector2f ci, int nci)
   * \brief Le constructeur
   * \param aWindow Le contexte graphique
   * \param position Le vecteur position de depart
   * \param t le type de projectile
   * \param ci Le vecteur position de la cible
   * \param nci Le numero de l'ennemi vise
   */
  Particle(RenderWindow& aWindow, Vector2f position, int t, Vector2f ci, int nci);
  /** \fn   ~Particle()
   * \brief Le destructeur
   */
  ~Particle();
  /** \fn  bool IsDone()
   * \brief Permet de savoir si le projectile est arrive a destination
   * \return vrai ou faux
   */
  bool IsDone();
  /** \fn  int GetTargetNbr()
   * \brief Permet d'obtenir le numero de la cible visee
   * \return Le numero de la cible
   */
  int GetTargetNbr();
  /** \fn  int GetPower()
   * \brief Permet de recuperer la puissance du tir
   * Depend de la tour d'origine
   * \see Tower
   * \return La valeur de la puissance de feu
   */
  int GetPower();
  /** \fn  void SetPosition(Vector2f pos)
   * \brief Permet de definir la position du projectile
   * \param pos Le vecteur position
   */
  void SetPosition(Vector2f pos);
  /** \fn  Vector2f GetPosition(void)
   * \brief Permet d'obtenir la position du projectile
   * \return Le vecteur position
   */
  Vector2f GetPosition(void);
  /** \fn  void Bresenham(int x, int y)
   * \brief Calcul de la trajectoire vers la cible
   * \param x L'abscisse de la cible (pixel)
   * \param y L'ordonnee de la cible (pixel)
   */
  void Bresenham(int x, int y);
  /** \fn  void Render()
   * \brief Dessine le projectile
   */
  void Render();
  /** \fn   void Update()
   * \brief met a jour la position du projectile et son etat si necessaire
   */
  void Update();
  
private:
  RenderWindow& _window;
  Vector2f _pos;
  Vector2f _target;
  CircleShape _circle;
  std::vector <Vector2f *> _path;
  std::vector <Vector2f *>::iterator _it;
  int _type;
  int _tarNbr;
  int _power;
  
  bool _done;
  bool _hasPath;
};

#endif
