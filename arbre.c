#include "arbre.h"




Noeud * RechercherProfondeur(Point *pointATrouver, Noeud *noeudActuel) {
    
    if (!dist(noeudActuel->cle, pointATrouver)) {   // noeud trouvé
        return noeudActuel;
    }

    Noeud *n;
    if (noeudActuel->gauche) {
        n = RechercherProfondeur(pointATrouver, noeudActuel->gauche);
        if (n) {
            return n;
        }
    }
    if (noeudActuel->droit) {
        n = RechercherProfondeur(pointATrouver, noeudActuel->droit);
        if (n) {
            return n;
        }
    }
    
    return NULL;
}



Noeud * RechercherNoeudPrecedent(Point *pointATrouver, Noeud *noeudActuel) {
    
    if (noeudActuel->gauche) {
        if (!dist((noeudActuel->gauche)->cle, pointATrouver)) {   // noeud trouvé
            return noeudActuel;
        } else {
            Noeud *n = RechercherNoeudPrecedent(pointATrouver, noeudActuel->gauche);
            if (n) {
                return n;
            }
        }
    }
    
    if (noeudActuel->droit) {
        if (!dist((noeudActuel->droit)->cle, pointATrouver)) {   // noeud trouvé
            return noeudActuel;
        } else {
            Noeud *n = RechercherNoeudPrecedent(pointATrouver, noeudActuel->droit);
            if (n) {
                return n;
            }
        }
    }
    
    return NULL;  
}



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
        if (nParent != racine ) {
            // supprime la liaison du noeud parent avec le noeud fils qui est réutilisé
            nParent->gauche == n ? (nParent->gauche = NULL) : (nParent->droit = NULL);
        } else {
            nParent->gauche == n ? (nParent->gauche = n->gauche) : (nParent->droit = n->droit);
        }
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
        if (!nParent) { // le noeud qu'on supprime est le dernier de l'arbre
            noeudASupprimer->cle = NULL;
        } else {
            nParent->gauche == noeudASupprimer ? (nParent->gauche = NULL) : (nParent->droit = NULL);
            free(noeudASupprimer);
        }
    }

    return true;
}



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



void AfficherPoint(Point *point) {
    
    printf("(%i, %i, %i)", point->x, point->y, point->z);
    
}



void AfficherNoeuds(Noeud *noeudActuel, int espace) { 

    if (noeudActuel == NULL) {
        return; 
    }
    
    espace += 9; 
    
    AfficherNoeuds(noeudActuel->droit, espace); 
    
    for (int i = 9; i < espace; i++) { // permet de décaler l'affichage en fonction de la position du noeud dans l'arbre
        printf(" "); 
    }
    
    AfficherPoint(noeudActuel->cle);
    if (noeudActuel->gauche && !noeudActuel->droit) { printf("┐"); }
    else if (!noeudActuel->gauche && noeudActuel->droit) { printf("┘"); }
    printf("\n");
    
    AfficherNoeuds(noeudActuel->gauche, espace); 
} 



void AfficherArbre(Noeud *racine) {
    
    if (!racine->cle) {
        printf("Arbre vide\n");
    } else {
        // Affichage de gauche à droite dans la console, i.e. la racine de l'arbre est à gauche
        AfficherNoeuds(racine, 0);
    }
}






