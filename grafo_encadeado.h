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
    Celula *primeiro;
    Celula *ultimo;
} Lista;

typedef struct Grafo
{
    int nVertices;
    Lista *listas;
} Grafo;

// Faz a lista ficar vazia
void cria_lista(Lista *lista);

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

// Busca um produto pelo código
// tProduto buscaCodigo(Lista *lista, int codigo);


#endif
