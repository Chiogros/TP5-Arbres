#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "point.h"
#include "arbre.h"
#include "fifo.h"

int main() {

    unsigned int size = 7;
    
    srand(time(NULL));  // pour la valeur aléatoire lors de la suppression d'un nœud
    
    Point repere = { 0, 0, 0 };
    Noeud racine = { NULL, NULL, NULL};
    Fifo *fifo = initFifo(size);
    
    while (1) {
        
        Point *p = malloc(sizeof(*p));
        int val;
        
        printf("1 - ajouter un point\n");
        if (racine.cle) {
            printf("2 - retirer un point\n");
        }
        printf("3 - afficher l'arbre\n");
        printf("Que voulez-vous faire : ");
        
        scanf(" %i", &val);
        
        switch (val) {
            case 1:
                printf("Quelles valeurs (x, y, z) du point voulez-vous ajouter : \n");
                printf("x : ");
                scanf(" %i", &(p->x));
                printf("y : ");
                scanf(" %i", &(p->y));
                printf("z : ");
                scanf(" %i", &(p->z));
                if (!InsererNoeud(&racine, p, &repere, fifo)) {
                    printf("Le point "); AfficherPoint(p); printf(" existe déjà\n");
                }
                break;
            case 2:
                if (!racine.cle) {
                    printf("Impossible de supprimer un point : l'arbre est vide\n");
                    break;
                }
                printf("Quelles valeurs (x, y, z) du point voulez-vous retirer : \n");
                printf("x : ");
                scanf(" %i", &(p->x));
                printf("y : ");
                scanf(" %i", &(p->y));
                printf("z : ");
                scanf(" %i", &(p->z));
                if (!SupprimerNoeud(&racine, p, fifo)) {
                    printf("Le point "); AfficherPoint(p); printf(" n'existe pas\n");
                }
                free(p);
                break;
            case 3:
                AfficherArbre(&racine);
                break;
            default:
                break;
        }
    }
    
    return 0;
}
