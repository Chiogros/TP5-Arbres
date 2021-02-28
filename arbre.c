#include "arbre.h"


/*
 * O(logn) 
 * Ω(5) : O(1) + 1 + 1 + 1 + 1
 */
Noeud * RechercherProfondeur(Point *pointATrouver, Noeud *noeudActuel) {    // utilisé si activé dans la fonction SupprimerNoeud()
    
    Point p = { 0, 0, 0 };
    float distance = dist(noeudActuel->cle, &p) - dist(pointATrouver, &p);
    Noeud *cote;

    if (!distance) {
        return noeudActuel;
    } else if (distance > 0) {
        cote = noeudActuel->gauche;
    } else {
        cote = noeudActuel->droit;
    }

    return cote ? RechercherNoeudPrecedent(pointATrouver, cote) : NULL;
    
    /*float distance = dist(noeudActuel->cle, pointATrouver);
    Noeud *n;
    
    if (!distance) {
        return noeudActuel;
    } else if (distance > 0) {
        if (noeudActuel->gauche) {
            n = RechercherProfondeur(pointATrouver, noeudActuel->gauche);
            if (n) {
                return n;
            }
        }
    } else {
        if (noeudActuel->droit) {
            n = RechercherProfondeur(pointATrouver, noeudActuel->droit);
            if (n) {
                return n;
            }
        }
    }
    
    return NULL;*/
}



/*
 * O(logn)
 * Ω(6) : O(1) + O(1) + 1 + 1 + 1 + 1
 */
Noeud * RechercherNoeudPrecedent(Point *pointATrouver, Noeud *noeudActuel) {
    
    Point p = { 0, 0, 0 };
    float distance = dist(noeudActuel->cle, &p) - dist(pointATrouver, &p);
    Noeud *cote;

    if (!distance) {
        return noeudActuel;
    } else if (distance > 0) {
        cote = noeudActuel->gauche;
    } else {
        cote = noeudActuel->droit;
    }

    return !dist(cote->cle, pointATrouver) ? noeudActuel : RechercherNoeudPrecedent(pointATrouver, cote);
}


/*
 * O(n)
 */
Noeud * RechercherLargeur(Point *pointATrouver, Fifo *fifo, Noeud *racine) {
    
    if (!racine->cle) {
        return NULL;
    }
    
    Noeud *current;
    enfiler(fifo, racine);
    
    while (!isEmpty(fifo)) {
        current = defiler(fifo);
        if (!dist(current->cle, pointATrouver)) {
            return current;
        }
        if (current->gauche) { if (!enfiler(fifo, current->gauche)) { printf("Erreur : file trop petite\n"); exit(1); }}
        if (current->droit) { if (!enfiler(fifo, current->droit)) { printf("Erreur : file trop petite\n"); exit(1); }}
    }    
    return NULL;
}


/*
 * O(logn)
 */
bool SupprimerNoeud(Noeud *racine, Point *pointASupprimer, Fifo *fifo) {
    
    /* Parcours en profondeur */
    // Noeud *noeudASupprimer = RechercherProfondeur(pointASupprimer, racine);
    
    /* Parcours en largeur */
    Noeud *noeudASupprimer = RechercherLargeur(pointASupprimer, fifo, racine);
    
    if (!noeudASupprimer) { // si le point à supprimer n'existe pas dans l'arbre
        return false;
    }

    Noeud *gauche = noeudASupprimer->gauche, *droit = noeudASupprimer->droit;
    
    if (gauche && droit) { // c'est un tronc
        int r = rand() % 2; // pour garder l'arbre équilibré
        Noeud *n;
        // en fonction du r, par à gauche puis tout à droite ou à droite puis tout à gauche chercher le dernier noeud
        for (n = r ? noeudASupprimer->droit : noeudASupprimer->gauche ; r ? n->gauche : n->droit ; n = r ? n->gauche : n->droit);
        // cherche le noeud parent à celui qui va venir remplacer celui qui va être supprimé
        Noeud *nParent = RechercherNoeudPrecedent(n->cle, racine);
        // supprime la liaison du noeud parent avec le noeud fils qui est réutilisé
        nParent->gauche == n ? (nParent->gauche = NULL) : (nParent->droit = NULL);
        // remplace la clé du noeud supprimé par le noeud le plus en bas
        noeudASupprimer->cle = n->cle;
        free(n);
    } else if (gauche || droit) { // c'est une branche
        Noeud *n = noeudASupprimer->gauche ? noeudASupprimer->gauche : noeudASupprimer->droit;
        noeudASupprimer->cle = n->cle;
        noeudASupprimer->gauche = n->gauche;
        noeudASupprimer->droit = n->droit;
        free(n);
    } else { // c'est une feuille
        Noeud *nParent = RechercherNoeudPrecedent(noeudASupprimer->cle, racine);
        if (nParent == racine) { // le noeud qu'on supprime est le dernier de l'arbre
            noeudASupprimer->cle = NULL;
        } else {
            nParent->gauche == noeudASupprimer ? (nParent->gauche = NULL) : (nParent->droit = NULL);
            free(noeudASupprimer);
        }
    }
    return true;
}


/*
 * O(logn)
 */
bool InsererNoeud(Noeud *noeudActuel, Point *pointAInserer, Point *repere, Fifo *fifo) {
    
    // si aucune clé n'est déjà enregistrée
    if (!noeudActuel->cle) {
        noeudActuel->cle = pointAInserer;
        AfficherPoint(noeudActuel->cle); printf(" inséré en tête\n");
        return true;
    } 
    
    float comp = dist(pointAInserer, repere) - dist(noeudActuel->cle, repere);
    
    if (!comp) { // si == 0 alors le point existe déjà
        return false;
    }
    
    Noeud **noeudCote = comp < 0 ? &(noeudActuel->gauche) : &(noeudActuel->droit);  // point à insérer > ou < au noeud actuel
    
    if (*noeudCote) {
        return InsererNoeud(*noeudCote, pointAInserer, repere, fifo);
    }
    
    *noeudCote = malloc(sizeof(**noeudCote));
    (*noeudCote)->cle = pointAInserer;
    
    // Afficher où s'est inséré le point
    AfficherPoint((*noeudCote)->cle); printf(" inséré à "); 
    comp < 0 ? printf("gauche") : printf("droite");
    printf(" de "); AfficherPoint(noeudActuel->cle); printf("\n");
    
    return true;
}


/*
 * O(1)
 */
void AfficherPoint(Point *point) {
    
    printf("(%i, %i, %i)", point->x, point->y, point->z);
    
}


/*
 * O(n)
 */
void AfficherNoeuds(Noeud *noeudActuel, int espace) { 

    if (noeudActuel == NULL) {
        return; 
    }
    
    espace += 10; 
    
    AfficherNoeuds(noeudActuel->droit, espace); 

    for (int i = 10; i < espace; i++) { // permet de décaler l'affichage en fonction de la position du noeud dans l'arbre
        printf(" "); 
    }
    
    AfficherPoint(noeudActuel->cle);
    printf("\n");
    
    AfficherNoeuds(noeudActuel->gauche, espace); 
} 


/*
 * O(n) : hérité de AfficherNoeuds()
 */
void AfficherArbre(Noeud *racine) {
    
    if (!racine->cle) {
        printf("Arbre vide\n");
    } else {
        // Affichage de gauche à droite dans la console, i.e. la racine de l'arbre est à gauche
        printf("------------------------------------------>\n");
        AfficherNoeuds(racine, 0);
    }
}



