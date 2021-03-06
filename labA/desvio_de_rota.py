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


def dj_kastra(grafo, cidadeConserto, qtdRota):
    distancias = [[x, infnite(cidadeConserto, x.rotulo)] for x in grafo.vertices]
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
        if k[0].rotulo in range(qtdRota):
            vizinhosK = [x for x in grafo.vizinhos(k[0].rotulo) if x[0] == k[0].rotulo + 1]
        else:
            vizinhosK = grafo.vizinhos(k[0].rotulo)
        vizinho_sem_peso = [x[0] for x in vizinhosK]
        for i in aberto:
            if i.rotulo in vizinho_sem_peso:
                custo = min(distancias[i.rotulo][1], distancias[k[0].rotulo][1] + grafo.custo_entre(k[0].rotulo, i.rotulo))
                if custo < distancias[i.rotulo][1]:
                    distancias[i.rotulo][1] = custo
    return distancias


if __name__ == "__main__":
    n = 1
    m = 1
    c = 1
    k = 1
    while n != 0 or m != 0 or c != 0 or k != 0:
        entrada = input().split(' ')
        n = int(entrada[0])
        m = int(entrada[1])
        c = int(entrada[2])
        k = int(entrada[3])
        if n == 0 and m == 0 and c == 0 and k == 0:
            break
        Rota = Grafo(n)
        for i in range(m):
            arestas = input().split(' ')
            u = int(arestas[0])
            v = int(arestas[1])
            custo = int(arestas[2])
            Rota.ligar_vertices(u, v, custo)
        print(str(dj_kastra(Rota, k, c)[c-1][1]))
        #print(str(Rota.matriz_custo))
