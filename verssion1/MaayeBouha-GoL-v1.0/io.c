/**
 * \file io.c
 * \brief Fichier io.c
 */

#include "io.h"

void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i) 
		if (ligne[i] == 0 ) printf ("|   "); else printf ("| O ");
	printf("|\n");
	return;
}

void affiche_grille (grille g){
	int i, l=g.nbl, c=g.nbc;
	printf("\n");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}	
	printf("\n"); 
	return;
}

void efface_grille (grille g){
  printf("\n\e[%dA", g.nbl*2 + 5); 
}

void debut_jeu(grille *g, grille *gc){
	char c = getchar();
	char filegrille[100];
	while (c != 'q') // touche 'q' pour quitter
	{ 
		switch (c) {
		        case 'n' :
			  { // touche 'n' changement de grille
			  printf("Entrez une autre grille : ");
     			  scanf("%s", filegrille);
			  init_grille_from_file(filegrille, g);
			  alloue_grille(g->nbl, g->nbc, gc);
			  affiche_grille(*g);
			  printf("\n");
			  break;
			}
			case '\n' : 
			{ // touche "entree" pour évoluer
				evolue(g,gc);
				efface_grille(*g);
				affiche_grille(*g);
				break;
			}
			default : 
			{ // touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
		c = getchar(); 
	}
	return;	
}




