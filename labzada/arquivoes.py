import sys
import string
# from connected_graph import conex

def carrega_entrada(nomeArquivo):
    with open(nomeArquivo, "r") as file:
        data = file.read()
    return data


if __name__ == "__main__":
    nomeArquivo = f"{sys.argv[1]}"
    print(f"Arquivo de entrada: {nomeArquivo}")
    dados = carrega_entrada(nomeArquivo)
    N = int(dados[0])
    
    for case in list(range(N)):
        print(f"Case #{case + 1}:")
        # conex(...)
    

    
    
