/**
 * \file grille.h
 * \brief Fichier contenant les déclaraions des fonctions de grille.c
 */

#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
 
/**
 * \brief Structure grille : nombre de lignes, nombre de colonnes, tableau de tableau de cellules
 *  int nbl: Nombre de ligne de cellules 
 *  int nbc: Nombre de colonnes de cellules
 *  int** cellules: Pointeur de pointeur du tableau contenant les cellules (Tableau 2D)
 */

typedef struct {int nbl; int nbc; int** cellules;} grille;
 
/**
 * \brief Alloue une grille de taille l*c, et initialise toutes les cellules à mortes
 * \param [in] l Nombre de ligne à allouer
 * \param [in] c Nombre de colonnes à allouer
 * \param [out] g Pointeur sur la grille allouée de taille l*c
 */
 
void alloue_grille (int l, int c, grille* g);

/**
 * \brief Libère une grille
 * \param [out] g Pointeur sur la grille à allouer (lignes et colonnes)
 */

void libere_grille (grille* g);

/**
 * \brief Alloue et initalise la grille g à partir d'un fichier
 * \param *filename Nom du fichier à charger
 * \param *g pointeur grille 
*/

void init_grille_from_file (char * filename, grille* g);

//fonctions rapides suivantes non commentées

// rend vivante la cellule (i,j) de la grille g
static inline void set_vivante(int i, int j, grille g){g.cellules[i][j] = 1;}
// rend morte la cellule (i,j) de la grille g
static inline void set_morte(int i, int j, grille g){g.cellules[i][j] = 0;}
// rend non viable la cellule (i,j) de la grille g
static inline void set_nonViable(int i, int j, grille g){g.cellules[i][j] = -1;}
// teste si la cellule (i,j) de la grille g est non viable                                                                                           
static inline int est_nonViable(int i, int j, grille g){return g.cellules[i][j] == -1;}
// teste si la cellule (i,j) de la grille g est vivante
static inline int est_vivante(int i, int j, grille g){return g.cellules[i][j] >= 1;}



/**
 * \brief recopie gs dans gd (sans allocation)
 * \param gs Grille source
 * \param gd Grille destination
 */

void copie_grille (grille gs, grille gd);

#endif
