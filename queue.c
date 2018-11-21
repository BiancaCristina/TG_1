#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

queue* cria_queue () {
    queue* fi = (queue*)malloc(sizeof(queue));

    if (fi == NULL) return NULL;

    fi->inicio = NULL;
    fi->tamanho = 0;

    return fi; 
}

int insere_queue_ord (queue* fi, vertice v) {
    if (fi == NULL) return -1;

    int grau = v.grau; 
    link* novo;
    link* percorre = fi->inicio;
    link* anterior = NULL; 

    novo = (link*)malloc(sizeof(link));

    if (novo == NULL) return -1; 

    novo->v = v; 

    if (fi->tamanho == 0) {
        // Fila vazia
        novo->prox = fi->inicio;
        fi->inicio = novo; 
        fi->tamanho++;
    }

    else {
        while (percorre != NULL && percorre->v.grau > grau) {
            anterior = percorre; 
            percorre = percorre->prox; 
        }

        if (percorre == fi->inicio) {
            // Insere no inicio
            novo->prox = fi->inicio;
            fi->inicio = novo; 
        }

        else {
            novo->prox = anterior->prox;
            anterior->prox = novo; 
        }

        fi->tamanho++;

    }

    return 1;

}

vertice remove_queue (queue* fi) {
    if (fi != NULL) {

        vertice removido;

        link* aux = fi->inicio; 
        removido = fi->inicio->v;

        fi->inicio = fi->inicio->prox;
        free(aux);

        fi->tamanho--;

        return removido;
    }
}

int queue_tamanho (queue* fi) {
    return fi->tamanho; 
}
 
void exibe_queue (queue* fi) {
    if (fi == NULL) printf("Fila nao existe! \n");

    link* aux = fi->inicio;

    while (aux != NULL) {
        printf("grau = %d\n", aux->v.grau);
        aux = aux->prox; 
    }
}

int queue_vazia (queue* fi) {
    if (fi == NULL) return 0;

    if (fi->inicio == NULL) return 1;

    return 0;
}

void libera_queue (queue* fi) {
    if (fi != NULL) {
        link* aux = fi->inicio;

        while (aux != NULL) {
            link* libera = aux->prox;
            free(aux);
            aux = libera; 
        }

        free(fi); 
    }
}