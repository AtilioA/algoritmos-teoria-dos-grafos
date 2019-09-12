#include <stdio.h>
#include <stdlib.h>
#include "grafo_encadeado.h"

int main()
{
    Grafo *grafo = malloc(sizeof(Grafo));
    // tProduto item;

    Cria_grafo(grafo, 10);
    insere_aresta(grafo, 0, 1);
    insere_aresta(grafo, 0, 2);
    insere_aresta(grafo, 0, 3);
    insere_aresta(grafo, 0, 5);
    insere_aresta(grafo, 0, 4);
    insere_aresta(grafo, 0, 6);
    insere_aresta(grafo, 0, 7);
    insere_aresta(grafo, 7, 1);
    printf("Lista vazia criada com sucesso!\n");
    printar_adjacencias(grafo);
    // printf("Inserindo itens...\n");
    // item = criaProduto(1,"Sabonete", 10, 3.90);
    // insere(item, &lista);

    printf("Imprimindo a lista:\n");
    // imprime_lista(grafo);

    printf("\n\n");
    // destroiLista(grafo);
    printf("Lista destruida com sucesso!\n");
    destroi_grafo(grafo);
    free(grafo);
    return 0;
}
