#ifndef FIFO_STRUCT_H
#define FIFO_STRUCT_H

typedef struct fifo Fifo; 
struct fifo {
    struct fifo *next;
    struct noeud *noeud;
};

#endif




#ifndef FIFO_H
#define FIFO_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "arbre.h"

Fifo * initFifo(unsigned int size);
void freeFifo(Fifo *fifo);
bool isEmpty(Fifo *fifo);
bool isFull(Fifo *fifo);
Fifo * head(Fifo *fifo);
Fifo * queue(Fifo *fifo);
bool enfiler(Fifo *fifo, Noeud *element);
Noeud * defiler(Fifo *fifo);


#endif
