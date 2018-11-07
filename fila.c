#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

fila* cria_fila()
{
    fila* fi = (fila*)malloc(sizeof(fila));

    if (fi != NULL)
    {
        fi->fim = NULL;
        fi->inicio = NULL;
        fi->tamanho= 0;

    }

    return fi;
}

void libera_fila(fila* fi)
{
    /*
    if (fi != NULL)
    {
        node* aux;

        while (fi->inicio != NULL)
        {
            aux = fi->inicio;
            fi->inicio = fi->inicio->prox;
            free(aux);
        }

        free(fi);
    }

    */

    if (fi == NULL) return;     // Fila nao existe

    node* aux = fi->inicio;

    while (aux != NULL) {
        node* libera = aux->prox;
        free(aux);
        aux = libera;
    }

    free(fi);


}

int fila_tamanho(fila* fi)
{
    if (fi == NULL) return 0;

    return fi->tamanho;
}
int fila_cheia(fila* fi)
{
    return 0; // NAO EXISTE FILA CHEIA EM FILA DINAMICA
}
int fila_vazia(fila* fi)
{
    if (fi == NULL) return 0;

    if (fi->inicio == NULL) return 1;

    return 0;
}

void exibe_fila(fila* fi)
{
    node* percorre = fi->inicio;

    while (percorre != NULL)
    {
        printf("%d\n", percorre->dados);
        percorre = percorre->prox;
    }
}

int insere_fila(fila* fi, int i)
{
    if (fi== NULL) return 0;

    node* aux= (node*)malloc(sizeof(node));

    if (aux ==NULL) return 0;

    aux->dados= i;
    aux->prox= NULL;
    fi->tamanho++;

    if(fi->fim == NULL) // TESTA SE A LISTA TA VAZIA
    {
        fi->inicio = aux;
        fi->fim= aux;
    }

    else
    {
        fi->fim->prox = aux;
        fi->fim= aux;

    }

    return 1;
}
int remove_fila(fila* fi)
{
    if (fi== NULL) return 0;

    node* aux= fi->inicio;

    fi->inicio = fi->inicio->prox;
    free(aux);

    if (fi->inicio == NULL){ // FILA FICOU VAZIA
        fi->fim = NULL;

    }

    fi->tamanho--;
    return 1;
}

int remove_fila_v2 (fila* fi){ // MOSTRA QUAL ELEMENTO FOI REMOVIDO
    int removido;
    if (fi == NULL) return -1; // FILA NEM EXISTE

    node* aux = fi->inicio;
    removido = fi->inicio->dados;

    fi->inicio = fi->inicio->prox;
    free(aux);

    if (fi->inicio == NULL){ // FILA FICOU VAZIA
        fi->fim = NULL;

    }

    fi->tamanho--;

    return removido;
}


