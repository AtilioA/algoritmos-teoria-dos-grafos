from collections import defaultdict

def tupla2(tupla):
    return tupla[1]


# Grafo não direcionado com lista de adjacências
class Grafo:
    def __init__(self, nVertices):
        # default dictionary para armazenar o grafo
        self.adjs = defaultdict(list)
        self.nVertices = nVertices
        self.peso = 0
        self.visitado = [False] * (self.nVertices)
        # Inicializa listas de adjacências dos vértices
        for i in range(nVertices):
            self.adjs[i] = []

    def adiciona_aresta(self, u, v, peso):
        # O vértice u possui aresta incidindo exteriormente para v
        self.adjs[u].append(((u, v), peso))
        self.adjs[v].append(((v, u), peso))
        self.peso += peso

    def remove_aresta(self, u, v, peso):
        # O vértice u possui aresta incidindo exteriormente para v
        self.adjs[u].remove(((u, v), peso))
        self.adjs[v].remove(((v, u), peso))
        self.peso -= peso

    def tem_ciclo(self, v):
        # Marca o vértice de entrada como visitado
        self.visitado[v] = True
        ciclico = False

        # Recursão com os vértices adjacentes ao de entrada
        for i in self.adjs[v]:
            if self.visitado[i[0][1]] is False:
                ciclico = self.buscaAnterior(i[0][1], v)
            else:
                ciclico = True
        self.visitado = [False] * (self.nVertices)
        return ciclico

    def buscaAnterior(self, v, anterior):
        # Marca o vértice de entrada como visitado
        self.visitado[v] = True
        ciclico = False

        # Recursão com os vértices adjacentes ao de entrada
        for i in self.adjs[v]:
            if self.visitado[i[0][1]] is False:
                ciclico = self.buscaAnterior(i[0][1], v)
            elif anterior == i[0][1]:
                continue
            else:
                ciclico = True
        return ciclico

    def arestas_pra_lista(self):
        arestas = list()
        for vertice in self.adjs:
            arestas += self.adjs[vertice]
        return arestas

    def kruskal(self):
        # print(dict(self.adjs))
        arestas = self.arestas_pra_lista()
        arestas.sort(key=tupla2)

        T = Grafo(self.nVertices)

        for aresta in arestas:
            T.adiciona_aresta(aresta[0][0], aresta[0][1], aresta[1])
            if not T.tem_ciclo(aresta[0][0]):
                continue
            else:
                T.remove_aresta(aresta[0][0], aresta[0][1], aresta[1])

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

    T = G.kruskal()
    print(T.peso)
