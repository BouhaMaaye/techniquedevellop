/**
 * \file io.h
 * \brief Fichier contenant les déclarations des fonctions de io.c
 */ 

#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"

/**
 * \brief Permet d'afficher le caractère '|' pour faire les traits
 * \param c colonnes
 */

void affiche_trait (int c);

/** 
 * \brief Affichage d'une ligne de la grille
 * \param c colonnes
 * \param *ligne pointeur lignes
 */

void affiche_ligne (int c, int* ligne);

/**
 * \brief affichage d'une grille
 * \param g grille
 */

void affiche_grille (grille g);

/**
 * \brief effacement d'une grille
 * \param g grille
 */

void efface_grille (grille g);

/**
 * \brief debute le jeu
 * \param *g pointeur grille
 * \param *gc pointeur grille
 * On utilise cette fonction avec les touches 'entrée' (avancer), 'q' (quitter), 'n' (changement de grille), 'c' (cyclique->non-cyclique) (niv2prototype)
 */

void debut_jeu(grille *g, grille *gc);

/**
 * \brief affiche le temps d'évolution (incrémenté de 1 à chaque coup)
 * \param *evol pointeur sur la variable d'evolution
 */

void affiche_evolution(int *evol);


#endif
