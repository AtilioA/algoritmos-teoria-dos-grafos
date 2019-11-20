class Edge(object):
    def __init__(self, u, v, w):
        self.source = u
        self.target = v
        self.capacity = w

    # "How" an Edge object is to be printed
    def __repr__(self):
        return f"Capacity from {self.source} to {self.target}: {self.capacity}"


class FlowNetwork(object):
    def __init__(self):
        self.adj = {}
        self.flow = {}

    def add_vertex(self, vertex):
        self.adj[vertex] = []

    def get_edges(self, v):
        return self.adj[v]

    def add_edge(self, u, v, w=0):
        if u == v:
            # Graph must be simple
            raise ValueError("u == v")
        edge = Edge(u, v, w)
        reverseEdge = Edge(v, u, 0)

        edge.reverseEdge = reverseEdge
        reverseEdge.reverseEdge = edge

        self.adj[u].append(edge)
        self.adj[v].append(reverseEdge)

        # Initialize all flows to zero
        self.flow[edge] = 0
        self.flow[reverseEdge] = 0

    def find_path(self, source, target, path):
        if source == target:
            return path

        # BFS
        for edge in self.get_edges(source):
            residual = edge.capacity - self.flow[edge]
            if residual > 0 and not (edge, residual) in path:
                result = self.find_path(
                    edge.target, target, path + [(edge, residual)])
                if result != None:
                    return result

    def max_flow(self, source, target):
        path = self.find_path(source, target, [])
        print(f'Path after enter max_flow: {path}')
        for key in self.flow:
            print(f'{key}:{self.flow[key]}')
        print('-' * 20)

        while path != None:
            flow = min(res for edge, res in path)
            for edge, _ in path:
                self.flow[edge] += flow
                self.flow[edge.reverseEdge] -= flow
            for key in self.flow:
                print(f'{key}:{self.flow[key]}')
            path = self.find_path(source, target, [])
            print(f'Path inside of while loop: {path}\n')

        for key in self.flow:
            print(f'{key}:{self.flow[key]}')

        return sum(self.flow[edge] for edge in self.get_edges(source))


if __name__ == "__main__":
    g = FlowNetwork()
    g.add_vertex('0')
    g.add_vertex('1')
    g.add_vertex('2')
    g.add_vertex('3')
    g.add_vertex('4')
    g.add_vertex('5')

    g.add_edge('0', '1', 16)
    g.add_edge('0', '2', 13)
    g.add_edge('1', '2', 10)
    g.add_edge('1', '3', 12)
    g.add_edge('2', '1', 4)
    g.add_edge('2', '4', 14)
    g.add_edge('3', '2', 9)
    g.add_edge('3', '5', 20)
    g.add_edge('4', '3', 7)
    g.add_edge('4', '5', 4)
    # g.add_vertex('s')
    # g.add_vertex('o')
    # g.add_vertex('p')
    # g.add_vertex('r')
    # g.add_vertex('t')
    # g.add_vertex('q')

    # g.add_edge('s', 'o', 5)
    # g.add_edge('s', 'p', 3)
    # g.add_edge('o', 'p', 2)
    # g.add_edge('o', 'q', 3)
    # g.add_edge('p', 'r', 4)
    # g.add_edge('r', 't', 3)
    # g.add_edge('q', 'r', 4)
    # g.add_edge('q', 't', 2)

    maxFlow = g.max_flow('0', '5')
    print(f"Maximum flow: {maxFlow}")
