#include <iostream>
#include <vector>
#include <limits>
#include <sstream>

using namespace std;

// Verificar se um valor está contido em um vetor
bool is_in(vector<bool>::iterator it1, vector<bool>::iterator it2, bool val)
{
    for (vector<bool>::iterator it = it1; it != it2; it++)
    {
        if ((*it) == val)
        {
            return 1;
        }
    }
    return 0;
}

// Template para encontrar índice da primeira ocorrência de um elemento em um vetor
template <typename comparavel>
int index(typename vector<comparavel>::iterator it1, typename vector<comparavel>::iterator it2, comparavel val)
{
    int qtd = 0;
    for (typename vector<comparavel>::iterator it = it1; it != it2; it++)
    {
        if ((*it) == val)
        {
            return qtd;
        }
        qtd++;
    }
    return 0;
}


int sum_inf(int i, int j)
{
    if (j == numeric_limits<int>::max() || i == numeric_limits<int>::max())
    {
        return numeric_limits<int>::max();
    }
    else
    {
        return i + j;
    }
}

class Grafo
{
    private:
        vector<vector<pair<int, int>>> adj;
        int nVertices;
        vector<bool> aberto;

    public:
        Grafo(int nVertices)
        {
            // Inicializa vértices do grafo e "conjunto" (vetor) aberto
            for (int i = 0; i < nVertices; i++)
            {
                vector<pair<int, int>> k;
                this->aberto.push_back(true);
                this->adj.push_back(k);
            }
            this->nVertices = nVertices;
        };

        void adiciona_aresta(int u, int v, int peso)
        {
            pair<int, int> ida = make_pair(u, peso);
            pair<int, int> volta = make_pair(v, peso);

            this->adj[v].push_back(ida);
            this->adj[u].push_back(volta);
        }

        vector<int> DJ_Kastra_proibido(int inicio, int proibido)
        {
            vector<int> dists;

            // Inicializa vetor de distâncias com valores infinitos e 0 para vértice de ínicio
            for (int i = 0; i < this->nVertices; i++)
            {
                dists.push_back(numeric_limits<int>::max());
            }
            dists[inicio] = 0;

            // Remove cidade proibida do "conjunto" (vetor) aberto
            this->aberto[proibido] = false;

            while (is_in(this->aberto.begin(), this->aberto.end(), true))
            {
                int indiceMenor = index<bool>(this->aberto.begin(), this->aberto.end(), true);
                int proximoVertice = 0;
                for (int dist : dists)
                {
                    if (this->aberto[proximoVertice] && dist < dists[indiceMenor])
                    {
                        indiceMenor = proximoVertice;
                    }
                    proximoVertice++;
                }
                this->aberto[indiceMenor] = false;

                vector<pair<int, int>> vizinhos = this->adj[indiceMenor];
                for (pair<int, int> vizinho : vizinhos)
                {
                    if (this->aberto[vizinho.first])
                    {
                        int custo = min(dists[vizinho.first], sum_inf(dists[indiceMenor], vizinho.second));
                        dists[vizinho.first] = custo;
                    }
                }
            }
            return dists;
        }
};

int main()
{
    string entrada;
    int n;
    int m;
    int a;
    int b;
    int c;
    int e;
    int r;

    while (getline(cin, entrada) && !entrada.empty())
    {
        stringstream entrada1(entrada);
        entrada1 >> n;
        entrada1 >> m;

        Grafo *g = new Grafo(n);

        for (int i = 0; i < m; i++)
        {
            getline(cin, entrada);
            stringstream entrada2(entrada);
            entrada2 >> a;
            entrada2 >> b;
            g->adiciona_aresta(a - 1, b - 1, 1); // Todas as rotas têm custo 1
        }

        getline(cin, entrada);

        stringstream entrada3(entrada);
        entrada3 >> c;
        entrada3 >> r;
        entrada3 >> e;

        vector<int> dists = g->DJ_Kastra_proibido(c - 1, e - 1);

        // Pega a distância de C até a cidade R
        cout << dists[r - 1] << '\n';

        entrada.erase();
        delete g;
    }

    return 0;
}
