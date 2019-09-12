// Guard para evitar dupla inclusão
#ifndef __grafo_encadeado_a_H
#define __grafo_encadeado_a_H

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
    Celula *primeiro;
    Celula *ultimo;
} Lista;

typedef struct Grafo
{
    int nVertices;
    Lista **adj;
} Grafo;

void cria_grafo(Grafo *g, int vertices);
void destroi_grafo(Grafo *g);

// Faz a lista ficar vazia
void cria_lista(Lista *lista);

// Verifica se a lista está vazia
int esta_vazia(Lista *lista);

// Verifica se existe um produto com um dado código na lista
// int codigoExistente(int codigo, Lista *lista);

void insere_lista(Lista *lista, int chave);

// Insere um vertice adjacente na lista do vertice de origem
void insere_aresta(Grafo *g, vertice origem, vertice destino);

// Retorna a quantidade de uma lista
int quantidade_lista(Lista *lista);

// Libera uma lista
void destroi_lista(Lista *lista);

// Imprime os produtos da lista
void imprime_lista(Lista *lista);

void imprime_grafo(Grafo *g);

// Busca um produto pelo código
// tProduto buscaCodigo(Lista *lista, int codigo);


#endif