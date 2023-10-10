/**
 * \file io.h
 * \brief Fichier contenant les déclarations des fonctions de io.c
 */ 

#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"

#ifdef GRAPHIC

#include <stdio.h>
#include "jeu.h"
#include "grille.h"
#include "io.h"
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <string.h>

#define SIZEX 800
#define SIZEY 600

double TAILLE_CX;
double TAILLE_CY;

void affiche_grille_gr(cairo_surface_t *surface, grille g);

#else



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

void affiche_evolution(int *evol);

#endif

void debut_jeu(grille *g, grille *gc);

/**                                                                                                                                                  
 * \brief affiche le temps d'évolution (incrémenté de 1 à chaque coup)                                                                               
 * \param *evol pointeur sur la variable d'evolution                                                                                                 
*/


#endif
