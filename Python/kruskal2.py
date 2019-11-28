from collections import defaultdict


def tupla2(tupla):
    return tupla[1]


# Grafo não direcionado com lista de adjacências
class Grafo:
    def __init__(self, nVertices):
        # default dictionary para armazenar o grafo
        self.adjs = defaultdict(list)
        self.nVertices = nVertices
        # self.nArestas = 0
        self.visitado = [False] * (self.nVertices)
        # Inicializa listas de adjacências dos vértices
        for i in range(nVertices):
            self.adjs[i] = []

    def adiciona_aresta(self, u, v, p):
        # O vértice u possui aresta incidindo exteriormente para v
        self.adjs[u].append(((u, v), p))
        self.adjs[v].append(((v, u), p))
        # self.nArestas += 1

    def remove_aresta(self, u, v, p):
        # O vértice u possui aresta incidindo exteriormente para v
        self.adjs[u].remove(((u, v), p))
        self.adjs[v].remove(((v, u), p))
        # self.nArestas -= 1

    def busca(self, v):
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

    def tem_ciclo(self, v, anterior):
        # Marca o vértice de entrada como visitado
        self.visitado[v] = True
        # print(f"Vértice atual: {v}.\nVértice anterior: {anterior}\n")
        # print(f"Anterior atualizado: {anterior}\n")

        # print(self.adjs[v])
        # print([x[0][1] for x in self.adjs[v]])

        # Recursão com os vértices adjacentes ao inicial
        for i in [x[0][1] for x in self.adjs[v]]:
            if self.visitado[i] is False and i != anterior:
                anterior = v
                self.tem_ciclo(i, anterior)
            else:
                return True
        return False

    def arestas_pra_lista(self):
        arestas = list()
        for vertice in g.adjs:
            arestas += g.adjs[vertice]
        return arestas

    def kruskal(self):
        arestas = self.arestas_pra_lista()
        arestas.sort(key=tupla2)

        T = Grafo(self.nVertices)

        for aresta in arestas:
            T.adiciona_aresta(aresta[0][0], aresta[0][1], aresta[1])
            if not T.busca(0):
                continue
            else:
                T.remove_aresta(aresta[0][0], aresta[0][1], aresta[1])

        return T


if __name__ == "__main__":
    g = Grafo(4)
    g.adiciona_aresta(0, 1, 0)
    g.adiciona_aresta(0, 2, 1)
    g.adiciona_aresta(1, 3, 2)
    g.adiciona_aresta(3, 0, 9)
    # print(g.adjs)
    # for vertice in g.adjs:
        # print(vertice)
        # print(g.adjs[vertice])

    # print(f'\nG tem ciclo? {g.busca(0)}')
    T = g.kruskal()
    print(dict(T.adjs.items()))
