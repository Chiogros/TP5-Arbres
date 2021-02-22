#ifndef ARBRE_H
#define ARBRE_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "point.h"

typedef struct Noeud Noeud;
struct Noeud {
    Noeud *gauche;
    Noeud *droit;
    Point *cle;
};


Noeud * RechercherProfondeur(Point *pointATrouver, Noeud *noeudActuel);
Noeud * RechercherLargeur(Point *pointATrouver, Noeud *noeudActuel);
Noeud * RechercherNoeudPrecedent(Point *pointATrouver, Noeud *noeudActuel);
bool InsererNoeud(Point *repere, Noeud *noeudActuel, Point *pointAInserer);
bool SupprimerNoeud(Noeud *noeudActuel, Point *pointASupprimer);
void AfficherPoint(Point *point);
void AfficherNoeuds(Noeud *noeudActuel, int espace);
void AfficherArbre(Noeud *racine);










#endif
