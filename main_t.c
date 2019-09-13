#include <stdio.h>
#include <stdlib.h>
#include "grafo_encadeado_t.h"

int main()
{
    Grafo *grafo = malloc(sizeof(Grafo));
    // tProduto item;

    Cria_grafo(grafo, 10);
    insere_aresta(grafo, 0, 2);
    insere_aresta(grafo, 0, 3);
    insere_aresta(grafo, 0, 4);
    insere_aresta(grafo, 1, 9);
    insere_aresta(grafo, 3, 7);
    insere_aresta(grafo, 4, 9);
    insere_aresta(grafo, 4, 5);
    insere_aresta(grafo, 5, 9);
    insere_aresta(grafo, 5, 8);
    insere_aresta(grafo, 5, 6);
    insere_aresta(grafo, 6, 8);
    insere_aresta(grafo, 6, 7);
    insere_aresta(grafo, 7, 8);
    insere_aresta(grafo, 8, 9);
    printf("Lista vazia criada com sucesso!\n");
    printar_adjacencias(grafo);
    // printf("Inserindo itens...\n");
    // item = criaProduto(1,"Sabonete", 10, 3.90);
    // insere(item, &lista);

    printf("Imprimindo a lista:\n");
    // imprime_lista(grafo);
    busca_em_depth(grafo);
    printf("\n\n");
    // destroiLista(grafo);
    printf("Lista destruida com sucesso!\n");
    destroi_grafo(grafo);
    free(grafo);
    return 0;
}
