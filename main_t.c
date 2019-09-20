#include <stdio.h>
#include <stdlib.h>
#include "grafo_encadeado_t.h"

int main()
{
    Grafo *grafo = malloc(sizeof(Grafo));
    // tProduto item;

    Cria_grafo(grafo, 12);
    insere_aresta(grafo, 0, 3);
    insere_aresta(grafo, 0, 1);
    insere_aresta(grafo, 0, 2);
    insere_aresta(grafo, 1, 2);
    insere_aresta(grafo, 7, 6);
    insere_aresta(grafo, 6, 5);
    insere_aresta(grafo, 6, 4);
    insere_aresta(grafo, 8, 10);
    insere_aresta(grafo, 10, 9);
    insere_aresta(grafo, 9, 11);
    insere_aresta(grafo, 11, 8);
    printf("Lista vazia criada com sucesso!\n");
    printar_adjacencias(grafo);
    // printf("Inserindo itens...\n");
    // item = criaProduto(1,"Sabonete", 10, 3.90);
    // insere(item, &lista);
    printf("Componentes conexas %d\n", conexprim(grafo));
    printf("Imprimindo a lista:\n");
    // imprime_lista(grafo);
    busca_em_depth(grafo);
    printf("\n\n");
    // destroiLista(grafo);
    busca_length(grafo);
    printf("\n");
    printf("Lista destruida com sucesso!\n");
    imprimir_matriz(grafo);
    destroi_grafo(grafo);
    free(grafo);
    return 0;
}
