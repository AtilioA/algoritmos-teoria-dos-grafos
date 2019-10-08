class CONST(object):
    __slots__ = ()
    ALFABETO = [chr(k) for k in range(ord('a'), ord('z') + 1)]


class Vertice(object):
    def __init__(self, rotulo):
        self.rotulo = rotulo
        self.visitado = False
    #     self.adj = []

    # def adiciona_aresta(self, v):
    #     self.adj.append(v)


class Grafo(object):
    def __init__(self, nVertices):
        self.nVertices = nVertices
        self.vertices = set()
        self.arestas = set()

    def adicionar_vertice(self, vertice):
        self.vertices.add(vertice)

    def ligar(self, u, v):
        self.arestas.add((u, v))
        self.arestas.add((v, u))


def busca_util(vertice, grafo):
    vertice.visitado = True
    rotulos = []
    rotulos.append(vertice.rotulo)
    for elemento in grafo.vertices:
        if vertice.rotulo == elemento.rotulo:
            elemento.visitado = True

    for conexao in grafo.arestas:
        if vertice.rotulo == conexao[0]:
            for j in grafo.vertices:
                if conexao[1] == j.rotulo and j.visitado is False:
                    rotulos = rotulos + busca_util(j, grafo)
    return rotulos


def busca_prof(grafo):
    componentes = 0
    for vertice in grafo.vertices:
        vertice.visitado = False
    for vertice in grafo.vertices:
        if vertice.visitado is False:
            componentes += 1
            rotulosVertices = busca_util(vertice, grafo)
            rotulosVertices.sort()
            for rotulo in rotulosVertices:
                print(rotulo, end=",")
            print("")
    return componentes

CONST = CONST()
if __name__ == "__main__":
    nGrafos = int(input())
    for i in range(nGrafos):
        entrada = input().strip().split(' ')
        v = int(entrada[0])
        e = int(entrada[1])
        G = Grafo(nGrafos)
        vertices = []
        for j in range(v):
            G.adicionar_vertice(Vertice(CONST.ALFABETO[j]))
        for j in range(e):
            entradaVertices = input().strip().split(' ')
            v1 = entradaVertices[0]
            v2 = entradaVertices[1]
            G.ligar(v1, v2)

        print("Case #{}:".format(i + 1))
        componentes = busca_prof(G)
        print("{0} connected components".format(componentes))
        print("")
