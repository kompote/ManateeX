/*
 * \file Mob.hxx
 * \brief Class Mob Header
 * \author Thomas FOURCROY
 * \author Benoit Djerigian
 * \version 0.9
 * \date 14 fevrier 2012
 *
 * Classe mob representant un enemi
 * possede les fonctions de calcul de trajectoires
 *
 */

#ifndef MOB_H
#define MOB_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Map.hxx"
using namespace sf;
/**
* \struct _node
* \brief Representation d'une case dans le graphe des positions
* Represente un noeud dans le graphe utiliser pour calculer les chemins.
* Contient ses coordonnées, les coordonnées des parents, le cout pour aller a la destination, le cout depuis l'origine, le cout total, et un pointeur vers la case correspondante.
*/
typedef struct 
  {
    /** \brief Abscisse du noeud */
    int x;
    /** \brief Ordonnee du noeud */
    int y;
    /** \brief Abscisse du noeud parent */
    int parent_x;
    /** \brief Ordonnee du noeud parent */
    int parent_y;
    /** \brief Cout jusqu'a destination */
    int costtodest;
    /** \brief Cout depuis l'origine */
    int costfromorg;
    /** \brief Cout total */
    int totalcost;
    /** \brief Pointeur vers la case correspondante */
    Square* current;
  } _node;

/**
 * \class Mob
 * \brief La classe des ennemis
 *
 * Gere l'affichage et le deplacement des ennemis
 */
class Mob {
public:
/**
 * \fn  Mob::Mob(sf::RenderWindow& aWindow, Vector2f position, int numero)
 * \brief Constructeur
 * \param aWindow le contexte graphique
 * \param position la position initiale
 * \param numero un id
 */
  Mob(RenderWindow& aWindow,Vector2f position ,int numero);
/**
 * \fn ~Mob()
 * \brief Destructeur
 */
  ~Mob();
/**
 * \fn void SetPosition(Vector2f aPos)
 * \brief Applique une position a l'ennemi
 * \param aPos Le vecteur position
 */
  void SetPosition(Vector2f aPos);
/**
 * \fn   Vector2f GetPosition()
 * \brief Recupere la position de l'ennemi
 * \return Le vecteur position
 */
  Vector2f GetPosition();
/**
 * \fn void Hit(int)
 * \brief Applique une perte de point de vie a l'ennemi
 * \param k Quantite a retirer
 */
  void Hit(int k);
/**
 * \fn  bool IsDead()
 * \brief Permet de savoir si un ennemi est mort (_hp<0)
 * \return vrai ou faux
 */
  bool IsDead();
/**
 * \fn int GetID()
 * \brief Permet de recuperer l'ID d'un ennemi
 * \return ID
 */
  int GetID();
/**
 * \fn  int GetHP()
 * \brief Permet de recuperer les points de vie d'un ennemi
 * \return HP
 */
  int GetHP();
/**
 * \fn bool HasArrived()
 * \brief Permet de savoir si un ennemi est arrive a destination
 * \return Vrai ou faux
 */
  bool HasArrived();
/**
 * \fn   void AStar(Map& map, int x, int y)
 * \brief Fonction de calcul de trajectoire
 * \param map La carte sur laquel le calcul est a faire
 * \param x L'abscisse de destination (case)
 * \param y L'ordonnee de destination (case)
 * Calcul la trajectoire en utilisant l'algorithme A*
 * Utiliste uniquement les cases
 */
  void AStar(Map& map, int x,int y);
/**
 * \fn   void Bresenham(int,int)
 * \brief Fonction d'affinage de la trajectoire
 * \param x L'abscisse de destination (pixel)
 * \param y L'ordonnee de destination (pixel)
 * Affine la trajectoire en utilisant l'algorithme de Bresenham
 * Permet de calculer le chemin entre 2 cases
 * Appelé par AStar
 */
  void Bresenham(int x, int y);
/**
 * \fn  void Render()
 * \brief Affiche l'ennemi sur la frame suivante
 */
  void Render();
/**
 * \fn    void Update()
 * \brief Met a jour l'ennemi le deplace a la prochaine position
 */
  void Update();
  
private:
  /**
   * /brief Le contexte graphique
   *
   */  
  RenderWindow& _window;
  /**
   * /brief La position
   *
   */  
  Vector2f _pos;
  /**
   * /brief La position de la cible
   *
   */  
  Vector2f _target;
  /**
   * /brief Un cercle representant l'ennemi
   *
   */  
  CircleShape _circle;
  /**
   * /brief Vecteur contenant la liste des coodronnees de la trajectoire
   *
   */  
  std::vector <Vector2f *> _path;
  /**
   * /brief Iterateur representant la position actuelle dans _path
   *
   */  
  std::vector <Vector2f *>::iterator _it;
  /**
   * /brief Le type de l'ennemi
   *
   */  
  int _type;
  /**
   * /brief Les points de vie
   *
   */  
  int _hp;
  /**
   * /brief Etat de l'ennemi
   *
   */  
  bool _dead;
  /**
   * /brief connait son chemin
   *
   */  
  bool _hasPath;
  /**
   * /brief identifiant
   *
   */  
  int _id;
  /**
   * /brief Temporaires
   *
   */  
  int _xtmp;
  /**
   * /brief Temporaires
   *
   */  
  int _ytmp;
  /**
   * /brief Arrivé a destination
   *
   */  
  bool _arrived;
};

#endif
