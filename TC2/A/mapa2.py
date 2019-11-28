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
            L[w] = float("inf")
            Vl = Vl | set({w})
            for v in (V - Vl):
                if self.getPeso(v, w) < L[v]:
                    L[v] = self.getPeso(v, w)

        return T

if __name__ == "__main__":
    try:
        entradaGrafo = input().strip().split(' ')
        N = int(entradaGrafo[0])
        M = int(entradaGrafo[1])
    except:
        exit(1)

    G = Grafo(N)

    for _ in range(M):
        try:
            entradaArestas = input().strip().split(' ')

            u = int(entradaArestas[0]) - 1
            v = int(entradaArestas[1]) - 1
            peso = int(entradaArestas[2])

            G.adiciona_aresta(u, v, peso)
        except:
            break

    T = G.prim()
    print(T.peso)
