from collections import defaultdict


def tupla2(tupla):
    return tupla[1]


# Grafo não direcionado com lista de adjacências
class Grafo:
    def __init__(self, nVertices):
        # default dictionary para armazenar o grafo
        self.grafo = defaultdict(list)
        self.nVertices = nVertices
        self.nArestas = 0
        self.visitado = [False] * (self.nVertices)
        # Inicializa listas de adjacências dos vértices
        for i in range(nVertices):
            self.grafo[i] = []

    def adiciona_aresta(self, u, v, p):
        # O vértice u possui aresta incidindo exteriormente para v
        self.grafo[u].append(((u, v), p))
        self.grafo[v].append(((v, u), p))
        self.nArestas += 1

    def remove_aresta(self, u, v, p):
        # O vértice u possui aresta incidindo exteriormente para v
        self.grafo[u].remove(((u, v), p))
        self.grafo[v].remove(((v, u), p))
        self.nArestas -= 1

    def busca(self, v):
        # Marca o vértice de entrada como visitado
        self.visitado[v] = True
        print(v, end=' ')

        # Recursão com os vértices adjacentes ao de entrada
        for i in self.grafo[v]:
            if self.visitado[i] is False:
                self.busca(i)

    def arestas_pra_lista(self):
        arestas = list()
        for vertice in g.grafo:
            arestas += g.grafo[vertice]
        return arestas

    def kruskal(self):
        arestas = self.arestas_pra_lista()
        arestas.sort(key=tupla2)

        T = Grafo(self.nVertices)

        for aresta in arestas:


if __name__ == "__main__":
    g = Grafo(5)
    # print(g.grafo)
    # for vertice in g.grafo:
    #     print(vertice)
    #     print(type(vertice))
    #     print(g.grafo[vertice])
    g.adiciona_aresta(0, 1, 1000)
    g.adiciona_aresta(0, 4, 1)
    g.adiciona_aresta(1, 3, 5)
    # print(g.grafo)
