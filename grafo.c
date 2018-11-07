#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grafo.h"
#include "fila.h"
#define INFINITO 24345345

struct vertice {
    int v;      // Guarda o "indice" do vertice
    int r;      // Guarda o "rótulo" do vertice (corresponde ao nome dele no .txt)
    int grau;   // Guarda o grau do vertice
};

struct aresta {
    int v1;     // Aresta origem
    int v2;     // Aresta destino
};

struct no {
    vertice v;              // Indice do vertice
    struct no* prox;
};

typedef struct no no;

struct grafo {
    int qtd_vertices;       // Guarda a quantidade de vértices do grafo
    int qtd_arestas;        // Guarda a quantidade de arestas do grafo
    vertice* info_v;        // Guarda informações sobre os vértices do grafo
    no** aresta;            // Arestas do grafo
};

/// Vertice
int formata_rotulo (Grafo* g, int vertice) {
    if (g == NULL) return -1; // Grafo não existe

    //printf("%d \n", g->info_v[vertice].r);
    return g->info_v[vertice].r;
}

int indice_rotulo (Grafo* g, int rotulo) {
    if (g == NULL) return -1;

    int i;
    int indice = -1;

    for (i=0; i< g->qtd_vertices; i++) {
        // Percorre o vetor de vértices até achar o índice do vértice que possua o rótulo

        if (g->info_v[i].r == rotulo) {
            indice = i;
            break;
        }
    }

    if (indice == -1) return -1;        // Não existe vertice com tal rotulo!
    else return indice;
}

int insere_rotulo (Grafo* g, int x, int y, int tamanho) {
    // Essa função verifica se os rótulos já estão no grafo e os insere caso não estejam
    int flagx = 0;      // Flag pra marcar caso o rotulo x já esteja no grafo
    int flagy = 0;      // Flag pra marcar caso o rótulo y já esteja no grafo
    int i;

    for (i=0; i< g->qtd_vertices; i++) {
        if (g->info_v[i].r == x)  flagx = 1;

        if (g->info_v[i].r == y)  flagy = 1;

        if (flagx == 1 && flagy == 1) {
            break;
        }
    }

    if (flagx != 1) {
        // Nesse caso, x ainda nao esta no grafo
        preenche_vertice(g, tamanho, x);
        tamanho++;
    }

    if (flagy != 1) {
        // Nesse caso, y ainda nao esta no grafo
        preenche_vertice(g, tamanho, y);
        tamanho++;
    }

    return tamanho;
}

void preenche_vertice (Grafo* g, int i, int r) {
    g->info_v[i].v = i;     // Índice do vértice == i
    g->info_v[i].r = r;     // Rótulo do vértice == r
}

/// Funçoes básicas de um grafo
Grafo* cria_grafo(int qtd_vertices) {
    if (qtd_vertices < 0) return NULL; // Quantidade de vértices invalida (negativa)

    Grafo* g = (Grafo*)malloc(sizeof(Grafo));

    if (g == NULL) {
        // Problema ao alocar grafo
        return NULL;
    }

    g->qtd_arestas = 0;
    g->qtd_vertices = qtd_vertices;

    g->info_v = (vertice*)calloc(qtd_vertices, sizeof(vertice));

    if (g->info_v == NULL) {
        // Problema ao alocar vetor de vertices
        free(g);
        return NULL;
    }

    g->aresta = (no**)calloc(qtd_vertices, sizeof(no*));

    if (g->aresta == NULL) {
        // Problema ao alocar vetor de arestas
        free(g->info_v);
        free(g);
        return NULL;
    }

    int i;      // Variável do for que aloca g->aresta[i]
    int j;      // Variavel cas de algum erro na alocacao de g->aresta[i]

    for (i=0; i< qtd_vertices; i++) {
        g->aresta[i] = (no*)malloc(qtd_vertices * sizeof(no));

        if (g->aresta[i] == NULL) {
            // Problema ao alocar g->aresta[i]

            for (j=0; j< i; j++) {
                // Desaloca cada g->aresta[i] que tenha sido alocada anteriormente
                free(g->aresta[j]);
            }

            free(g->aresta);
            free(g->info_v);
            free(g);
            return NULL;
        }
    }

    for (i=0; i< qtd_vertices; i++) {
        // Preenche os elementos de g->aresta[i] com NULL
        g->aresta[i] = NULL;
    }

    return g;
}

int insere_aresta (Grafo* g, int r1, int r2) {
    if (g == NULL || r1 < 0 || r2 < 0) return -1;   // Grafo não existe ou vértices inválidos (negativos)

    int v1, v2;
    vertice ver1, ver2;

    // Procura o indice de cada rotulo (r1 e r2)
    v1 = indice_rotulo(g, r1);
    v2 = indice_rotulo(g, r2);

    if (v1 < 0 || v2 < 0) return -1;        // Não existe vértice que possua tal rótulo

    // Preenche os vertices a serem inseridos
    ver1.r = r1;
    ver1.v = v1;
    ver2.r = r2;
    ver2.v = v2;

    // Verifica se aresta existe
    no* aux = g->aresta[v1];

    while (aux != NULL && aux->v.v != v2){
        aux = aux->prox;
    }

    if (aux != NULL) return 0;      // Aresta já existe

    // Insere no v1
    no* insere1 = (no*)malloc(sizeof(no));

    if (insere1 == NULL) return -1;     // Problema para alocar nó que insere

    insere1->v = ver2;
    insere1->prox = g->aresta[v1];
    g->aresta[v1] = insere1;

    // Insere no v2
    no* insere2 = (no*)malloc(sizeof(no));

    if (insere2 == NULL) return -1;     // Problema para alocar nó que insere

    insere2->v = ver1;
    insere2->prox = g->aresta[v2];
    g->aresta[v2] = insere2;

    // Atualiza as informações do grafo
    g->qtd_arestas++;
    g->info_v[v1].grau++;
    g->info_v[v2].grau++;

    return 1;
}

void exibe_grafo (Grafo* g) {
    int vertices = g->qtd_vertices;
    int i = 0;

    if (g == NULL) {
        printf("Grafo não existe!\n");
        return;
    }

    else if (g->qtd_arestas == 0) {
        printf("Grafo vazio!\n");
        return;
    }

    for (i=0; i< vertices; i++) {
        // Função que exibe os adjacentes
        no* aux = (no*)malloc(sizeof(no));

        if (aux == NULL) {
            // Problema ao alocar no aux
            return;
        }

        aux = g->aresta[i];

        while (aux != NULL) {
            printf("%d -> %d\n", formata_rotulo(g, i), formata_rotulo(g, aux->v.v));
            aux = aux->prox;
        }

        // Fim da função que mostra os adjacentes
    }
}

int remove_aresta (Grafo* g, int v1, int v2) {
    if (g == NULL || v1 < 0 || v2 < 0) return -1;   // Grafo não existe ou vértices inválidos (negativo)

    // Cria no auxiliar e no anterior para percorrer o grafo
    no* aux = (no*)malloc(sizeof(no));
    no* ant = NULL;

    if (aux == NULL) {
        // Problema para alocar o vetor auxiliar
        return -1;
    }

    aux = g->aresta[v1];

    // Verifica se a aresta existe
    while (aux != NULL && aux->v.v != v2) {
        ant = aux;
        aux = aux->prox;
    }

    if (aux == NULL) {
        // Se aux for NULL, a aresta não existe
        return 0;
    }

    // Remove um lado da aresta
    if (ant == NULL) {
        // Se ant for NULL, então é o primeiro no
        g->aresta[v1] = aux->prox; // Primeiro no agora aponta pra NULL
    }

    else {
        ant = aux->prox; // Elemento anterior agora aponta para NULL
    }

    free(aux); // Remove o aux

    // Remove o outro lado da aresta
    no* aux1 = (no*)malloc(sizeof(no));
    no* ant1 = NULL;

    if (aux1 == NULL) {
        // Problema ao alocar aux1
        return -1;
    }

    aux1 = g->aresta[v2];

    // Verifica a existencia da aresta
    while (aux1 != NULL && aux1->v.v != v1) {
        ant1 = aux1;
        aux1 = aux1->prox;
    }

    if (aux1 == NULL) {
        // Se aux1 for NULL, a aresta não existe
        return -1;
    }

    if (ant1 == NULL) {
        // Se ant1 for NULL, entao é o primeiro no
        g->aresta[v2] = aux1->prox;
    }

    else {
        ant1 = aux1->prox;
    }

    free(aux1);

    g->qtd_arestas--;
    g->info_v[v1].grau--;
    g->info_v[v2].grau--;

    return 1;
}

int verifica_adjacencia (Grafo* g, int v1, int v2) {
    if (g == NULL || v1 < 0 || v2 < 0) return -1; // Grafo não existe ou vértice inválidos (negativos)

    // Cria nó auxiliar para percorrer o grafo
    no* aux = (no*)malloc(sizeof(no));

    if (aux == NULL) {
        // Problema ao alocar no auxiliar
        return -1;
    }

    aux = g->aresta[v1];

    while (aux != NULL && aux->v.v != v2) {
        // Percorre os adjacentes do vértice até encontrar o v2 ou ser NULL
        aux = aux->prox;
    }

    if (aux == NULL) return 0;  // Não são adjacentes
    else return 1;              // São adjacentes
}

void libera_grafo (Grafo** g) {
    if ( g == NULL) return; // Grafo não existe

    int i;
    int vertices = (*g)->qtd_vertices;

    for (i=0; i< vertices; i++) {
        // Libera cada aresta[i]
        free((*g)->aresta[i]);
    }

    free((*g)->aresta);
    free((*g)->info_v);
    free(*g);

    (*g) = NULL;    // Faz o endereço do grafo apontar para NULL
}

/// Funções específicas do trabalho
int numero_vertices (Grafo* g) {
    if (g == NULL) return -1;

    else return g->qtd_vertices;
}

int numero_arestas (Grafo* g) {
    if (g == NULL) return -1;       // Grafo não existe

    return g->qtd_arestas;
}

int conta_adjacentes (Grafo* g, int v1) {
    if (g == NULL || v1 < 0) return -1; // Grafo não existe ou vértice inválido (negativo)

    int qtd_adjacentes = 0;
    // Cria nó para percorrer os adjacentes de v1
    no* aux = (no*)malloc(sizeof(no));

    if (aux == NULL) {
        // Problema ao alocar nó auxiliar
        return -1;
    }

    aux = g->aresta[v1];

    while (aux != NULL) {
        // Percorre os adjacentes de v1 até ser NULL
        qtd_adjacentes++;
        aux = aux->prox;
    }

    return qtd_adjacentes;
}

int maximo_adjacente (Grafo* g) {
    if (g == NULL) return -1;   // Grafo não existe

    int i;
    int max_adj = 0;    // Variável que guarda o max_adj
    int temp;           // Variável que guarda temporariamente o max_adj
    int vertices = g->qtd_vertices;

    for (i=0; i< vertices; i++) {
        temp = conta_adjacentes(g, i);

            if (temp > max_adj) {
            max_adj = temp;
        }
    }

    printf("MAIOR = %d\n", max_adj);

    return max_adj;
}

int grau_medio (Grafo* g) {
    if (g == NULL) return -1; // Grafo não existe

    int i;
    int soma = 0;   // Guarda a somatória dos graus
    int vertices = g->qtd_vertices;
    float media;    // Guarda a média

    for (i=0;i< vertices; i++) {
        soma += g->info_v[i].grau;
    }

    media = soma;
    media = media/vertices;

    //printf("\n\n\nMEDIA = %f\n", media);
    return media;
}

float densidade (Grafo* g) {
    if (g == NULL) return -1; // Grafo não existe

    float arestas = g->qtd_arestas;
    float vertices = g->qtd_vertices;
    float densidade;

    densidade = (2*arestas)/ (vertices * (vertices - 1));

    printf("DENSIDADE = %f\n", densidade);
    return densidade;
}

float porcentagem_extremos(Grafo* g) {
    if (g == NULL) return -1; // Grafo não existe

    int i=0;
    int contador = 0;   // Variável que conta a quantidade de extremos do grafo
    float porcentagem;

    for (i=0;i< g->qtd_vertices; i++) {
        if (g->info_v[i].grau == 1) contador++; // Incrementa o contador se o grau de um determinado vértice for igual a 1
    }

    porcentagem = contador;
    porcentagem = porcentagem/ g->qtd_vertices;

    printf("Porcentagem = %.2f\n", (porcentagem*100));

    return porcentagem;
}
