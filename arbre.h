#ifndef ARBRE_STRUCT_H
#define ARBRE_STRUCT_H

#include "point.h"

typedef struct noeud Noeud;
struct noeud {
    Noeud *gauche;
    Noeud *droit;
    Point *cle;
};

#endif



#ifndef ARBRE_H
#define ARBRE_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "fifo.h"
#include "point.h"

Noeud * RechercherProfondeur(Point *pointATrouver, Noeud *noeudActuel);
Noeud * RechercherNoeudPrecedent(Point *pointATrouver, Noeud *noeudActuel);
Noeud * RechercherLargeur(Point *pointATrouver, Fifo *fifo, Noeud *racine);
void InsererNoeudsDansFile(Fifo *fifo, Noeud *racine, unsigned int profondeur);
void UpdateFile(Fifo *fifo, Noeud *racine);
bool InsererNoeud(Noeud *noeudActuel, Point *pointAInserer, Point *repere, Fifo *fifo);
bool SupprimerNoeud(Noeud *racine, Point *pointASupprimer, Fifo *fifo);
void AfficherPoint(Point *point);
void AfficherNoeuds(Noeud *noeudActuel, int espace);
void AfficherArbre(Noeud *racine);


#endif
