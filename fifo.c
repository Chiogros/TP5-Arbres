#include "fifo.h"



Fifo * initFifo(int size) {
    
    Fifo *fifo = malloc(sizeof(*fifo));    // 3
    Fifo *current = fifo;    // 2
    
    for (int i = 1 ; i < size ; i++) {    // 3
        current->next = malloc(sizeof(*current));    // 3
        current->noeud = NULL;    // 1
        current = current->next;    // 2
    }
    current->next = fifo;    // 2
    
    return fifo;    // 2
    
}



void freeFifo(Fifo *fifo) {
    
    Fifo *current = fifo;    // 2
    Fifo *back;    // 1
    
    do {
        
        back = current;    // 2
        current = current->next;    // 2
        free(back);    // 2
        
    } while (current != fifo);    // 3
    
}



bool isEmpty(Fifo *fifo) {
    
    Fifo *current = fifo;   // 2
    bool isEmpty = true;   // 1
    
    do {
        
        if (current->noeud) {   // 2
            isEmpty = false;   // 1
            break;
        }
        current = current->next;   // 2
        
    } while (current != fifo);   // 3
    
    return isEmpty;   // 2
        
}



bool isFull(Fifo *fifo) {
    
    Fifo *current = fifo;
    bool isFull = true;
    
    do {
        
        if (!current->noeud) {
            isFull = false;
            break;
        }
        current = current->next;
        
    } while (current != fifo);
    
    return isFull;
    
}



Fifo * head(Fifo *fifo) {
    
    return fifo;
    
}



Fifo * queue(Fifo *fifo) {
    
    Fifo *current = fifo;
    do {
        
        current = current->next;
        
    } while (current != fifo);
        
    return current;
}



bool enfiler(Fifo *fifo, Noeud element) {
    
    Fifo *current = fifo;
    if (!isFull(fifo)) {
        do {
            
            if (!current->noeud) {
                current->noeud = &element;
                return true;
            } else {
                current = current->next;
            }
        } while (current != fifo);
    }
    return false;
}



Fifo * defiler(Fifo **fifo) {
    
    Fifo *defile = *fifo;
    
    if (!defile) {
        return NULL;
    } else {
        *fifo = (*fifo)->next;
        return defile;
    }
    
}



void printFifo(Fifo *fifo) {
    
    Fifo *current = fifo;
    
    do {
        
        printf("(%i, %i, %i)\n", ((current->noeud)->cle)->x, ((current->noeud)->cle)->y, ((current->noeud)->cle)->z);
        current = current->next;
        
    } while (current != fifo);
    
}












