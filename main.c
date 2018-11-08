#include <stdio.h>
#include <stdlib.h>
#include "arquivo.h"
#include "grafo.h"

int main() {
    char* url1;         // URL do arquivo

    int qtd_vertices;           // Guarda a qtd_vertices do grafo
    int aproximado = 400000;     // Marca a quantidade aproximada de vértices
    Grafo* g;

    url1 = (char*)malloc(sizeof(char));
    //url1 = "/home/algar/Documentos/Bianca/Grafos/email-Enron.txt";
    //url1 = "/home/algar/Documentos/Bianca/Grafos/ca-GrQc.txt";

    //url1 = "/home/bianca/Documentos/Grafos/ca-GrQc.txt";
    //url1 = "/home/bianca/Documentos/Grafos/ca-HepTh.txt";
    url1 = "/home/bianca/Documentos/Grafos/email-Enron.txt";

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
    //free(visitado);
    //getchar();

    /// Coeficiente de agrupamento do vértice
    //coeficiente_agrupamento(g);

    /// Conta componentes conexas do grafo
    //conta_componentes_conexas(g);
    
    // Verifica se grafo eh conexo
    //printf("CONEXO = %d\n", eh_conexo(g));

    // dijkstra
    dijkstra(g, 20, 125);

    libera_grafo(&g);
    //free(url1);

    return 1;
}
