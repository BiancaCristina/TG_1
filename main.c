#include <stdio.h>
#include <stdlib.h>
#include "arquivo.h"
#include "grafo.h"

int main() {
    char* url1;         // URL do arquivo

    int qtd_vertices;           // Guarda a qtd_vertices do grafo
    int aproximado = 400000;     // Marca a quantidade aproximada de vértices
    int maximo = 100;           // Quantidade máxima de vertices a ser analisada
    Grafo* g;

    url1 = (char*)malloc(sizeof(char));
    //url1 = "/home/algar/Documentos/Bianca/Grafos/email-Enron.txt";
    //url1 = "/home/algar/Documentos/Bianca/Grafos/ca-GrQc.txt";
    url1 = "/home/bianca/Documentos/Grafos/ca-GrQc.txt";

    /// Conta a quantidade de vértices do grafo
    qtd_vertices = conta_vertices(aproximado, url1);

    /// Cria o grafo
    g = cria_grafo(qtd_vertices);

    /// Insere os vertices + rótulos no grafo
    le_vertice(g, url1);

    /// Insere as arestas no grafo
    le_aresta(g, url1);

    /// Busca em largura
    //int* visitado = (int*)calloc(qtd_vertices, sizeof(int));
    //busca_largura(g, visitado, 0);

    /// Coeficiente de agrupamento do vértice
    //coeficiente_agrupamento(g, maximo);

    //printf("AQUI.........\n");
    libera_grafo(&g);
    //free(url1);
    exit(1);
}
