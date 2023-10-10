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

int compte_voisins_vivants_cycliques (int i, int j, grille g);


/**
 * \brief compte le nombre de voisins vivant de la cellule (i,j) les bords ne sont pas cycliques.
 * \param i numero ligne
 * \param j numero colonne
 * \param g grille
 */


int compte_voisins_vivants_non_cycliques (int i, int j, grille g);


/**
 * \brief  fait évoluer la grille g d'un pas de temps sans vieillissment
 * \param *g pointeur grille
 * \param *gc pointeur grille
 * \param *cyclique_ou_pas pointeur sur l'etat cyclique ou non
 */

void evolue_sv (grille *g, grille *gc, int (*cyclique_ou_pas)(int,int,grille));

/**                                                                                                                                  
 * \brief  fait évoluer la grille g d'un pas de temps avec vieillissment                                       
 * \param *g pointeur grille                                                                                                      
 * \param *gc pointeur grille                                                                                                     
 * \param *cyclique_ou_pas pointeur sur l'etat cyclique ou non                                                                       */


void evolue_v (grille *g, grille *gc, int (*cyclique_ou_pas)(int,int,grille));

#endif
