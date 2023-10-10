/**
 * \file io.c
 * \brief Fichier io.c
 */

#include "../include/io.h"

void affiche_evolution(int* evol){
  *evol = *evol + 1;
  printf("Temps d'évolution = %i \n", *evol);
}

void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

void affiche_ligne (int c, int* ligne){
	int i;
	for(i=0; i<c; ++i){ 
	  if(ligne[i] == 0){
	    printf("|   ");
	  }
	  else if(ligne[i] == -1){
	    printf("| X ");
	  }
	  else{
	    printf("| %d ", ligne[i]);
	  }
	}
	printf("|\n");
	return;
}

void affiche_grille (grille g){
	int i, l=g.nbl, c=g.nbc;
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
  printf("\n");
  printf("Temps d'évolution = 0");
  printf("\n");
  affiche_grille(*g);
  int (*compteVoisinsVivants) (int, int, grille) = &compte_voisins_vivants_cycliques;
  char filegrille[100];
  int evol = 0;
  void (*evolue) (grille *g, grille *gc, int (*cyclique_ou_pas)(int,int,grille))=&evolue_sv;
  char c = getchar();
  while (c != 'q') // touche 'q' pour quitter
  {
    switch (c){
    case 'v' :
      {
	//touche 'v' pour activer/désactiver le vieillissement
	if(evolue==&evolue_sv){
	  evolue=&evolue_v;
	}
	else{
	  evolue=&evolue_sv;
	}
	break;
      }
    case 'n' :
      { // touche 'n' changement de grille
	printf("Entrez une autre grille : ");
	scanf("%s", filegrille);
	init_grille_from_file(filegrille, g);
	alloue_grille(g->nbl, g->nbc, gc);
	printf("\n");
	evol = 0;
	printf("Temps d'évolution = %i \n", evol);
	affiche_grille(*g);
	printf("\n");
	break;
      }

    case 'c' :
      { // touche 'c' passage cyclique -> non cyclique
	if(compteVoisinsVivants == &compte_voisins_vivants_cycliques){
	  compteVoisinsVivants = &compte_voisins_vivants_non_cycliques;
	}
	else{
	  compteVoisinsVivants = &compte_voisins_vivants_cycliques;
	}
	break;
      }
      
    case '\n' :
      { // touche "entree" pour évoluer
	evolue(g,gc,compteVoisinsVivants);
	efface_grille(*g);
	affiche_evolution(&evol);
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
