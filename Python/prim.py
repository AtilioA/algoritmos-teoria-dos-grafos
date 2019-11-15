import random
from math import inf

from aresta import Aresta


def prim(grafo):
    # Inicializa a árvore geradora mínima
    arvore = []
    # Pega um vértice inicial qualquer
    vertice = 0  # vértice aleatório -> random.randint(0, len(grafo) - 1)
    # Inicializa fila sem elementos repetidos para comparar pesos de arestas
    filaSet = set()
    filaSet.add(vertice)

    # Enquanto a árvore tem menos vértices que o grafo,
    while len(arvore) < len(grafo) - 1:
        # Inicializa variáveis do while
        min = inf
        vertice = None
        outroVertice = None

        # Pra cada vértice U da fila,
        for verticeU in filaSet:
            # Pra cada vértice V do grafo,
            for verticeV in range(len(grafo)):
                # Se o peso da aresta entre U e V for menor que o mínimo
                if grafo[verticeU][verticeV] < min:
                    # Atualiza mínimo
                    min = grafo[verticeU][verticeV]
                    # Guarda valores para mais tarde
                    vertice = verticeU
                    outroVertice = verticeV

        # Adiciona "último verticeV" para comparação posterior
        filaSet.add(outroVertice)
        # Adiciona aresta entre "últimos" U e V na árvore, já que é mínima
        arvore.append(Aresta(grafo[vertice][outroVertice], vertice, outroVertice))

        # "Retira" os dois vértices da comparação pois já foram checados
        # Nos dois sentidos pois o grafo é simples e a matriz é simétrica
        grafo[vertice][outroVertice] = inf
        grafo[outroVertice][vertice] = inf
        # Alteramos o grafo, mas estamos interessados na árvore

    return arvore


if __name__ == "__main__":
    grafo = [[inf, 1, inf, inf, 1, inf],
             [1, inf, 2, 3, inf, 1],
             [inf, 2, inf, 4, 2, 3],
             [inf, 3, 4, inf, 2, 3],
             [1, inf, 2, 2, inf, 3],
             [inf, 1, 3, 3, 3, inf]]

    grafo = prim(grafo)
    print("Imprimindo árvore geradora mínima:")
    for aresta in grafo:
        print("Peso {} - {} {}".format(aresta.peso, aresta.first, aresta.second))
