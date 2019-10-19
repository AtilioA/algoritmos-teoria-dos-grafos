from collections import defaultdict, deque


# Grafo direcionado com lista de adjacências
class Graph:
    def __init__(self):
        # default dictionary para armazenar o grafo
        self.graph = defaultdict(list)

    def adiciona_aresta(self, u, v):
        self.graph[u].append(v)

    # Fazer BFS de um grafo e printar
    def BFS(self, inicio):
        # Marca os vértices como não visitados
        visited = [False] * (len(self.graph) + 1)

        # Cria uma fila para o BFS
        # (deque = Double Ended Queue)
        queue = deque()

        # Marca o vértice de entrada como marcado e enfilera-o
        queue.append(inicio)
        visited[inicio] = True

        # Enquanto a fila tiver vértices
        while queue:
            print(f"Fila atual: {queue}")
            # Desenfilera um vértice e printa
            desenfileirado = queue.popleft()
            print(f"Vértice visitado: {desenfileirado}")

            # Pega os adjacentes ao vértice desenfileirado
            # Se não estiver visitado, marca-o e enfilera-o
            # Nova iteração com a nova fila até que terminem os vizinhos
            for adj in self.graph[desenfileirado]:
                print(f"Adjacentes a {desenfileirado}:")
                print(adj)

                if visited[adj] is False:
                    print(f"{adj} foi marcado e enfileirado.")
                    visited[adj] = True
                    queue.append(adj)
                else:
                    print(f"{adj} já foi marcado.")
            print()


# Cria um grafo e adiciona arestas
g = Graph()

g.adiciona_aresta(0, 1)
g.adiciona_aresta(1, 2)
g.adiciona_aresta(1, 3)
g.adiciona_aresta(2, 3)
g.adiciona_aresta(2, 0)

print(f"\nGrafo: {g.graph.items()}")

s = 0
print(f"\nRealizando busca em amplitude (breadth-first traversal) começando do vértice {s}:\n")
g.BFS(s)
