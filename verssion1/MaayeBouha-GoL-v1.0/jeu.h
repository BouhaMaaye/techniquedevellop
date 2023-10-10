#ifndef __JEU_H
#define __JEU_H

#include "grille.h"

// fct rapide non commentée 
// modulo modifié pour traiter correctement les bords i=0 et j=0
// dans le calcul des voisins avec bords cycliques
static inline int modulo(int i, int m) {return (i+m)%m;}

/**
 * \brief compte le nombre de voisins vivants de la cellule (i,j) les bords sont cycliques.
 * \param i numero ligne
 * \param j numero colonne
 * \param g grille
 */

int compte_voisins_vivants (int i, int j, grille g);

/**
 * \brief  fait évoluer la grille g d'un pas de temps
 * \param *g pointeur grille
 * \param *gc pointeur grille
 */

void evolue (grille *g, grille *gc);

#endif
