#include <stdio.h>
#include <stdlib.h>
#include "grafo_encadeado_a.h"

int main()
{
    // Lista *lista = malloc(sizeof(Lista));
    Grafo *grafo = malloc(sizeof(Grafo));

    cria_grafo(grafo, 10);
    printf("Grafo vazio criado com sucesso!\n");

    // cria_lista(lista);
    // printf("Lista vazia criada com sucesso!\n");

    printf("Inserindo vertices...\n");
    insere_aresta(grafo, 1, 8);
    insere_aresta(grafo, 0, 2);
    insere_aresta(grafo, 3, 3);
    insere_aresta(grafo, 3, 8);
    insere_aresta(grafo, 3, 7);
    // insere_aresta(grafo, 4, 2);
    // insere_aresta(grafo, 5, 6);
    // insere_aresta(grafo, 6, 5);
    // insere_aresta(grafo, 3, 0);
    insere_aresta(grafo, 3, 2);
    insere_aresta(grafo, 9, 4);

    printf("Imprimindo a lista:\n");
    imprime_grafo(grafo);

    printf("\n");
    // destroi_lista(lista);
    destroi_grafo(grafo);
    // free(lista->primeiro);
    // free(lista);
    free(grafo);
    printf("Lista destruida com sucesso!\n");

    return 0;
}
