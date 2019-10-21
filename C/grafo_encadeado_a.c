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

void prof(Lista **adj, vertice v)
{
    // for (int i = 0; i < adj[v]->tamanho; i++)
    // {
    Celula *atual = adj[v]->primeiro;
    adj[v]->visitado = 1;
    while (atual->prox != NULL)
    {
        if (adj[atual->rotulo]->visitado == 0)
        {
            printf("de %i para %i\n", v, atual->rotulo);
            prof(adj, atual->rotulo);
        }
        atual = atual->prox;
    }
}


void busca_prof(Grafo *g)
{
    int i = 0;

    for (i; i < g->nVertices; i++)
    {
        g->adj[i]->visitado = 0;
    }

    for (i; i < g->nVertices; i++)
    {
        if (g->adj[i]->visitado == 0)
        {
            prof(g->adj, i);
        }
    }
}

void cria_lista(Lista *lista)
{
    lista->primeiro = (Celula *)malloc(sizeof(Celula));
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
    insere_lista(g->adj[destino], origem);
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

        // Percorre a lista até chegar em NULL
        for (aux = lista->primeiro; aux->prox != NULL; aux = aux->prox)
        {
            if (aux->prox->prox != NULL)
            {
                printf("%d -> ", aux->rotulo);
            }
            else
            {
                printf("%d ", aux->rotulo);
            }
        }
    }
}

void imprime_grafo(Grafo *g)
{
    for (int i = 0; i < g->nVertices; i++)
    {
        printf("[%i] -> ", i);
        imprime_lista(g->adj[i]);
        printf("\n");
    }
}

void destroi_lista(Lista *lista)
{
    if (lista != NULL)
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
}

void destroi_grafo(Grafo *grafo)
{
    if (grafo != NULL)
    {
        for (int i = 0; i < grafo->nVertices; i++)
        {
            destroi_lista(grafo->adj[i]);
            free(grafo->adj[i]);
        }
        // free(grafo);
        free(grafo->adj);
    }
}

int contem(int nm, Lista *v)
{
    Celula *aux = v->primeiro;

    while (aux->prox != NULL)
    {
        if (aux->rotulo == nm)
        {
            return 1;
        }
        aux = aux->prox;
    }

    return 0;
}

Lista *sub(Lista *v1, Lista *v2)
{
    Lista *sub = malloc(sizeof(Lista));
    Celula *aux = v1->primeiro;
    cria_lista(sub);

    while (aux->prox != NULL)
    {
        if (!contem(aux->rotulo, v2))
        {
            insere_lista(sub, aux->rotulo);
        }
        aux = aux->prox;
    }

    return sub;
}

Lista *uniao_listas(Lista *v1, Lista *v2)
{
    Celula *aux = v1->primeiro;
    Celula *aux2 = v2->primeiro;
    Lista *uni = malloc(sizeof(Lista));
    cria_lista(uni);

    while (aux->prox != NULL)
    {
        insere_lista(uni, aux->rotulo);
        aux = aux->prox;
    }
    while (aux2->prox != NULL)
    {
        if (!(contem(aux2->rotulo, v1)))
        {
            insere_lista(uni, aux2->rotulo);
        }
        aux2 = aux2->prox;
    }
    return uni;
}

void cria_fila(Lista *fila)
{
    fila->primeiro = NULL;
    fila->ultimo = NULL;
    fila->tamanho = 0;
}

void enfileirar(int rotulo, Lista *fila)
{
    if (fila->primeiro == NULL)
    {
        fila->primeiro = malloc(sizeof(Celula));
        fila->ultimo = fila->primeiro;
        fila->tamanho++;
        fila->primeiro->rotulo = rotulo;
        return;
    }

    fila->ultimo->prox = malloc(sizeof(Celula));
    fila->ultimo->prox->rotulo = rotulo;
    fila->ultimo = fila->ultimo->prox;
    fila->tamanho++;
}
