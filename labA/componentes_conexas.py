class CONST(object):
    __slots__ = ()
    ALFABETO = [chr(k) for k in range(ord('a'), ord('z') + 1)]


class Vertice(object):
    def __init__(self, rotulo):
        self.rotulo = rotulo
        self.visitado = False
        self.adj = []

    def adiciona_aresta(self, v):
        self.adj.append(v)


class Grafo(object):
    def __init__(self, nVertices):
        self.nVertices = nVertices
        self.vertices = set()
        self.arestas = set()

    def adicionar_vertice(self, objVertice):
        self.vertices.add(objVertice)

    def ligar(self, u, v):
        self.arestas.add((u, v))
        self.arestas.add((v, u))
        # v.adiciona_aresta(u)


def busca_util(vertice, grafo):
    vertice.visitado = True
    lista = []
    lista.append(vertice.rotulo)
    for elemento in grafo.vertices:
        if vertice.rotulo == elemento.rotulo:
            elemento.visitado = True
            # print("Vertice visitado")

    for conexao in grafo.arestas:
        # print("For busca_util")
        if vertice.rotulo == conexao[0]:
            for j in grafo.vertices:
                # print(f"{conexao[1]} e {j.rotulo}")
                if conexao[1] == j.rotulo and j.visitado is False:
                    lista = lista + busca_util(j, grafo)
    return lista


def busca_prof(grafo):
    componentes = 0
    for vertice in grafo.vertices:
        vertice.visitado = False
        # print()
    for vertice in grafo.vertices:
        if vertice.visitado is False:
            componentes += 1
            vertices = busca_util(vertice, grafo)
            vertices.sort()
            for i in vertices:
                print(str(i), end=",")
            print("")
    return componentes

CONST = CONST()
if __name__ == "__main__":
    print("Main:\n")
    nGrafos = int(input())
    for i in range(nGrafos):
        entrada = input().split(' ')
        v = int(entrada[0])
        e = int(entrada[1])
        # print("Numero de grafos: {}".format(nGrafos))
        # print("Numero de vertices: {}".format(v))
        # print("Numero de arestas: {}".format(e))
        G = Grafo(nGrafos)
        vertices = []
        for j in range(v):
            G.adicionar_vertice(Vertice(CONST.ALFABETO[j]))
        # print(list(G.vertices)[-1].rotulo)
        for j in range(e):
            entradaVertices = input().split(' ')
            v1 = entradaVertices[0]
            v2 = entradaVertices[1]
            # print(f"v1: {v1}, v2: {v2}")
            G.ligar(v1, v2)

        print("Case #{}:".format(i + 1))
        componentes = busca_prof(G)
        print("{0} connected components".format(componentes))
        print("")
