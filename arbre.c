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



Noeud * RechercherLargeur(Point *pointATrouver, Noeud *noeudActuel) {
    
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



bool InsererNoeud(Point *repere, Noeud *noeudActuel, Point *pointAInserer) {
    
    if (!noeudActuel->cle) {
        noeudActuel->cle = pointAInserer;
        AfficherPoint(noeudActuel->cle); printf(" inséré en tête\n");
        return true;
    } 
    
    float comp = dist(pointAInserer, repere) - dist(noeudActuel->cle, repere);
    
    if (!comp) {
        return false;
    }
    
    Noeud **noeudCote = comp < 0 ? &(noeudActuel->gauche) : &(noeudActuel->droit);
    
    if (*noeudCote) {
        return InsererNoeud(repere, *noeudCote, pointAInserer);
    }
    
    *noeudCote = malloc(sizeof(**noeudCote));
    (*noeudCote)->cle = pointAInserer;
    
    // Afficher où s'est inséré le point
    AfficherPoint((*noeudCote)->cle); printf(" inséré à "); 
    comp < 0 ? printf("gauche") : printf("droite");
    printf(" de "); AfficherPoint(noeudActuel->cle); printf("\n");
    
    return true;
}



bool SupprimerNoeud(Noeud *noeudActuel, Point *pointASupprimer) {
    
    Noeud *noeudASupprimer = RechercherProfondeur(pointASupprimer, noeudActuel);
    if (!noeudASupprimer) { // si le point à supprimer n'existe pas
        return false;
    }
    
    Noeud *gauche = noeudASupprimer->gauche, *droit = noeudASupprimer->droit;
    
    if (gauche && droit) {
        int r = rand() % 2; // pour garder l'arbre équilibré
        Noeud *n;
        // en fonction du r, par à gauche puis tout à droite ou à droite puis tout à gauche chercher le dernier noeud
        for (n = r ? noeudASupprimer->droit : noeudASupprimer->gauche ; r ? n->gauche : n->droit ; n = r ? n->gauche : n->droit);
        // cherche le noeud parent à celui qui va venir remplacer celui qui va être supprimé
        Noeud *nParent = RechercherNoeudPrecedent(n->cle, noeudActuel);
        // supprime la liaison du noeud parent avec le noeud fils qui est réutilisé
        nParent->gauche == noeudASupprimer ? (nParent->gauche = NULL) : (nParent->droit = NULL);
        // remplace la clé du noeud supprimé par le noeud le plus en bas
        noeudASupprimer->cle = n->cle;
        free(n);
    } else if (!(gauche || droit)) {
        // cherche le noeud parent à celui qui va être supprimé
        Noeud *nParent = RechercherNoeudPrecedent(noeudASupprimer->cle, noeudActuel);
        // si c'est le dernier noeud qu'on essaye de supprimer
        if (nParent) {
            // supprime la liaison du noeud parent avec le noeud fils qui est réutilisé
            nParent->gauche == noeudASupprimer ? (nParent->gauche = NULL) : (nParent->droit = NULL);
            free(noeudASupprimer);
        } else {
            noeudASupprimer->cle = NULL;
        }
    } else { // c'est une feuille
        Noeud *nCote = gauche ? gauche : droit;
        noeudASupprimer->cle = nCote->cle;
        noeudASupprimer->gauche = nCote->gauche;
        noeudASupprimer->droit = nCote->droit;
        free(nCote);
    }
    return true;
}



void AfficherPoint(Point *point) {
    
    printf("(%i, %i, %i)", point->x, point->y, point->z);
    
}



void AfficherNoeuds(Noeud *noeudActuel, int espace) { 

    if (noeudActuel == NULL) {
        return; 
    }
    
    espace += 10; 
    
    AfficherNoeuds(noeudActuel->droit, espace); 
    printf("\n"); 
    
    for (int i = 10; i < espace; i++) { // permet de décaler l'affichage en fonction de la position du noeud dans l'arbre
        printf(" "); 
    }
    
    AfficherPoint(noeudActuel->cle);
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




