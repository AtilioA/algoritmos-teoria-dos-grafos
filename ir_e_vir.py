from collections import defaultdict


# Grafo direcionado com lista de adjacências
class Grafo:
    def __init__(self, nVertices):
        # default dictionary para armazenar o grafo
        self.adjs = defaultdict(list)
        self.nVertices = nVertices
        self.visitado = [False] * (self.nVertices)
        # Inicializa listas de adjacências dos vértices
        for i in range(nVertices):
            self.adjs[i] = []

    def adiciona_aresta(self, u, v):
        # O vértice u possui aresta incidindo exteriormente para v
        self.adjs[u].append(v)

    def busca(self, v):
        # Marca o vértice de entrada como visitado
        self.visitado[v] = True

        # Recursão com os vértices adjacentes ao de entrada
        for i in self.adjs[v]:
            if self.visitado[i] is False:
                self.busca(i)

    def percorre_adiciona_pilha(self, v, pilhaDeVertices):
        # Marca o vértice de entrada como visitado
        self.visitado[v] = True

        # Recursão com os vértices adjacentes ao de entrada
        for i in self.adjs[v]:
            if self.visitado[i] is False:
                self.percorre_adiciona_pilha(i, pilhaDeVertices)

        # Adiciona o vértice visitado à pilha
        pilhaDeVertices = pilhaDeVertices.append(v)

    # Para obter o grafo reverso (transposta da matriz de adjacências)
    def cria_grafo_reverso(self):
        gReverso = Grafo(self.nVertices)

        # Para cada aresta incidente exteriormente do grafo original,
        # Tomá-la como incidente internamente
        for vertice in self.adjs:
            for adjacente in self.adjs[vertice]:
                gReverso.adiciona_aresta(adjacente, vertice)
        return gReverso

    def componentes_f_conexas(self):
        pilhaDeVertices = list()

        # Coloca vértices na pilha de acordo com a recursão da busca
        for i in range(self.nVertices):
            if self.visitado[i] is False:
                self.percorre_adiciona_pilha(i, pilhaDeVertices)

        # Cria o grafo reverso
        grafoReverso = self.cria_grafo_reverso()

        nComponentesFConexas = 0
        while pilhaDeVertices:
            i = pilhaDeVertices.pop()
            if grafoReverso.visitado[i] is False:
                grafoReverso.busca(i)
                nComponentesFConexas += 1

        return nComponentesFConexas


if __name__ == "__main__":
    while True:
        entrada = input().strip().split(' ')
        N = int(entrada[0])
        M = int(entrada[1])
        if N == 0 and M == 0:
            break

        g = Grafo(N)

        for vertice in range(M):
            entradaArestas = input().strip().split(' ')
            # Subtraindo 1 pois vértices do grafo começam do 0
            V = int(entradaArestas[0]) - 1
            W = int(entradaArestas[1]) - 1
            P = int(entradaArestas[2])

            if P == 1:
                g.adiciona_aresta(V, W)
            elif P == 2:
                g.adiciona_aresta(V, W)
                g.adiciona_aresta(W, V)

        nComponentesFConexas = g.componentes_f_conexas()
        if nComponentesFConexas != 1:
            print(0)
        else:
            print(1)
        print(g.adjs)
