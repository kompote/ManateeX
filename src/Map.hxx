/*
 * \file Map.hxx
 * \brief Class Map Header
 * \author Thomas FOURCROY
 * \author Benoit Djerigian
 * \version 0.9
 * \date 14 fevrier 2012
 *
 * Classe Map
 * 
 */

#ifndef MAP_H
#define MAP_H

#include "Square.hxx"
/** \class Map
 * \brief La classe de la map (carte)
 */
class Map {

private:
  Square* _grid[60][80];
  Square* _lastSelected;
  
		
public:
  /** \fn Map()
   * \brief Construit la carte avec 80x60 Cases
   * \see Square
   */
  Map();
  /** \fn   void Redraw(RenderTarget& target) const
   * \brief Redessine la carte
   * \param target Le contexte graphique
   */
  void Redraw(RenderTarget& target) const;
  /** \fn  Square* GetSquare(int i, int j)
   * \brief Permet d'obtenir une case en fonction de ses coordonnees
   * \param i Abscisse de la case
   * \param j Ordonnee de la case
   * \return Un pointeur sur la case correspondante
   */
  Square* GetSquare(int i, int j);
  /** \fn Square* GetSquarePixel(int x, int y)
   * \brief Permet d'obtenir une case en fonction de coordonnées reelles (pixels)
   * \param x Abscisse du pixel
   * \param y Ordonnee du pixel
   * \return Un pointeur sur la case correspondante
   */
  Square* GetSquarePixel(int x, int y);
  /** \fn   void Select(Square* s)
   * \brief Met en surbrillance une case
   * \param s Un pointeur vers une case
   * \see Square
   */
  void Select(Square* s);
};

#endif
