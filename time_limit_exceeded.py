import timeit

inicio = 0
nVertices = 1000

start = timeit.default_timer()

distV = [float("inf")] * nVertices
distV[inicio] = 0

stop = timeit.default_timer()

print(f'Time: {stop - start:.50f}')
