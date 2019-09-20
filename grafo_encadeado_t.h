// Guard para evitar dupla inclusão
#ifndef __GRAFO_ENCADEADO_H
#define __GRAFO_ENCADEADO_H

typedef int vertice;
typedef int aresta;

typedef struct Celula
{
    int rotulo;
    struct Celula *prox;
} Celula;

typedef struct Lista
{
    int tamanho;
    int visitado;
    Celula *primeiro;
    Celula *ultimo;
} Lista;

typedef struct Grafo
{
    int nVertices;
    Lista **adjacencias;
    int **matrizAdj;
} Grafo;


int contem(int nm, Lista *v);

Lista *uniao_listas(Lista *v1, Lista *v2);
// Faz a lista ficar vazia
void cria_lista(Lista *lista);

void insere_lista(Lista *lista, vertice v);

Lista *sub(Lista *v1, Lista *v2);

int conexprim(Grafo *g);
int conex(Lista *V, Grafo *g);

// Verifica se a lista está vazia
int esta_vazia(Lista *lista);

// Verifica se existe um produto com um dado código na lista
// int codigoExistente(int codigo, Lista *lista);

// Insere um vertice na lista
void insere_vertice(Grafo *g, vertice v, aresta w);

// Retorna a quantidade de uma lista
int quantidade_lista(Lista *lista);

// Libera uma lista
void destroi_lista(Lista *lista);

// Imprime os produtos da lista
void imprime_lista(Lista *lista);

void insere_aresta(Grafo *g, vertice u, vertice v);

void Cria_grafo(Grafo *g, int vertices);
// Busca um produto pelo código
// tProduto buscaCodigo(Lista *lista, int codigo);

void busca_length(Grafo *g);

void printar_adjacencias(Grafo *g);

void destroi_grafo(Grafo *g);

void busca_em_depth(Grafo *g);

void imprimir_matriz(Grafo *g);

#endif
