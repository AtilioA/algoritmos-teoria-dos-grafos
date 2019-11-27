from collections import defaultdict

class Grafo:
    def __init__(self, nVertices):
        self.adjs = defaultdict(list)
        self.nVertices = nVertices
        self.peso = 0
        # Inicializa todos os vértices
        for vertice in range(nVertices):
            self.adjs[vertice] = []
        # <<Conjuntos>> para Dijkstra
        self.fechado = [False] * nVertices
        self.aberto = [True] * nVertices

    def adiciona_aresta(self, u, v, peso):
        self.peso += peso
        self.adjs[u].append((v, peso))
        self.adjs[v].append((u, peso))

    def getPeso(self, u, v):
        peso = float("inf")
        for i in self.adjs[u]:
            if i[0] == v:
                peso = i[1]
                break
        return peso

    def prim(self):
        T = Grafo(self.nVertices)
        Vl = set({0})
        L = [float("inf")] * self.nVertices
        V = set(range(self.nVertices))
        for v in self.adjs[0]:
            L[v[0]] = v[1]
        while bool(V - Vl):
            w = L.index(min([L[x] for x in (V - Vl)]))
            wAdjs = [x for x in self.adjs[w] if x[0] in Vl] 
            pesos = list(map(lambda x: x[1], wAdjs))
            menorPeso = min(pesos)
            indiceMenor = pesos.index(menorPeso)
            u = wAdjs[indiceMenor][0]
            T.adiciona_aresta(u, w , self.getPeso(u, w))
            Vl = Vl | set({w})
            for v in (V - Vl):
                if self.getPeso(v, w) < L[v]:
                    L[v] = self.getPeso(v, w)
        return T


if __name__ == "__main__":
    G = Grafo(4)
    G.adiciona_aresta(0, 1, 2)
    G.adiciona_aresta(0, 3, -10)
    G.adiciona_aresta(0, 2, 3)
    G.adiciona_aresta(1, 2, 5)
    G.adiciona_aresta(1, 3, 0)
    G.adiciona_aresta(2, 3, 4)
    print(G.adjs.items())
    T = G.prim()
    print(T.adjs.items())
    print(T.peso)