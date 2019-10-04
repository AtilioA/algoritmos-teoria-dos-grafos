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

void cria_fila(Lista *lista){
    lista->primeiro = NULL;
    lista->ultimo = NULL;
    lista->tamanho = 0;
}

void enfileirar(int rotulo, Lista *lista){
    if(lista->primeiro == NULL){
        lista->primeiro = malloc(sizeof(Celula));
        lista->ultimo = lista->primeiro;
        lista->tamanho++;
        lista->primeiro->rotulo = rotulo;
        return;
    }
    lista->ultimo->prox = malloc(sizeof(Celula));
    lista->ultimo->prox->rotulo = rotulo;
    lista->ultimo = lista->ultimo->prox;
    lista->tamanho++;
}

Celula * desenfileirar(Lista *lista){
    Celula *aux = lista->primeiro;
    if(lista->primeiro == lista->ultimo && lista->primeiro != NULL){
        lista->primeiro = NULL;
        lista->ultimo = NULL;
        lista->tamanho--;
        return aux;
    }
    lista->primeiro = lista->primeiro->prox;
    lista->tamanho--;
    return aux;
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

int esta_vazia_fila(Lista *lista)
{
    if (lista->primeiro == NULL)
    {
        return 1;
    }
    return 0;
}

void Cria_grafo(Grafo *g, int vertices){
    g->nVertices = vertices;
    g->adjacencias = malloc(sizeof(Lista*) * vertices);
    for(int i = 0; i < vertices; i++){
        g->adjacencias[i] = malloc(sizeof(Lista));
        cria_lista(g->adjacencias[i]);
    }
    g->matrizAdj = malloc(sizeof(int *) * vertices);
    for(int i = 0; i < vertices; i++){
        g->matrizAdj[i] = calloc(vertices, sizeof(int));
    }
}

int contem(int nm, Lista *v){
    Celula *aux = v->primeiro;
    while(aux->prox != NULL){
        if(aux->rotulo == nm){
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}

Lista *sub(Lista *v1, Lista *v2){
    Lista *sub = malloc(sizeof(Lista));
    Celula *aux = v1->primeiro;
    cria_lista(sub);
    while(aux->prox != NULL){
        if(!contem(aux->rotulo, v2)){
            insere_lista(sub, aux->rotulo);
        }
        aux = aux->prox;
    }
    return sub;
}

Lista *uniao_listas(Lista *v1, Lista *v2){
    Celula *aux = v1->primeiro;
    Celula *aux2 = v2->primeiro;
    Lista *uni = malloc(sizeof(Lista));
    cria_lista(uni);
    while(aux->prox != NULL){
        insere_lista(uni, aux->rotulo);
        aux = aux->prox;
    }
    while(aux2->prox != NULL){
        if(!(contem(aux2->rotulo, v1))){
            insere_lista(uni, aux2->rotulo);
        }
        aux2 = aux2->prox;
    }
    return uni;
}

int conexprim(Grafo *g){
    Lista *Vzao = malloc(sizeof(Lista));
    cria_lista(Vzao);
    for(int i = 0 ; i < g->nVertices; i++){
        insere_lista(Vzao, i);
    }
    int k = conex(Vzao, g);
    destroi_lista(Vzao);
    free(Vzao);
    return k;
}

Lista *gama(int v, Grafo *g){
    return g->adjacencias[v];
}

Lista *gamaT(Lista *ver, Grafo *g){
    Celula *aux = ver->primeiro;
    Lista *lixo;
    Lista *all = malloc(sizeof(Lista));
    cria_lista(all);
    while(aux->prox != NULL){
        lixo = all;
        all = uniao_listas(all, gama(aux->rotulo, g));
        destroi_lista(lixo);
        free(lixo);
        aux = aux->prox;
    }
    return all;
}

int conex(Lista *V, Grafo *g){
    int v;
    Lista *lixo;
    Celula *aux = V->primeiro;
    if(aux->prox != NULL){
        v = aux->rotulo;
    }
    Lista *rzao = malloc(sizeof(Lista));
    cria_lista(rzao);
    insere_lista(rzao, v);
    Lista *Ylon = NULL;
    Lista *gamalixo = gamaT(rzao, g);
    Lista *subs = sub(gamalixo,rzao);
    destroi_lista(gamalixo);
    free(gamalixo);
    Lista *lixos = subs;
    while(!esta_vazia(subs)){
        lixo = Ylon;
        gamalixo = gamaT(rzao, g);
        Ylon = sub(gamalixo,rzao);
        destroi_lista(gamalixo);
        free(gamalixo);
        destroi_lista(lixo);
        free(lixo);
        lixo = rzao;
        rzao = uniao_listas(rzao, Ylon);
        destroi_lista(lixo);
        free(lixo);
        lixo = subs;
        gamalixo = gamaT(rzao, g);
        subs = sub(gamalixo,rzao);
        destroi_lista(gamalixo);
        free(gamalixo);
        destroi_lista(lixo);
        free(lixo);
    }
    lixo = Ylon;
    Ylon = rzao;
    destroi_lista(lixo);
    free(lixo);
    Lista *otroV = sub(V, Ylon);
    if(!esta_vazia(otroV)){
        int k = conex(otroV, g) + 1;
        destroi_lista(otroV);
        free(otroV);
        destroi_lista(rzao);
        free(rzao);
        destroi_lista(Ylon);
        free(Ylon);
        destroi_lista(subs);
        free(subs);
        return k;
    }
    destroi_lista(rzao);
    free(rzao);
    destroi_lista(Ylon);
    free(Ylon);
    destroi_lista(subs);
    free(subs);
    destroi_lista(otroV);
    free(otroV);
    return 1;
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

void imprimir_matriz(Grafo *g){
    for(int i = 0; i < g->nVertices; i++){
        for(int j = 0; j < g->nVertices; j++){
            printf("%d ", g->matrizAdj[i][j]);
        }
        printf("\n");
    }
}

void busca_length(Grafo *g){
    for(int i = 0; i < g->nVertices; i++){
        g->adjacencias[i]->visitado = 0;
    }
    Lista *fila = malloc(sizeof(Lista));
    Celula *aux2;
    Celula *aux;
    cria_fila(fila);
    enfileirar(0, fila);
    g->adjacencias[0]->visitado = 1;
    while(!esta_vazia_fila(fila)){
        aux = desenfileirar(fila);
        aux2 = g->adjacencias[aux->rotulo]->primeiro;
        printf("de %d para :", aux->rotulo);
        while(aux2 != NULL){
            if(!(g->adjacencias[aux2->rotulo]->visitado)){
                enfileirar(aux2->rotulo, fila);
                printf("|%d|", aux2->rotulo);
                g->adjacencias[aux2->rotulo]->visitado = 1;
            }
            aux2 = aux2->prox;
        }
        printf("\n");
        free(aux);
    }
    free(fila);
}
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
    g->matrizAdj[u][v] = 1;
    g->matrizAdj[v][u] = 1;
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


void imprime_lista(Lista *lista)
{
    Celula *aux = NULL;
    // Percorre a lista até chegar em NULL
    for (aux = lista->primeiro; aux->prox != NULL; aux = aux->prox)
    {
        printf("%d ", aux->rotulo);
    }
    printf("\n");
}


void destroi_lista(Lista *lista)
{
    if(lista == NULL){
        return;
    }
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
    for(int i = 0; i < g->nVertices; i++){
        free(g->matrizAdj[i]);
    }
    free(g->matrizAdj);
    free(g->adjacencias);
}
