# Implementação básica de insertion sort, porém para lista de arestas (ver aresta.py)
def insert_sort(collection, vertices):
    tamanho = len(collection)

    if tamanho < 2:
        # Já está ordenado, retorne
        return collection, vertices

    # Roda para cada aresta da coleção (neste caso, lista)
    for indiceFrente in range(1, tamanho):
        indiceAtras = indiceFrente - 1
        elementoFrente = collection[indiceFrente]

        # Enquanto o peso da aresta detrás for maior que os da frente
        while indiceAtras >= 0 and collection[indiceAtras] > elementoFrente:
            # Colocamos ela pra trás (procedimento padrão do insertion sort)
            collection[indiceAtras + 1] = collection[indiceAtras]
            indiceAtras -= 1

        # Preenche "buraco"
        collection[indiceAtras + 1] = elementoFrente
        # Fim da implementação de insertion sort padrão

        vertices[elementoFrente.first] = 0
        vertices[elementoFrente.second] = 0

    return collection, vertices
