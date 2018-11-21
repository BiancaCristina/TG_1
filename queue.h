#include "grafo.h"

typedef struct link {
    vertice v; 
    struct link* prox;
} link;

typedef struct queue {
    int tamanho;
    link* inicio;
} queue;

queue* cria_queue ();
int insere_queue_ord (queue* fi, vertice v); 
vertice remove_queue (queue* fi); 
void exibe_queue (queue* fi);
void libera_queue (queue* fi); 