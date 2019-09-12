#include <stdio.h>
#include <stdlib.h>
#include "grafo_encadeado_a.h"

void cria_grafo(Grafo *g, int vertices)
{
    g->nVertices = vertices;
    g->adj = malloc(vertices * sizeof(Lista *));
    for (int i = 0; i < g->nVertices; i++)
    {
        g->adj[i] = malloc(sizeof(Lista));
        cria_lista(g->adj[i]);
    }
}

void cria_lista(Lista *lista)
{
    lista->primeiro = (Celula *)malloc(sizeof(Celula)); // lista->primeiro será a cabeça da lista
    lista->ultimo = lista->primeiro;
    lista->ultimo->prox = NULL;
    lista->tamanho = 0;
}

int esta_vazia(Lista *lista)
{
    if (lista->primeiro == lista->ultimo)
    {
        return 1;
    }

    else
    {
        return 0;
    }
}

void insere_aresta(Grafo *g, vertice origem, vertice destino)
{
    insere_lista(g->adj[origem], destino);
}

void insere_lista(Lista *lista, int chave)
{
    lista->ultimo->rotulo = chave;
    lista->ultimo->prox = (Celula *)malloc(sizeof(Celula));
    lista->ultimo = lista->ultimo->prox;
    lista->ultimo->prox = NULL;
    lista->tamanho++;
}

int quantidade_lista(Lista *lista)
{
    return lista->tamanho;
}

void imprime_lista(Lista *lista)
{
    if (lista->tamanho > 0)
    {
        Celula *aux = NULL;

        // printf("Quantidade de itens: %i\n", quantidade_lista(lista));
        // Percorre a lista até chegar em NULL
        for (aux = lista->primeiro; aux->prox != NULL; aux = aux->prox)
        {
            printf("%d ", aux->rotulo);
        }
    }
}

void imprime_grafo(Grafo *g)
{
    for (int i = 0; i < g->nVertices; i++)
    {
        imprime_lista(g->adj[i]);
        printf("\n");
    }
}

void destroi_lista(Lista *lista)
{
    Celula *atual = lista->primeiro;
    Celula *anterior = NULL;

    while (atual != NULL)
    {
        anterior = atual;
        atual = atual->prox;
        free(anterior);
    }

    lista->tamanho = -1;
}

void destroi_grafo(Grafo *grafo)
{
    for (int i = 0; i < grafo->nVertices; i++)
    {
        destroi_lista(grafo->adj[i]);
        free(grafo->adj[i]);
    }
    // free(grafo);
    free(grafo->adj);
}

/*
tProduto buscaCodigo(Lista *lista, int codigo)
{
    Celula *atual = lista->primeiro->prox;

    for (atual = lista->primeiro->prox; atual != NULL; atual = atual->prox)
    {
        if (codigo == atual->produto.codigo)
        {
            return atual->produto;
        }
    }

    tProduto produtoInvalido;
    produtoInvalido.codigo = -1;

    printf("Nao ha produto com este codigo.\n");

    return produtoInvalido;
}
*/
