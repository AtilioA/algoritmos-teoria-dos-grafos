from collections import defaultdict

class Grafo:
    def __init__(self, nVertices):
        self.adjs = defaultdict(list)
        self.nVertices = nVertices
        self.peso = 0
        # Inicializa todos os vértices acessando o defaultdict
        for vertice in range(nVertices):
            self.adjs[vertice]

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
        Vl = {0}
        L = [float("inf")] * self.nVertices
        V = set(range(self.nVertices))

        for v in self.adjs[0]:
            L[v[0]] = v[1]

        while V - Vl:
            w = L.index(min([L[x] for x in (V - Vl)]))
            wAdjs = [x for x in self.adjs[w] if x[0] in Vl]
            pesos = list(map(lambda x: x[1], wAdjs))
            menorPeso = min(pesos)
            indiceMenor = pesos.index(menorPeso)
            u = wAdjs[indiceMenor][0]
            T.adiciona_aresta(u, w , self.getPeso(u, w))
            Vl = Vl | set({w})
            L[w] = float("inf")
            for v in (V - Vl):
                if self.getPeso(v, w) < L[v]:
                    L[v] = self.getPeso(v, w)

        return T


if __name__ == "__main__":
    entrada1 = input().strip().split(' ')
    n = int(entrada1[0])
    m = int(entrada1[1])
    g = Grafo(n)
    for i in range(m):
        entradaArestas = input().strip().split(' ')
        # Subtraindo 1 pois vértices do grafo começam do 0
        V = int(entradaArestas[0]) - 1
        W = int(entradaArestas[1]) - 1
        g.adiciona_aresta(V, W, int(entradaArestas[2]))
    t = g.prim()
    print(t.peso)