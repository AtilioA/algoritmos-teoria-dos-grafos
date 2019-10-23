from collections import defaultdict
import timeit

adjs = defaultdict(list)
adjs = {0: [1, 2, 4, 5], 1: [4, 3], 2: [0, 1, 5], 3: [1, 4], 4: [1, 3], 5: [2, 0]}
indiceMenor = 3
aberto = [True] * 100

start = timeit.default_timer()

vizinhos = [x for x in adjs[indiceMenor] if aberto[x[0]]]

stop = timeit.default_timer()

print(f'Time: {stop - start:.50f}')
