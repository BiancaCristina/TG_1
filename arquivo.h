#ifndef ARQUIVO_H_INCLUDED
#define ARQUIVO_H_INCLUDED
#include "grafo.h"

int conta_vertices (int aproximado, char* url);          // Função que retorna a quantidade de vértices do grafo
int le_vertice (Grafo* g, char* url);                   // Função que insere os vértices no grafo
int le_aresta (Grafo* g, char* url);

#endif // ARQUIVO_H_INCLUDED
