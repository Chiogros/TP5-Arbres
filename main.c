#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "point.h"
#include "arbre.h"
#include "fifo.h"

int main() {

    srand(time(NULL));  // 1 + 1 + 1
    
    Point repere = { 0, 0, 0 };
    Noeud racine = { NULL, NULL, NULL };
    
    while (1) {    // 1
        
        Point *p = malloc(sizeof(*p));    // 1 + 1 + 1
        int val;    // 1
        
        printf("1 - ajouter un point\n");    // 1
        printf("2 - retirer un point\n");    // 1
        printf("3 - afficher l'arbre\n");    // 1
        printf("Que voulez-vous faire : ");    // 1
        
        scanf(" %i", &val);    // 1 + 1
        
        switch (val) {    // 1
            case 1:    // 1
                printf("Quelles valeurs (x, y, z) du point voulez-vous ajouter : \n");    // 1
                printf("x : ");    // 1
                scanf(" %i", &(p->x));    // 1 + 1
                printf("y : ");    // 1
                scanf(" %i", &(p->y));    // 1 + 1
                printf("z : ");    // 1
                scanf(" %i", &(p->z));    // 1 + 1
                if (!InsererNoeud(&repere, &racine, p)) {
                    printf("Le point "); AfficherPoint(p); printf(" existe déjà\n");
                }
                break;
            case 2:
                printf("Quelles valeurs (x, y, z) du point voulez-vous retirer : \n");
                printf("x : ");
                scanf(" %i", &(p->x));
                printf("y : ");
                scanf(" %i", &(p->y));
                printf("z : ");
                scanf(" %i", &(p->z));
                if (!SupprimerNoeud(&racine, p)) {
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
