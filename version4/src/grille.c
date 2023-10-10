/**
 * \file grille.c
 * \brief Fichier grille.c
 */

#include "../include/grille.h"


void alloue_grille(int l, int c, grille* g){
  g->cellules = malloc(l*sizeof(int*));
  for(int k = 0; k<l; k++){
    g->cellules[k] = malloc(c*sizeof(int));
  }
  g->nbl = l;
  g->nbc = c;
  for(int i = 0; i<g->nbl; i++){
    for(int j = 0; j<g->nbc; j++){
      g->cellules[i][j] = 0;
    }
  }
}

void libere_grille(grille* g){
  for(int i = 0; i < g->nbl; i++){
    free(g->cellules[i]);
  }
  free(g->cellules);
}


void init_grille_from_file (char * filename, grille* g){
	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	assert (pfile != NULL);
	
	int i,j,n,m,l,c,vivantes=0;
	int nonViables=0;
	
	fscanf(pfile, "%d", & l);
	fscanf(pfile, "%d", & c);
	
	alloue_grille(l,c,g);
	
	fscanf(pfile, "%d", & vivantes);
	for (n=0; n< vivantes; ++n){
	   fscanf(pfile, "%d", & i);
	   fscanf(pfile, "%d", & j);
	   set_vivante(i,j,*g);
	}

	fscanf(pfile, "%d", &nonViables);
        for (m=0; m<nonViables; ++m){
           fscanf(pfile, "%d", & i);
           fscanf(pfile, "%d", & j);
           set_nonViable(i,j,*g);
	}
	
        fclose (pfile);
	return;
}


void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;	
}
