# Abstrai uma aresta, com peso, vértice u (first) e vértice v (second)
class Aresta:
    def __init__(self, peso, first, second):
        self.peso = peso
        self.first = first
        self.second = second
        self.first_count = 0
        self.second_count = 0

    # Define se uma aresta é "menor" que outra (tem menor peso)
    def __lt__(self, outraAresta):
        return self.peso < outraAresta.peso
