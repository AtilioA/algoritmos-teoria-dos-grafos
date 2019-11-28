import random
import matplotlib.pyplot as plt
import networkx as nx
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

    # Não funciona; apenas para fins de recordação
    def tem_ciclo2(self, v, anterior):
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

        # for vertice in range(self.nVertices):
        #     T.adjs[vertice] = list(dict.fromkeys(T.adjs[vertice]))

        return T


if __name__ == "__main__":
    g = Grafo(4)
    g.adiciona_aresta(0, 1, 2)
    g.adiciona_aresta(0, 3, -10)
    g.adiciona_aresta(0, 2, 3)
    g.adiciona_aresta(1, 2, 5)
    g.adiciona_aresta(1, 3, 0)
    g.adiciona_aresta(2, 3, 4)
    print(f"Grafo:\n{dict(g.adjs)}")
    for vertice in g.adjs:
        print(f"Vizinhos do vértice {vertice}:")
        print(g.adjs[vertice])

    print(f"\nG tem ciclo? {g.tem_ciclo(0)}!\n")
    T = g.kruskal()

    G2 = nx.Graph()
    i = 0
    for vertice, arestas in g.adjs.items():
        print([(vertice, aresta[0][1]) for aresta in arestas])
        G2.add_node(vertice, pos=(random.randint(0, 5),i))
        G2.add_node(vertice, pos=(random.randint(0, 5),i))
        i += 1
        G2.add_weighted_edges_from([(vertice, aresta[0][1], aresta[1]) for aresta in arestas])

    T2 = nx.Graph()
    i = 0
    pos = nx.get_node_attributes(G2,'pos')
    print(pos)
    for vertice, arestas in T.adjs.items():
        print([(vertice, aresta[0][1]) for aresta in arestas])
        print(f"Posicao: {pos[i]}")
        T2.add_node(vertice, pos=(pos[i]))
        T2.add_node(vertice, pos=(random.randint(0, 5),i))
        i += 1
        T2.add_weighted_edges_from([(vertice, aresta[0][1], aresta[1]) for aresta in arestas])


    # nx.draw(T2)
    # nx.draw_random(T2)

    plt.figure(1)
    pos = nx.get_node_attributes(T2,'pos')
    nx.draw(T2, pos)
    labelPesos = nx.get_edge_attributes(T2,'weight')
    nx.draw_networkx_edge_labels(T2, pos, edge_labels=labelPesos)

    plt.figure(2)
    pos = nx.get_node_attributes(G2,'pos')
    nx.draw(G2, pos)
    labelPesos = nx.get_edge_attributes(G2,'weight')
    nx.draw_networkx_edge_labels(G2, pos, edge_labels=labelPesos)


    plt.show()

    print(f"Imprimindo árvore geradora mínima de G, que possui peso {T.peso}:\n{dict(T.adjs.items())}")
