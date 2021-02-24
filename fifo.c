#include "fifo.h"



Fifo *initFifo(unsigned int size) {
  
    if (size <= 1) {
        printf("erreur : la taille de la file doit être >= 2\n");
        exit(1);
    }
    
    Fifo *fifo = malloc(sizeof(*fifo));
    Fifo *current = fifo;
    
    for (unsigned int i = 1 ; i < size ; i++) {
        current->next = malloc(sizeof(*current));
        current->noeud = NULL;
        current = current->next;
    }
    current->next = fifo;
    current->noeud = NULL;
    
    return fifo;
    
}



void freeFifo(Fifo *fifo) {
    
    Fifo *current = fifo;
    Fifo *back;
    
    do {
        
        back = current;
        current = current->next;
        free(back);
        
    } while (current != fifo);
    
}



bool isEmpty(Fifo *fifo) {
    
    Fifo *current = fifo;
    
    do {
        
        if (current->noeud) {
            return false;
        }
        current = current->next;
        
    } while (current != fifo);
    
    return true;
        
}



bool isFull(Fifo *fifo) {
    
    Fifo *current = fifo;
    
    do {
        
        if (!current->noeud) {
            return false;
        }
        current = current->next;
        
    } while (current != fifo);
    
    return true;
    
}



Fifo * head(Fifo *fifo) {

    return queue(fifo)->next;
    
}



Fifo * queue(Fifo *fifo) {
    
    Fifo *current;
    
    for (current = fifo ; current->next != fifo ; current = current->next);
    return current;

}



bool enfiler(Fifo *fifo, Noeud *element) {
    
    if (isFull(fifo) || !element) {
        return false;
    }
    
    Fifo *current;
    for (current = fifo ; current->noeud ; current = current->next);  // on ne met pas de condition pour si on arrive au bout de la file puisqu'il y a une place de libre (testé au dessus)
    current->noeud = element;
    
    return true;
    
}



Noeud * defiler(Fifo *fifo) {
    
    if (isEmpty(fifo)) {
        return NULL;
    }
    
    Fifo *current = fifo;
    Noeud *toReturn = current->noeud;
    for ( ; current->next != fifo ; current = current->next) {
        current->noeud = (current->next)->noeud;
    }
    current->noeud = NULL;
    
    return toReturn;
    
}








