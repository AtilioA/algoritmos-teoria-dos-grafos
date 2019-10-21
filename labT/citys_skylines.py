import math

class Grafo(object):
    def __init__(self):
        self.vertices = set()
        self.arestas = set()
        self.matriz = []
        self.matriz_custo = []

    def adicionar_vertice(self, vertice):
        self.vertices.add(vertice)
        self.matriz.append([])
        self.matriz_custo.append([])

    def autom_vertices(self, n):
        self.vertices = set(range(n))
        for i in self.vertices:
            self.matriz.append([])
            self.matriz_custo.append([])

    def ligar(self, vertices, custo):
        self.arestas.add((vertices, custo))
        self.arestas.add(((vertices[1], vertices[0]),custo))
        self.matriz[vertices[0]].append(vertices[1])
        self.matriz[vertices[1]].append(vertices[0])
        self.matriz_custo[vertices[0]].append((vertices[1], custo))
        self.matriz_custo[vertices[1]].append((vertices[0], custo))

    def vizinhos(self, vertice):
        return set([x[0][1] for x in list(self.arestas) if x[0][0] == vertice])

    def custo_entre(self, u, v):
        for i in self.arestas:
            if u == i[0][0] and v == i[0][1]:
                return i[1]
        return 0
        

def nequal(a, b):
    if a == b:
        return 0
    else:
        return float("inf")

def min(a, b):
    if a < b:
        return a
    else:
        return b

# def dijkstra(grafo, inicio):
#     vin = inicio
#     distancias = [[x, nequal(inicio, x)] for x in grafo.vertices]
#     fechado = set()
#     aberto = grafo.vertices
#     anterior = [[x, 0] for x in grafo.vertices]
#     while aberto != set():
#         k = list(distancias)[0]
#         for i in distancias:
#             if k[0] not in aberto:
#                 k = i
#             if k[1] > i[1] and i[0] in aberto:
#                 k = i
#         fechado = fechado | set([k[0]])
#         aberto = aberto - set([k[0]])
#         vizinhosK = grafo.vizinhos(k[0])
#         for i in vizinhosK:
#             if i in aberto:
#                 custo = min(distancias[i][1], distancias[k[0]][1] + grafo.custo_entre(k[0], i))
#                 if custo < distancias[i][1]:
#                     distancias[i][1] = custo
#                     anterior[i] = k[0]

#     return distancias

def custo_ate(grafo, inicio, qtdRota):
    vin = inicio
    distancias = [[x, nequal(inicio, x)] for x in grafo.vertices]
    fechado = set()
    aberto = grafo.vertices
    while aberto != set():
        k = distancias[0]
        for i in distancias:
            if k[0] not in aberto:
                k = i
            if k[1] > i[1] and i[0] in aberto:
                k = i
        fechado = fechado | set([k[0]])
        aberto = aberto - set([k[0]])
        if k[0] < qtdRota:
            vizinhosK = [k[0] + 1]
        else:
            vizinhosK = grafo.matriz[k[0]]
        for i in (set(vizinhosK) & aberto):
            custo = min(distancias[i][1], distancias[k[0]][1] + grafo.teste_custo(k[0], i))
            if custo < distancias[i][1]:
                distancias[i][1] = custo

    return distancias

H = Grafo()

H.autom_vertices(6)
H.ligar((0, 1), 10)
H.ligar((0, 2), 5)
H.ligar((2, 1), 4)
H.ligar((2, 4), 6)
H.ligar((4, 3), 2)
H.ligar((3, 1), 1)
H.ligar((3, 5), 3)
H.ligar((1, 4), 4)
H.ligar((4, 5), 1)

if __name__ == "__main__":
    n = 1
    m = 1
    c = 1
    k = 1
    while n != 0 or m != 0 or c != 0 or k != 0:
        entrada = input().split(' ')
        n = int(entrada[0])
        m = int(entrada[1])
        c = int(entrada[2])
        k = int(entrada[3])
        if n == 0 and m == 0 and c == 0 and k == 0:
            break
        Rota = Grafo()
        Rota.autom_vertices(n)
        for i in range(m):
            arestas = input().split(' ')
            u = int(arestas[0])
            v = int(arestas[1])
            custo = int(arestas[2])
            Rota.ligar((u, v), custo)
        print(str(custo_ate(Rota, k, c)[c-1][1]))
        #print(str(Rota.matriz_custo))
