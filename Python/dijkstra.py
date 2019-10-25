from collections import defaultdict


class Grafo:
    def __init__(self, nVertices):
        self.adjs = defaultdict(list)
        self.nVertices = nVertices
        # Inicializa todos os vértices
        for vertice in range(nVertices):
            self.adjs[vertice] = []
        # <<Conjuntos>> para Dijkstra
        self.fechado = [False] * nVertices
        self.aberto = [True] * nVertices

    def adiciona_aresta(self, u, v, peso):
        self.adjs[u].append((v, peso))
        self.adjs[v].append((u, peso))

    def dijkstra(self, inicio):
        distV = list(map(lambda x: 0 if x == inicio else float("inf"), range(self.nVertices)))
        # print(distV)

        self.adjs[inicio]
        while True in self.aberto:
            indiceMenor = self.aberto.index(True)
            # print(f"Aberto: {self.aberto}")
            # print(f"Fechado: {self.fechado}")
            # print(f"Distancias: {distV}")
            for dist in distV:
                if self.aberto[distV.index(dist)] and dist < distV[indiceMenor]:
                    indiceMenor = distV.index(dist)
                # print(f"Indice Menor: {indiceMenor}, dist: {distV.index(dist)}")
            # print(indiceMenor)
            self.aberto[indiceMenor] = False
            self.fechado[indiceMenor] = True

            vizinhos = [x for x in self.adjs[indiceMenor] if self.aberto[x[0]]]
            for vizinho in vizinhos:
                custo = min(distV[vizinho[0]], distV[indiceMenor] + vizinho[1])
                distV[vizinho[0]] = custo

        return distV

g = Grafo(7)
g.adiciona_aresta(0, 1, 4)
g.adiciona_aresta(0, 2, 2)
g.adiciona_aresta(1, 2, 1)
g.adiciona_aresta(1, 3, 1)
g.adiciona_aresta(2, 3, 3)
g.adiciona_aresta(2, 4, 3)
g.adiciona_aresta(3, 4, 1)
g.adiciona_aresta(3, 5, 5)
g.adiciona_aresta(5, 4, 2)
g.adiciona_aresta(4, 6, 4)
g.adiciona_aresta(5, 6, 1)
print(g.adjs.items())
# print(g.adjs[2])

inicio = 0
print(f"Distância do vértice {inicio} para todos os outros: \n{g.dijkstra(inicio)}")
