#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

/// Funções básicas do grafo
typedef struct grafo Grafo;
Grafo* cria_grafo (int qtd_vertices);                           // Função que cria o grafo
int insere_aresta (Grafo* g, int r1, int r2);                   // Função que insere uma aresta no grafo
int remove_aresta (Grafo* g, int v1, int v2);                   // Função que remove uma aresta do grafo
int verifica_adjacencia (Grafo* g, int v1, int v2);             // Função que verifica se dois vértices são adjacentes
void exibe_grafo (Grafo* g);                                    // Função que exibe o grafo
void libera_grafo (Grafo** g);                                  // Função que libera o grafo

/// Vértice
typedef struct vertice {
    int v;      // Guarda o "indice" do vertice
    int r;      // Guarda o "rótulo" do vertice (corresponde ao nome dele no .txt)
    int cor;    // Guarda a cor do vertice
    int grau;   // Guarda o grau do vertice
} vertice;

int formata_rotulo (Grafo* g, int vertice);                         // Função que retorna o rótulo de um vértice
int indice_rotulo (Grafo* g, int rotulo);                           // Retorna o índice de um vértice à partir do seu rótulo
int insere_rotulo (Grafo* g, int x, int y, int tamanho);            // Função que verifica se os rótulos x e y já estão presentes no grafo e os insere
int insere_rotulo_v2 (Grafo* g, int x, int tamanho);                // Função que verifica se o rótulo x já está presente no grafo e o insere
void preenche_vertice (Grafo* g, int i, int r);                     // Função que insere o vértice no grafo

/// Aresta
typedef struct aresta aresta;

/// Funções específicas do trabalho
int numero_vertices (Grafo* g);                                 // Função que retorna a quantidade de vertices de um grafo
int numero_arestas (Grafo* g);                                  // Função que retorna a quantidade de arestas do grafo
int conta_adjacentes (Grafo* g, int v1);                        // Função que conta os vértices adjacentes a um vértice específico
int maximo_adjacente (Grafo* g);                                // Função que retorna qual a quantidade máxima de adjacentes do grafo
int grau_medio (Grafo* g);                                      // Função que retorna o grau médio do grafo
float densidade (Grafo* g);                                     // Função que calcula a densidade do grafo
float porcentagem_extremos(Grafo* g);                           // Função que calcula quantos vétices extremos existem no grafo
int busca_largura (Grafo* g, int* visitado, int v1);            // Função que faz busca em largura à partir de um vértice específico
float agrupamento_vertice (Grafo* g, int v1);                   // Função que retorna o coeficiente de agrupamento de um dado vértice
float coeficiente_agrupamento (Grafo* g);                       // Função que retorna o coeficiente de agrupamento do grafo
int conta_componentes_conexas (Grafo* g);                       // Função que conta a quantidade de componentes conexas do grafo
int eh_conexo (Grafo* g);                                       // Função que verifica se um grafo é conexo
int dijkstra (Grafo* g, int v1, int v2);                        // Função que calcula o menor caminho entre dois vértices
float centralidade_vertice (Grafo* g, int v1);                  // Função que calcula a centralidade de um vértice
float centralidade_grafo (Grafo* g);                            // Função que calcula a centralidade do grafo
Grafo* maior_componente_conexa (Grafo* g);                      // Função que retorna a maior componente conexa do grafo
int maior_caminho (Grafo* g, int v1, int v2);                   // Função que calcula o maior caminho entre dois vértices
int maior_grau (Grafo* g);                                      // Função que retorna qual maior grau do grafo
int numero_cromatico (Grafo* g);                                // Função que calcula o número cromático do grafo
int excentricidade_vertice (Grafo* g, int v1);
float excentricidade_grafo (Grafo* g);
int diametro_raio_grafo (Grafo* g);
float vertices_centrais (Grafo* g); 

#endif // GRAFO_H_INCLUDED
