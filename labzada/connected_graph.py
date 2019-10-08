class Vertice(object):
    def __init__(self, rotulo):
        self.rotulo = rotulo
        self.visitado = False

class Grafo(object):
    def __init__(self):
        self.vertices = set()
        self.vertice_mark = []
        self.arestas = set()

    def adicionar_vertice(self, vertice):
        self.vertices.add(vertice)

    def adicionar_mark(self, vertice):
        self.vertice_mark.append([vertice, 0])

    def ligar(self, vertices):
        self.arestas.add(vertices)
        self.arestas.add((vertices[1], vertices[0]))


def busca_util(vertice, grafo):
    vertice.visitado = True
    lista = []
    lista.append(vertice.rotulo)
    for i in grafo.vertices:
        if vertice.rotulo == i.rotulo:
            i.visitado = True

    for i in grafo.arestas:
        if vertice.rotulo == i[0]:
            for j in grafo.vertices:
                if i[1] == j.rotulo and j.visitado is True:
                    lista = lista + busca_util(j, grafo)
    # print(lista)
    return lista


def busca_prof(grafo):
    componentes = 0
    for vertice in grafo.vertices:
        vertice.visitado = False
    for vertice in grafo.vertices:
        if vertice.visitado is False:
            componentes += 1
            vertices = busca_util(vertice, grafo)
            # print(vertices)
            vertices.sort()
            # print(vertices)
            for i in vertices:
                print(str(i), end=",")
            print("")
    return componentes

if __name__ == "__main__":
    N = int(input())
    for i in range(N):
        entrada = input().split(' ')
        v = int(entrada[0])
        e = int(entrada[1])
        G = Grafo()
        for j in range(v):
            G.adicionar_vertice(Vertice([chr(k) for k in range(ord('a'), ord('z') + 1)][j]))
        for j in range(e):
            entradaVertices = input().split(' ')
            v1 = entradaVertices[0]
            v2 = entradaVertices[1]
            # print(f"v1: {v1}, v2: {v2}")
            G.ligar((v1, v2))
            # print(G.arestas)

        print("Case #{}:".format(i + 1))
        componentes = busca_prof(G)
        print("{} connected components".format(componentes))
        print("")
