#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "arbre.h"

typedef struct Fifo Fifo; 
struct Fifo {
    Fifo *next;
    Noeud *noeud;
} ;


Fifo * initFifo(int size);    // 9n+9
void freeFifo(Fifo *fifo);    // 9n+3
bool isEmpty(Fifo *fifo);   // 7n+5
bool isFull(Fifo *fifo);
Fifo * head(Fifo *fifo);
Fifo * queue(Fifo *fifo);
bool enfiler(Fifo *fifo, Noeud element);
Fifo * defiler(Fifo **fifo);
void printFifo(Fifo *fifo);
