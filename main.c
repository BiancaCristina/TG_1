#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
    url1 = "/home/bianca/Documentos/Grafos/ca-HepTh.txt";
    //url1 = "/home/bianca/Documentos/Grafos/email-Enron.txt";

    /// Conta a quantidade de vértices do grafo
    qtd_vertices = conta_vertices(aproximado, url1);
    
    /// Cria o grafo
    g = cria_grafo(qtd_vertices);

    /// Insere os vertices + rótulos no grafo
    le_vertice(g, url1);

    /// Insere as arestas no grafo
    le_aresta(g, url1);

    // Quantidade de componentes conexas 
    //printf("Componentes conexas antes de pegar a maior = %d\n", conta_componentes_conexas(g));
    
    // Maior componente conexa
    g = maior_componente_conexa(g); 

    // Grafo conexo
    //printf("CONEXO = %d\n", eh_conexo(g));
    
    // Numero de vertices
    //printf("VERTICES = %d\n", numero_vertices(g));

    // Numero de arestas
    //printf("ARESTAS = %d\n", numero_arestas(g));

    // Grau medio
    //printf("GRAU MEDIO = %d\n", grau_medio(g));
    // Numero cromatico
    // ?

    // Maior grau
    //printf("Maior grau = %d\n", maior_grau(g));
    
    // Numero cromatico
    //printf("Numero cromatico = %d \n", numero_cromatico(g));

    // Excentricidade media
    //excentricidade_vertice(g,0);
    //excentricidade_grafo(g);

    // Diametro + raio
    diametro_raio_grafo (g);
    //free(url1);

    return 1;
}
