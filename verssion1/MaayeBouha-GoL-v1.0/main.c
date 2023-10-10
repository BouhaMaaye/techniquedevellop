/**
 * \file main.c
 * \brief Fichier main.c (coeur)
 */

#include <stdio.h>

#include "grille.h"
#include "io.h"
#include "jeu.h"

/**
 * \brief Fonction main classique, avec tout ses appels
 * \return 0 
 */

int main (int argc, char ** argv) {
	
  if (argc != 2 )
    {
		printf("usage : main <fichier grille>");
		return 1;
		}

	grille g, gc;
	
	init_grille_from_file(argv[1],&g);
	alloue_grille (g.nbl, g.nbc, &gc);
	affiche_grille(g);
	
	debut_jeu(&g, &gc);

	libere_grille(&g);
	libere_grille(&gc);
  
	return 0;
}
