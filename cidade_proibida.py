from collections import defaultdict


class Grafo:
    def __init__(self, nVertices):
        # default dictionary para armazenar o grafo
        self.adjs = defaultdict(list)
        self.nVertices = nVertices
        # <<Conjuntos>> para Dijkstra
        self.aberto = [True] * nVertices

    def adiciona_aresta(self, u, v, peso):
        self.adjs[u].append((v, peso))
        self.adjs[v].append((u, peso))

    def dijkstra_proibido(self, inicio, proibido):
        distV = [float("inf")] * self.nVertices
        distV[inicio] = 0

        self.aberto[proibido] = False
        while True in self.aberto:
            indiceMenor = self.aberto.index(True)
            for dist in distV:
                if self.aberto[distV.index(dist)] and dist < distV[indiceMenor]:
                    indiceMenor = distV.index(dist)
            self.aberto[indiceMenor] = False

            vizinhos = [x for x in self.adjs[indiceMenor] if self.aberto[x[0]]]
            for vizinho in vizinhos:
                custo = min(distV[vizinho[0]], distV[indiceMenor] + vizinho[1])
                distV[vizinho[0]] = custo

        return distV

if __name__ == "__main__":
    while True:
        try:
            entrada = input().strip().split(' ')
            N = int(entrada[0])
            M = int(entrada[1])
        except EOFError:
            break

        g = Grafo(N)

        for vertice in range(M):
            entradaArestas = input().strip().split(' ')
            # Subtraindo 1 pois vértices do grafo começam do 0
            V = int(entradaArestas[0]) - 1
            W = int(entradaArestas[1]) - 1
            g.adiciona_aresta(V, W, 1)

        entradaCidades = input().strip().split(' ')
        C = int(entradaCidades[0]) - 1
        R = int(entradaCidades[1]) - 1
        E = int(entradaCidades[2]) - 1

        # print(g.adjs.items())
        dists = g.dijkstra_proibido(C, E)
        distR = dists[R]
        print(distR)
