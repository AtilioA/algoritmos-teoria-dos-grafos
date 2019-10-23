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
        # print(v, end=' ')

        # Recursão com os vértices adjacentes ao de entrada
        for i in self.grafo[v]:
            if self.visitado[i] is False:
                self.busca(i)

    def percorre_adiciona_pilha(self, v, pilhaDeVertices):
        # Marca o vértice de entrada como visitado
        self.visitado[v] = True

        # Recursão com os vértices adjacentes ao de entrada
        for i in self.grafo[v]:
            # print(i)
            # print(self.visitado)
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

        nComponentesFConexas = 0
        # Printar vértices do da pilha de busca do grafo reverso
        while pilhaDeVertices:
            i = pilhaDeVertices.pop()
            if grafoReverso.visitado[i] is False:
                # print(f"Componente nº {nComponentesFConexas}:")
                grafoReverso.busca(i)
                # print("\n")
                nComponentesFConexas += 1
        return nComponentesFConexas


if __name__ == "__main__":
    while True:
        entrada = input().strip().split(' ')
        N = int(entrada[0])
        M = int(entrada[1])
        # print(f"N = {N}, M = {M}")
        if N == 0 and M == 0:
            break

        g = Grafo(N)

        for vertice in range(M):
            entradaArestas = input().strip().split(' ')
            V = int(entradaArestas[0]) - 1
            W = int(entradaArestas[1]) - 1
            P = int(entradaArestas[2])
            # print(f"V = {V}, W = {W}, P = {P}\n")

            if P == 1:
                g.adiciona_aresta(V, W)
            elif P == 2:
                g.adiciona_aresta(V, W)
                g.adiciona_aresta(W, V)

        nComponentesFConexas = g.componentes_f_conexas()
        # print(f"Número de componentes f-conexas: {nComponentesFConexas}\n\n")
        if nComponentesFConexas != 1:
            print(0)
        else:
            print(1)
