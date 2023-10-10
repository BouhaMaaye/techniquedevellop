/**
 * \file jeu.c
 * \brief Fichier jeu.c
 */

#include "jeu.h"

int compte_voisins_vivants_cycliques(int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);

	return v; 
}

int compte_voisins_vivants_non_cycliques(int i, int j, grille g){
  int v = 0;
  int lgn = g.nbl;
  int col = g.nbc;
  int k;
  int l;
  for(k = -1; k<=1; k++){
    for(l = -1; l <= 1; l++){
      if(k != 0 || l != 0){
	if(k+i >= 0 && k+i < lgn && l+j >= 0 && l+j < col){
	  v = v + est_vivante(i+k, j+l, g);
	}
      }
    }
  }
  return v;
}

void evolue_sv (grille *g, grille *gc, int (*cyclique_ou_pas)(int,int,grille)){
  copie_grille (*g,*gc); // copie temporaire de la grille
  int i,j,l=g->nbl, c = g->nbc,v;
  for (i=0; i<l; i++)
    {
      for (j=0; j<c; ++j)
	{
	  v = (*cyclique_ou_pas)(i, j, *gc);
	  if (est_vivante(i,j,*g))
	    { // evolution d'une cellule vivante
	      if ( v!=2 && v!= 3 ) set_morte(i,j,*g);
	    }
	  else
	    { // evolution d'une cellule morte
	      if ( v==3 ) set_vivante(i,j,*g);
	    }
	}
    }
  //return;
}



void evolue_v (grille *g, grille *gc, int (*cyclique_ou_pas)(int,int,grille)){
  copie_grille (*g,*gc); // copie temporaire de la grille
  int i,j,l=g->nbl, c = g->nbc,v;
  for (i=0; i<l; i++)
    {
      for (j=0; j<c; ++j)
	{
	  v = (*cyclique_ou_pas)(i, j, *gc);
	  if (est_vivante(i,j,*g))
	    { // evolution d'une cellule vivante
	      if ( v!=2 && v!= 3 ) set_morte(i,j,*g);
	      else if (g->cellules[i][j] >= 1000) set_morte(i,j,*g);
	      else {g->cellules[i][j]++;}
	    }
	  else
	    { // evolution d'une cellule morte
	      if ( v==3 ) set_vivante(i,j,*g);
	    }
	}
    }
  //return;
}
