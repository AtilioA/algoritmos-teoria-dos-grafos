#include <iostream>
#include <vector>
#include <limits>
#include <sstream>
#include <algorithm>

using namespace std;

bool esta_em(vector<int> vetor, int elemento)
{
    for (int k : vetor)
    {
        if (elemento == k)
        {
            return true;
        }
    }
    return false;
}
class Grafo
{
    private:
        vector<vector<pair<int, int>>> adj;
        int nVertices;
        int peso;

    public:
        Grafo(int nVertices)
        {
            for (int i = 0; i < nVertices; i++)
            {
                vector<pair<int, int>> k;
                this->adj.push_back(k);
            }
            this->peso = 0;
            this->nVertices = nVertices;
        };

        void imprime_vertices()
        {
            int count = 0;
            for (vector<pair<int, int>> i : this->adj)
            {
                cout << count << ": ";
                for (pair<int, int> j : i)
                {
                    cout << "(" << j.first << "," << j.second << ") ";
                }
                count++;
                cout << "\n";
            }
        }

        int getPeso(int u, int v)
        {
            int peso = numeric_limits<int>::max();
            for (pair<int, int> arestas : this->adj[u])
            {
                if (arestas.first == v)
                {
                    peso = arestas.second;
                    break;
                }
            }
            return peso;
        };

        // Grafo não direcionado
        void adiciona_aresta(int u, int v, int peso)
        {
            pair<int, int> ida = make_pair(u, peso);
            pair<int, int> volta = make_pair(v, peso);

            this->adj[v].push_back(ida);
            this->adj[u].push_back(volta);

            this->peso += peso;
        }

        int prim()
        {
            int peso = 0;

            vector<int> Vl;
            Vl.push_back(0);

            vector<int> L;
            vector<int> V;
            vector<int> diff;

            // Inicializa vetores do algoritmo
            for (int i = 0; i < this->nVertices; i++)
            {
                V.push_back(i);
            }
            for (int i = 0; i < this->nVertices; i++)
            {
                L.push_back(numeric_limits<int>::max());
            }
            for (pair<int, int> k : this->adj[0])
            {
                L[k.first] = k.second;
            }

            set_difference(V.begin(), V.end(), Vl.begin(), Vl.end(), inserter(diff, diff.end()));
            while (!diff.empty())
            {
                vector<int> pesosDiff;
                for (int i : diff)
                {
                    pesosDiff.push_back(L[i]);
                }

                int minPeso = *min_element(pesosDiff.begin(), pesosDiff.end());
                int w = 0;
                for (int i = 0; i < L.size(); i++)
                {
                    if (L[i] == minPeso && esta_em(diff, i))
                    {
                        w = i;
                        break;
                    }
                }

                int u = Vl[0];
                for (pair<int, int> ar : this->adj[w])
                {
                    if (ar.second < this->getPeso(u, w) && esta_em(Vl, ar.first))
                    {
                        u = ar.first;
                    }
                }

                peso += this->getPeso(u, w);
                Vl.push_back(w);


                for (int v : diff)
                {
                    int p = this->getPeso(v, w);
                    if (p < L[v])
                    {
                        L[v] = p;
                    }
                }

                // Para uma nova iteração
                sort(Vl.begin(), Vl.end());
                diff.clear();
                set_difference(V.begin(), V.end(), Vl.begin(), Vl.end(), inserter(diff, diff.end()));
            }

            return peso;
    };
};

int main()
{
    int n;
    int m;
    int u;
    int v;
    int p;

    cin >> n;
    cin >> m;

    Grafo *g = new Grafo(n);

    for (int i = 0; i < m; i++)
    {
        cin >> u;
        cin >> v;
        cin >> p;

        g->adiciona_aresta(u - 1, v - 1, p);
    }

    cout << g->prim() << endl;

    delete g;
    return 0;
}
