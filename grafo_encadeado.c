#include <stdio.h>
#include <stdlib.h>
#include "grafo_encadeado.h"

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

void insere_vertice(Grafo *g, vertice v, aresta w)
{
    // else
//         lista->ultimo->prox = (Celula *)malloc(sizeof(Celula));
//         lista->ultimo = lista->ultimo->prox;
//         lista->ultimo->rotulo = v;
//         lista->ultimo->prox = NULL;
//         lista->tamanho++;
}

int quantidade_lista(Lista *lista)
{
    return lista->tamanho;
}

/*
void imprime_lista(Lista *lista)
{
    Celula *aux = NULL;

    printf("Quantidade de itens: %i\n", quantidade_lista(lista));
    // Percorre a lista até chegar em NULL
    for (aux = lista->primeiro; aux != NULL; aux = aux->prox)
    {
        imprimeProduto(aux->produto);
    }
}
*/

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

    lista->tamanho = 0;
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
