# https://www.geeksforgeeks.org/strongly-connected-components/
# Kosaraju's algorithm

from collections import defaultdict


# Grafo direcionado com lista de adjacências
class Grafo:
    def __init__(self, nVertices):
        # default dictionary para armazenar o grafo
        self.grafo = defaultdict(list)
        self.nVertices = nVertices
        self.visitado = [False] * (self.nVertices)
        # Inicializa listas de adjacências dos vértices
        for i in range(nVertices):
            self.grafo[i] = []

    def adiciona_aresta(self, u, v):
        # O vértice u possui aresta incidindo exteriormente para v
        self.grafo[u].append(v)

    def busca(self, v):
        # Marca o vértice de entrada como visitado
        self.visitado[v] = True
        print(v, end=' ')

        # Recursão com os vértices adjacentes ao de entrada
        for i in self.grafo[v]:
            if self.visitado[i] is False:
                self.busca(i)

    def percorre_adiciona_pilha(self, v, pilhaDeVertices):
        # Marca o vértice de entrada como visitado
        self.visitado[v] = True

        # Recursão com os vértices adjacentes ao de entrada
        for i in self.grafo[v]:
            if self.visitado[i] is False:
                self.percorre_adiciona_pilha(i, pilhaDeVertices)

        # Adiciona o vértice visitado à pilha
        pilhaDeVertices = pilhaDeVertices.append(v)

    # Para obter o grafo reverso (transposta da matriz de adjacências)
    def cria_grafo_reverso(self):
        gReverso = Grafo(self.nVertices)

        # Para cada aresta incidente exteriormente do grafo original,
        # Tomá-la como incidente internamente
        for vertice in self.grafo:
            for adjacente in self.grafo[vertice]:
                gReverso.adiciona_aresta(adjacente, vertice)
        return gReverso

    def componentes_f_conexas(self):
        pilhaDeVertices = list()

        # Coloca vértices na pilha de acordo com a recursão da busca
        for i in range(self.nVertices):
            if self.visitado[i] is False:
                self.percorre_adiciona_pilha(i, pilhaDeVertices)

        # Cria um grafo reverso
        grafoReverso = self.cria_grafo_reverso()

        nComponentes = 1
        # Printar vértices do da pilha de busca do grafo reverso
        while pilhaDeVertices:
            i = pilhaDeVertices.pop()
            if grafoReverso.visitado[i] is False:
                print(f"Componente nº {nComponentes}:")
                grafoReverso.busca(i)
                print("\n")
                nComponentes += 1


g = Grafo(5)
g.adiciona_aresta(1, 0)
g.adiciona_aresta(0, 2)
g.adiciona_aresta(2, 1)
g.adiciona_aresta(0, 3)
g.adiciona_aresta(3, 4)


print("As seguintes componentes são f-conexas:")
g.componentes_f_conexas()
