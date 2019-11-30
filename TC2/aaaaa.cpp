#include <iostream>
#include <vector>
#include <limits>
#include <sstream>
#include <math.h>

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
        vector<vector<pair<int, pair<int, int> > > > adj;
        int nVertices;
        vector<bool> aberto;

    public:
        Grafo(int nVertices)
        {
            // Inicializa vértices do grafo e "conjunto" (vetor) aberto
            for (int i = 0; i < nVertices; i++)
            {
                vector<pair<int, pair<int, int> > > k;
                this->aberto.push_back(true);
                this->adj.push_back(k);
            }
            this->nVertices = nVertices;
        };

        void adiciona_aresta(int u, int v, int peso)
        {   
            int val = 0;
            pair<int, int> pesoFlow = make_pair(peso, val);
            pair<int, pair<int, int> > ida = make_pair(u, pesoFlow);
            pair<int, pair<int, int> > volta = make_pair(v, pesoFlow);
            


            this->adj[v].push_back(ida);
            this->adj[u].push_back(volta);
        }
        
        void flowGeral(int f){
            for(vector<pair<int, pair<int, int> > > adjs : this->adj){
                for(pair<int, pair<int, int> > adj : adjs){
                    adj.second.second = f;
                }
            }
        }

        int precoViagem(int qtdAmigos, int qtdVagas){
            vector<int> dists;
            dists = this->DJ_Kastra(0).first;
            int preco = 0;
            int amg = qtdAmigos;
            int foram = 0;
            while(dists[this->nVertices - 1] < numeric_limits<int>::max() && amg > 0){
                amg -= qtdVagas;
                if(amg < 0){
                    preco += abs(amg)*dists[this->nVertices - 1];
                }else if (qtdVagas <= qtdAmigos){
                    preco += qtdVagas*dists[this->nVertices - 1];
                } else {
                    preco += qtdAmigos*dists[this->nVertices - 1];
                }
                dists = this->DJ_Kastra(0).first;
            }
            return preco;
        };

        void retirar_aresta(int u, int v){
            for(vector<pair<int, pair<int, int> > >::iterator i = this->adj[u].begin(); i != this->adj[u].end(); i++){
                if((*i).first == v){
                    this->adj[u].erase(i);
                    break;
                }
            }
            for(vector<pair<int, pair<int, int> > >::iterator i = this->adj[v].begin(); i != this->adj[v].end(); i++){
                if((*i).first == u){
                    this->adj[v].erase(i);
                    break;
                }
            }

        }

        pair<vector<int>, vector<int> > DJ_Kastra(int inicio)
        {
            vector<int> dists;
            vector<int> anterior(this->nVertices, 0);
            anterior[inicio] = -1;
            
            // Inicializa vetor de distâncias com valores infinitos e 0 para vértice de ínicio
            for (int i = 0; i < this->nVertices; i++)
            {
                dists.push_back(numeric_limits<int>::max());
            }
            dists[inicio] = 0;

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

                vector<pair<int, pair<int, int> > > vizinhos = this->adj[indiceMenor];
                for (pair<int, pair<int, int> > vizinho : vizinhos)
                {
                    if (this->aberto[vizinho.first])
                    {
                        int custo = min(dists[vizinho.first], sum_inf(dists[indiceMenor], vizinho.second.first));
                        dists[vizinho.first] = custo;
                        anterior[vizinho.first] = indiceMenor;
                    }
                }
            }
            int ant = anterior[this->nVertices - 1];
            int at = this->nVertices - 1;
            while(ant != -1){
                this->retirar_aresta(ant, at);
                at = ant;
                ant = anterior[ant];
            }
            for(int i = 0; i < this->aberto.size(); i++){
                this->aberto[i] = true;
            }
            return make_pair(dists, anterior);
        }
};


int main()
{
    int i = 0;

    int n;
    int m;
    int a;
    int b;
    int c;

    float d;
    float k;
    float nVoos = 0;

    int instancia = 0;

    string teste;
    string teste2;

    // while (true)
    // {
        cin >> n;
        cin >> m;

        Grafo *g = new Grafo(n);

        for (int i = 0; i < m; i++)
        {
            cin >> a;
            cin >> b;
            cin >> c;

            g->adiciona_aresta(a - 1, b - 1, c);
        }

        cin >> d;
        cin >> k;
        g->flowGeral(k);
        instancia++;

        cout << "Instancia " << instancia << "\n";
        cout << g->precoViagem(d, k) << "\n";
        cout << "\n";
    // }

    // delete g;
    return 0;
}