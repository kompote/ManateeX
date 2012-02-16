/**
 * \file Square.hxx
 * \brief Class Square Header
 * \author Thomas FOURCROY
 * \author Benoit Djerigian
 * \version 0.9
 * \date 14 fevrier 2012
 *
 * Classe des cases
 *
 */

#ifndef SQR_H
#define SQR_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>

using namespace sf;

using namespace std;

/** \class Square
 * \brief La classe des cases
 */
class Square
{
  
private:
  bool _free;
  int _content;
  string _texturePath;
  Texture _texture;
  Transformable _transform;
  

public:
  /** \brief Le sprite utilise */
  Sprite sprite;
  /** \brief Le numero de la case */
  int number;
  /** \fn  Square(int i)
   * \brief Le constructeur
   * \param i Le numero de la case
   */
  Square(int i);
  /** \fn  void SetPosition(int x, int y)
   * \brief Permet de definir la position de la case
   * \param x L'abscisse de la case (pixel)
   * \param y L'ordonnee de la case (pixel)
   */
  void SetPosition(int x, int y);
  /** \fn  Vector2f GetPosition() const
   * \brief Permet d'obtenir la position de la case
   * \return Le vecteur position
   */
  Vector2f GetPosition() const;
  /** \fn  void Draw(RenderTarget& target) const
   * \brief Dessine la case
   * \param target Le contexte graphique
   */
  void Draw(RenderTarget& target) const;
  /** \fn   void Select()
   * \brief Met en surbrillance la case
   */
  void Select();
  /** \fn  void UnSelect()
   * \brief Enleve la Surbrillance
   */
  void UnSelect();
  /** \fn  bool IsConstructible()
   * \brief Permet de savoir si la case est constructible
   * \return Vrai ou faux
   */
  bool IsConstructible();
  /** \fn  void SetConstructible(bool b)
   * \brief Permet de definir la 'constructibility' d'une case
   * \param b Vrai ou Faux
   */
  void SetConstructible(bool b);
  /** \fn  int GetContent()
   * \brief pas utilisé
   */
  int GetContent();
  /** \fn  string GetTexturePath()
   * \brief Permet d'obtenir le chemin vers la texture utilisée
   * \return Le chemin sous forme de string
   */
  string GetTexturePath();
  /** \fn  void SetTexturePath(string path, bool cons)
   * \brief Permet de definir une nouvelle texture, ainsi que la 'constructibility' d'une case
   * \param path Le chemin sous forme de string
   * \param cons Vrai ou faux
   */
  void SetTexturePath(string path, bool cons);
};

#endif
