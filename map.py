import timeit

inicio = 0
nVertices = 1000

start = timeit.default_timer()

distV = list(map(lambda x: 0 if x == inicio else float("inf"), range(nVertices)))

stop = timeit.default_timer()

print(f'Time: {stop - start:.50f}')
