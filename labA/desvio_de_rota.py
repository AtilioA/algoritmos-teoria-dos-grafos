import math

class Vertice:
    def __init__(self, rotulo):
        self.rotulo = rotulo
        self.adjPesos = list()


class Grafo:
    def adicionar_vertice(self, v):
        novo = Vertice(v)
        self.vertices.append(novo)

    def __init__(self, nVertices):
        self.vertices = list()
        self.arestas = list()
        self.matriz = list()
        self.matriz_custo = list()

        for i in range(nVertices):
            self.adicionar_vertice(i)

    def ligar_vertices(self, u, v, peso):
        self.vertices[u].adjPesos.append((v, peso))
        self.vertices[v].adjPesos.append((u, peso))

    def vizinhos(self, vertice):
        return self.vertices[vertice].adjPesos

    def custo_entre(self, k, i):
        for j in self.vertices[k].adjPesos:
            if j[0] == i:
                return j[1]

def infnite(vertice1, vertice2):
    if vertice1 == vertice2:
        return 0
    else:
        return float('inf')


def dj_kastra(grafo, inicio, qtdCidades):
    distancias = [[x, infnite(inicio, x.rotulo)] for x in grafo.vertices]
    aberto = set(grafo.vertices.copy())
    fechado = set()

    while aberto != set():
        k = distancias[0]
        for i in distancias:
            if k[0] not in aberto:
                k = i
            if k[1] > i[1] and i[0] in aberto:
                k = i
        fechado = fechado | set([k[0]])
        aberto = aberto - set([k[0]])
        vizinhosK = grafo.vizinhos(k[0].rotulo)
        vizinho_sem_peso = [x[0] for x in vizinhosK]
        for i in aberto:
            if i.rotulo in vizinho_sem_peso:
                custo = min(distancias[i.rotulo][1], distancias[k[0].rotulo][1] + grafo.custo_entre(k[0].rotulo, i.rotulo))
                if custo < distancias[i.rotulo][1]:
                    distancias[i.rotulo][1] = custo
    return distancias


if __name__ == "__main__":
    G = Grafo(6)
    G.ligar_vertices(0, 1, 10)
    G.ligar_vertices(0, 2, 5)
    G.ligar_vertices(1, 4, 4)
    G.ligar_vertices(1, 3, 1)
    G.ligar_vertices(2, 4, 6)
    G.ligar_vertices(2, 1, 4)
    G.ligar_vertices(3, 5, 3)
    G.ligar_vertices(3, 4, 2)
    G.ligar_vertices(4, 5, 1)
    # for i in G.vizinhos(1):
    #     print(i[0])
    # print(G.vizinhos(0))
    # print(dj)
    for i in dj_kastra(G, 0, 5):
        print(i[1])

    pass
