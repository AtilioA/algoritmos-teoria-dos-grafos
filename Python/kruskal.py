# Supostamente não funciona

from aresta import Aresta
from insert import insert_sort
from collections import defaultdict

def kruskal(arestas):
    arestas, vertices = insert_sort(arestas, defaultdict())

    # Inicializa a árvore de fato
    arvore = list()
    # vertices terá o número de chaves do dicionário retornado pelo insertion_sort
    tamanhoArvore = len(vertices.keys())
    i = 0

    # Enquanto o tamanho da árvore é menor que o tamanho do dicionário de vértices,
    while len(arvore) < tamanhoArvore - 1:
        # Utilizamos todas as arestas
        aresta = arestas[i]
        i += 1

        # Para verificar o peso das arestas com o dicionário
        if vertices[aresta.first] < 2 and vertices[aresta.second] < 2:
            vertices[aresta.first] += 1
            vertices[aresta.second] += 1
            arvore.append(aresta)
    # Não se utiliza todo o dicionário pois o tamanho da árvore quebra o while antes disso

    return arvore


if __name__ == "__main__":
    arestas = list()
    # arestas.append(Aresta(1, 'a', 'b'))
    # arestas.append(Aresta(8, 'a', 'c'))
    # arestas.append(Aresta(3, 'c', 'b'))
    # arestas.append(Aresta(4, 'b', 'd'))
    # arestas.append(Aresta(2, 'd', 'e'))
    # arestas.append(Aresta(3, 'b', 'e'))
    # arestas.append(Aresta(-1, 'c', 'd'))

    # arestas.append(Aresta(13, '0', '3'))
    # arestas.append(Aresta(24, '0', '1'))
    # arestas.append(Aresta(13, '0', '2'))
    # arestas.append(Aresta(22, '0', '4'))
    # arestas.append(Aresta(13, '1', '3'))
    # arestas.append(Aresta(22, '1', '2'))
    # arestas.append(Aresta(13, '1', '4'))
    # arestas.append(Aresta(19, '2', '3'))
    # arestas.append(Aresta(14, '2', '4'))
    # arestas.append(Aresta(19, '3', '4'))

    arestas.append(Aresta(2, "0", "1"))
    arestas.append(Aresta(-10, "0", "3"))
    arestas.append(Aresta(3, "0", "2"))
    arestas.append(Aresta(5, "1", "2"))
    arestas.append(Aresta(0, "1", "3"))
    arestas.append(Aresta(4, "2", "3"))

    grafo = kruskal(arestas)
    print("Imprimindo árvore geradora mínima:")
    for aresta in grafo:
        print(f"Peso {aresta.peso:2}: {aresta.first:1} para {aresta.second:2}")
