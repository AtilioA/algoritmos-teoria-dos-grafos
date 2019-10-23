import random



c = 1
r = 2
e = 3
with open(f"entrada2py.txt", "w+", encoding="utf8") as file:
    for grafos in range(random.randint(1, 3)):
        N = random.randint(1, 20)
        M = random.randint(5, 10)
        file.write(f"{N} {M}\n")
        for grafo in range(M):
            u = 0
            v = 0
            while u == v:
                u = random.randint(1, 100)
                v = random.randint(1, 100)
            file.write(f"{u} {v}\n")
        file.write(f"{c} {r} {e}\n")
