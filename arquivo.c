#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "grafo.h"

int conta_vertices (int aproximado, char* url) {
    int i, k;
    int qtd_vertices = 0;        // Variavel que guarda a quantida de vértices inseridas
    int* rotulos;                // Variável para guardar os rótulos
    FILE* arq;

    arq = fopen(url, "r");

    if (arq == NULL) {
        printf("Problema ao ler o arquivo\n");
        return -1;
    }

    else {
        printf("CONTANDO A QUANTIDADE DE VÉRTICES...\n");
        int x, y;
        int flagx=0, flagy=0;       // Flags pra marcar se um vértice já pertence ao grafo

        rotulos = (int*)malloc(aproximado * sizeof(int));

        if (rotulos == NULL) return -1;         // Problema ao alocar vetor de rotulos

        for(i=0; !feof(arq); i++) {
            fscanf(arq, "%d %d", &x, &y);

            for (k=0; k< qtd_vertices; k++) {
                if (rotulos[k] == x)    flagx = 1;

                if (rotulos[k] == y)    flagy = 1;

                if (flagx == 1 && flagy == 1) break;
            }

            if (flagx != 1) {
                // Nesse caso, x não está no grafo
                rotulos[qtd_vertices] = x;
                qtd_vertices++;
            }

            if (flagy != 1) {
                // Nesse caso, y não está no grafo
                rotulos[qtd_vertices] = y;
                qtd_vertices++;
            }

            flagx = 0;
            flagy = 0;

        }
    }

    free(rotulos);

    return qtd_vertices;
}

int le_vertice (Grafo* g, char* url) {
    if (g == NULL) return -1;   // Grafo não existe

    int i;
    int tamanho = 0;        // Variavel que guarda a quantida de vértices inseridas
    FILE* arq;

    arq = fopen(url, "r");

    if (arq == NULL) {
        printf("Problema ao ler o arquivo\n");
        return -1;
    }

    else {
        int x, y;

        for(i=0; !feof(arq); i++) {
            fscanf(arq, "%d %d", &x, &y);

            tamanho = insere_rotulo(g, x, y, tamanho);
        }
    }


    return 1;
}

int le_aresta (Grafo* g, char* url) {
    if (g == NULL) return -1;   // Grafo não existe

    int contador = 0;

    FILE* arq;

    arq = fopen(url, "r");

    if (arq == NULL) {
        printf("Problema ao ler o arquivo\n");
        return -1;
    }

    else {
        int v1, v2;

        while (!feof(arq)) {
            // Enquanto não chegar no fim do arquivo
            fscanf(arq, "%d %d", &v1, &v2);

            insere_aresta(g, v1, v2);
            printf("INSERINDO ARESTA... CONT = %d\n", contador);
            contador++;
        }
    }

    return 1;
}
