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

    def vizinhos(self, vertice):
        return set([x[1] for x in list(self.arestas) if x[0] == vertice])

    def vizinhosC(self, vertices):
        conj = []
        for x in list(vertices):
            conj = conj + list(self.vizinhos(x))
        return set(conj)


def busca_util(vertice, grafo):
    vertice[1] = 1
    lista = []
    lista.append(vertice[0])
    for i in grafo.vertice_mark:
        if vertice[0] == i[0]:
            i[1] = 1

    for i in grafo.arestas:
        if vertice[0] == i[0]:
            for j in grafo.vertice_mark:
                if i[1] == j[0] and j[1] == 0:
                    lista = lista + busca_util(j, grafo)
    return lista


def busca_prof(grafo):
    componentes = 0
    for vertice in grafo.vertice_mark:
        vertice[1] = 0
    for vertice in grafo.vertice_mark:
        if vertice[1] == 0:
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
            G.adicionar_mark([chr(k) for k in range(ord('a'), ord('z') + 1)][j])
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
