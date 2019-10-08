class CONST(object):
    __slots__ = ()
    ALFABETO = [chr(k) for k in range(ord('a'), ord('z') + 1)]


class Vertice(object):
    def __init__(self, rotulo):
        self.rotulo = rotulo
        self.visitado = False


class Grafo(object):
    def __init__(self):
        self.vertices = set()
        self.arestas = set()

    def adicionar_vertice(self, vertice):
        self.vertices.add(vertice)

    def ligar(self, vertices):
        self.arestas.add(vertices)
        self.arestas.add((vertices[::-1])) #  reflexivo


def busca_util(vertice, grafo):
    vertice.visitado = True
    rotulos = []
    rotulos.append(vertice.rotulo)
    for elemento in grafo.vertices:
        if vertice.rotulo == elemento.rotulo:
            elemento.visitado = True

    for conexao in sorted(list(grafo.arestas)):
        if vertice.rotulo == conexao[0]:
            for j in grafo.vertices:
                if conexao[1] == j.rotulo and j.visitado is False:
                    rotulos = rotulos + busca_util(j, grafo)

    print(rotulos)
    return sorted(rotulos)


def busca_prof(grafo):
    componentes = 0
    
    for vertice in list(grafo.vertices):
        vertice.visitado = False
    for vertice in list(grafo.vertices):
        if vertice.visitado is False:
            componentes += 1
            rotulosVertices = busca_util(vertice, grafo)
            # print(rotulosVertices)
            # rotulosVertices.sort()
            # print(rotulosVertices)
            for rotulo in rotulosVertices:
                print(rotulo, end=",")
            print("")
    return componentes


CONST = CONST()
if __name__ == "__main__":
    nGrafos = int(input().strip())
    for i in range(nGrafos):
        entrada = input().strip().split(' ')
        v = int(entrada[0])
        e = int(entrada[1])
        G = Grafo()
        vertices = []
        for j in range(v):
            G.adicionar_vertice(Vertice(CONST.ALFABETO[j]))
        for j in range(e):
            entradaVertices = input().strip().split(' ')
            v1 = entradaVertices[0]
            v2 = entradaVertices[1]
            # print(f"v1: {v1}, v2: {v2}")
            G.ligar((v1, v2))

        print("Case #{}:".format(i + 1))
        componentes = busca_prof(G)
        print("{} connected components".format(componentes))
        print("")
