#include <stdio.h>
#include <stdlib.h>
#include "grafo_encadeado.h"

int main()
{
    Lista *grafo;
    // tProduto item;

    cria_lista(grafo);
    printf("Lista vazia criada com sucesso!\n");

    // printf("Inserindo itens...\n");
    // item = criaProduto(1,"Sabonete", 10, 3.90);
    // insere(item, &lista);

    printf("Imprimindo a lista:\n");
    // imprime_lista(grafo);

    printf("\n\n");
    // destroiLista(grafo);
    printf("Lista destruida com sucesso!\n");

    return 0;
}
