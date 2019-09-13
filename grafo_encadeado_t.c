#include <stdio.h>
#include <stdlib.h>
#include "grafo_encadeado_t.h"

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

void Cria_grafo(Grafo *g, int vertices){
    g->nVertices = vertices;
    g->adjacencias = malloc(sizeof(Lista*) * vertices);
    for(int i = 0; i < vertices; i++){
        g->adjacencias[i] = malloc(sizeof(Lista));
        cria_lista(g->adjacencias[i]);
    }
}

void insere_lista(Lista *lista, vertice v){
    lista->ultimo->prox = malloc(sizeof(Celula));
    lista->ultimo->rotulo = v;
    lista->ultimo = lista->ultimo->prox;
    lista->ultimo->prox = NULL;
    lista->tamanho++;
}

void buscaUtil(Lista **adjacencias, int vertice){
    Lista *adj = adjacencias[vertice];
    Celula *atual = adj->primeiro;
    adjacencias[vertice]->visitado = 1;
    while(atual->prox != NULL){
        if(!(adjacencias[atual->rotulo]->visitado)){
            printf("de %d para %d\n", vertice, atual->rotulo);
            buscaUtil(adjacencias, atual->rotulo);
        }
        atual = atual->prox;
    }
}
/*
void busca_length(Grafo *g){
    Lista *pilha = malloc(sizeof(Lista));
    cria_lista(pilha);
    insere_lista(pilha, 0);
    while(!esta_vazia(pilha)){

    }
}

Celula *retira_fila(Lista *lista){
    Celula *ret = lista->primeiro->prox;
    if(ret == NULL){
        return NULL;
    }
    lista->primeiro->prox = lista->primeiro->prox->prox;
    return ret;
}
*/
void busca_em_depth(Grafo *g){
    for(int i = 0; i < g->nVertices; i++){
        g->adjacencias[i]->visitado = 0;
    }
    for(int i = 0; i < g->nVertices; i++){
        if(!(g->adjacencias[i]->visitado)){
            buscaUtil(g->adjacencias, i);
        }
    }
}

void insere_aresta(Grafo *g, vertice u, vertice v)
{
    insere_lista(g->adjacencias[u], v);
    insere_lista(g->adjacencias[v], u);
}

void printar_adjacencias(Grafo *g){
    for(int i = 0; i < g->nVertices; i++){
        printf("Vertice %d se conecta com ", i);
        Lista *adj = g->adjacencias[i];
        Celula *prim = adj->primeiro;
        while(prim->prox != NULL){
            printf("|%d|", prim->rotulo);
            prim = prim->prox;
        }
        printf("\n");
    }
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

void destroi_grafo(Grafo *g){
    for(int i = 0; i < g->nVertices; i++){
        destroi_lista(g->adjacencias[i]);
        free(g->adjacencias[i]);
    }
    free(g->adjacencias);
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
