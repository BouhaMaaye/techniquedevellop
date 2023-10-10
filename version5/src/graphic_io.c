/**                                                                      
 * \file graphic_io.c                                                            
 * \brief io.c version graphique
**/  

#include "../include/io.h"
#include <string.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#define MAX 100

int var_osc = 0;
char charOsc[20];
char textOsc[50];
char charEvol[20];
char textEvol[50];
char fileName[1000];
static int evol = 0;

int (*compteVoisinsVivants) (int, int, grille) = &compte_voisins_vivants_cycliques;
void (*evolue) (grille *g, grille *gc, int (*cyclique_ou_pas)(int,int,grille))=&evolue_sv;

int memes_grilles(grille gf, grille gs) {
  if(gf.nbc != gs.nbc || gf.nbl != gs.nbl){
    return 0;
  }
  for (int i = 0; i < gf.nbl; i++) {
    for (int j = 0; j < gs.nbc; j++) {
      if (est_vivante(i, j, gf) != est_vivante(i, j, gs)) {
	return 0;
      }
    }
  }
  return 1;
}

int vide(grille g){
  int l = g.nbl;
  int c = g.nbc;
  for(int i = 0; i < l; i++) {
    for(int j = 0; j < c; j++) {
      if(est_vivante(i,j,g))
	return 0;
    }
  }
  return 1;
}


int oscillation(grille g){
  grille evolGrilles[MAX];
  grille gNow;
  alloue_grille(g.nbl, g.nbc, &gNow);
  copie_grille(g, gNow);
  grille gEvol;
  alloue_grille(g.nbl, g.nbc, &gEvol);
  
  for(int i = 0; i < MAX; i++){
    if(vide(g)){
      return -1;
    }
    alloue_grille(g.nbl, g.nbc, &evolGrilles[i]);
    copie_grille(gNow, evolGrilles[i]);
    evolue(&gNow, &gEvol, compteVoisinsVivants);
    for(int j = 0; j < i; j++){
      if(memes_grilles(evolGrilles[j], gNow) == 1){
	libere_grille(&gNow);
	libere_grille(&gEvol);
	for(int k = 0; k < i; k++){
		libere_grille(&evolGrilles[k]);
	}
	return i+1;
      }
    }
  }
	libere_grille(&gNow);
	libere_grille(&gEvol);
	for(int k = 0; k < MAX; k++){
		libere_grille(&evolGrilles[k]);
	}
  return -1;
}

void affiche_grille_gr(cairo_surface_t *surface, grille g){
  cairo_t *cr;
  cr=cairo_create(surface);
  
  cairo_set_source_rgb(cr, 0.5, 0.5, 0);
  cairo_paint(cr);
  
  cairo_rectangle(cr, 0.18*SIZEX, 0.96*SIZEY, 16*SIZEX/60, 1.5*SIZEY/60);
  cairo_set_source_rgb(cr, 0.5, 0.5, 0.5);
  cairo_fill(cr);
  cairo_stroke(cr);

  //Zone d'entrée nouvelle grille
  cairo_set_source_rgb(cr, 1, 1, 1);
  cairo_move_to(cr, SIZEX/60, 0.98*SIZEY);
  cairo_show_text(cr, "Entrer la nouvelle grille :");
  cairo_move_to(cr, 0.19*SIZEX, 0.98*SIZEY);
  cairo_show_text(cr, fileName);

  //affichage tps d'évol
  cairo_move_to(cr, SIZEX/2, 0.98*SIZEY);
  sprintf(charEvol, "%d", evol);
  strcpy(textEvol, "Temps d'évolution: ");
  cairo_show_text(cr, strcat(textEvol, charEvol));

  //affichage période
  cairo_move_to(cr, SIZEX/1.25, 0.98*SIZEY);
  sprintf(charOsc, "%d", var_osc);
  strcpy(textOsc, "Periode: ");
  cairo_show_text(cr, strcat(textOsc, charOsc));
  
  for(int l = 0; l < g.nbl; l++){
    for(int c = 0; c < g.nbc; c++){
      cairo_set_source_rgb(cr, 0, 0.1, 0);
      cairo_rectangle(cr,c*TAILLE_CX,l*TAILLE_CY,TAILLE_CX,TAILLE_CY);
      float deg = 0.125;
      if(est_vivante(l,c,g)){
	for(int coul = 1; coul<=8; coul++){
	  if(g.cellules[l][c]==coul){
	    cairo_set_source_rgb(cr, 0.0, 0.0, 1.0-(0.111*((float)coul)));
	    cairo_fill(cr);
	  }
	}
      }
      if(est_nonViable(l,c,g)){
	  cairo_set_source_rgb(cr, 1.0, 0.0, 0.0);
	  cairo_fill(cr);
      }
      cairo_stroke(cr);
    }
  }
  cairo_destroy(cr);
}

void debut_jeu(grille *g, grille *gc){
  // X11 display                                                    
        Display *dpy;
	Window rootwin;
	Window win;
        XEvent e;
        int scr;

	TAILLE_CX = (double)(SIZEX)/((g->nbc));
        TAILLE_CY = (double)(SIZEY-0.05*SIZEY)/((g->nbl));

	// init the display
	if(!(dpy=XOpenDisplay(NULL))) {
                fprintf(stderr, "ERROR: Could not open display\n");
                exit(1);
        }

	 scr=DefaultScreen(dpy);
        rootwin=RootWindow(dpy, scr);

        win=XCreateSimpleWindow(dpy, rootwin, 1, 1, SIZEX, SIZEY, 0,
                        BlackPixel(dpy, scr), BlackPixel(dpy, scr));

        XStoreName(dpy, win, "Jeu de la vie");
        XSelectInput(dpy, win, ExposureMask|ButtonPressMask|KeyPressMask|KeyReleaseMask);
        XMapWindow(dpy, win);

	// create cairo surface                                           
	cairo_surface_t *cs;
	cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), SIZEX, SIZEY);

	while(1) {
		XNextEvent(dpy, &e);
		if(e.type==Expose && e.xexpose.count<1) { //affichage de la grille
		  affiche_grille_gr(cs, *g);
		}
		else if(e.type==ButtonPress && e.xbutton.button == 1){ // gestion de l'évolution, touche 'e'
		  evolue(g, gc, compteVoisinsVivants);
		  evol++;
		  affiche_grille_gr(cs, *g);
		}
		if(e.type==KeyPress && e.xbutton.button == 54){ // gestion du mode cyclique, touche 'c'
		  if(compteVoisinsVivants == &compte_voisins_vivants_cycliques){
		    compteVoisinsVivants = &compte_voisins_vivants_non_cycliques;
		  }
		  else{
		    compteVoisinsVivants = &compte_voisins_vivants_cycliques;
		  }
		  affiche_grille_gr(cs, *g);
		}
		if(e.type==KeyPress && e.xkey.keycode==55){ // gestion du vieillissement, touche 'v'
		  if(evolue==&evolue_sv){
		    evolue=&evolue_v;
		  }
		  else{
		    evolue=&evolue_sv;
		  }
		  affiche_grille_gr(cs, *g);
		}
		if(e.type==KeyPress && e.xkey.keycode==57) // gestion du chargement d'une nouvelle grille, touche 'n'
		{
		  KeySym key;	   	
		  char lettre[256];
		  while(1)
		  {
		    XNextEvent(dpy, &e);
		    if (e.type==KeyPress && XLookupString(&e.xkey,lettre,256,&key,0)==1)
		      {
			if(e.xkey.keycode == 36) // entrée de saisie + chargement de la grille
			  {
			    libere_grille(g);
			    libere_grille(gc);

			    init_grille_from_file(fileName, g);
			    alloue_grille(g->nbl, g->nbc, gc);

			    TAILLE_CX = SIZEX/((g->nbc));
			    TAILLE_CY = (SIZEY-0.05*SIZEY)/((g->nbl));
			    
			    affiche_grille_gr(cs, *g);
			    break;
			  }
			else if(e.xkey.keycode == 22){ // deletion de caractères
			  fileName[strlen(fileName)-1] = '\0';
			}
			else // ajour du caractère
			{
			  strcat(fileName, lettre); 
			}
		      }
		    evol = 0;
		    affiche_grille_gr(cs, *g);
		  }
		}
		if(e.type==KeyPress && e.xbutton.button == 32){ // activation du compte-oscillation (=période), touche 'o'
		  var_osc = oscillation(*g);
		  affiche_grille_gr(cs, *g);
		}
		if(e.type==ButtonPress && e.xbutton.button == 3) break; // fermer la fenetre, clic droit
	}
	cairo_surface_destroy(cs); // destroy cairo surface
	XCloseDisplay(dpy); // close the display
	return;
}
