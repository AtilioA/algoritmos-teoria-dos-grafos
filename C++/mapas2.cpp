#include <iostream>
#include <vector>
#include <limits>
#include <sstream>
#include <algorithm>
#include <queue>

using namespace std;

bool ordPeso(pair<pair<int, int>, int> i, pair<pair<int, int>, int > j){
    return i.second < j.second;
}

bool encontrar(vector<int> vt, int v){
    for(int k : vt){
        if(k == v){
            return true;
        }
    }
    return false;
};

class Grafo{
    private:
        vector<vector<pair<int, int> > > adj;
        int nVertices;
        int peso;
        vector<bool> aberto;
        vector<pair<pair<int, int>, int > > arestas;
    public:
        int getPesoGrafo(){
            return this->peso;
        }

         Grafo(int nVertices)
        {
            // Inicializa vértices do grafo e "conjunto" (vetor) aberto
            for (int i = 0; i < nVertices; i++)
            {
                vector<pair<int, int> > k;
                this->adj.push_back(k);
                this->aberto.push_back(true);
            }
            this->peso = 0;
            this->nVertices = nVertices;
        };
        
        void printVertices(){
            int count = 0;
            for(vector<pair<int, int> > i : this->adj){
                cout << count << ": ";
                for(pair<int, int> j : i){
                    cout << "(" << j.first << "," << j.second << ") ";
                }
                count++;
                cout << "\n";
            }
        }

        int getPeso(int u, int v){
            int peso = numeric_limits<int>::max();
            for(pair<int, int> i : this->adj[u]){
                if(i.first == v){
                    peso = i.second;
                    break;
                }
            }
            return peso;
        };
        void adiciona_aresta(int u, int v, int peso)
        {
            pair<int, int> ida = make_pair(u, peso);
            pair<int, int> volta = make_pair(v, peso);

            pair<int, int> aresta = make_pair(u, v);
            pair<pair<int, int>, int> arestaPeso = make_pair(aresta, peso);

            this->adj[v].push_back(ida);
            this->adj[u].push_back(volta);
            this->arestas.push_back(arestaPeso);
            this->peso += peso;
        };

        bool temCicloDesconexo(){
            for(int i = 0; i < this->nVertices; i++){
                this->aberto[i] = true;
            }
            for(int i = 0; i < this->nVertices; i++){
                if(this->aberto[i] && this->temCiclo(i)){
                    return true;
                }
            }
            return false;
        }

        bool temCiclo(int ini){
            vector<int> pais;
            for(int i = 0; i < this->nVertices; i++){
                pais.push_back(-1);
            }
            queue<int> fila;
            fila.push(ini);
            while(!fila.empty()){
                this->aberto[fila.front()] = false;
                for(pair<int, int> i : this->adj[fila.front()]){
                    if(this->aberto[i.first]){
                        fila.push(i.first);
                        this->aberto[i.first] = false;
                        pais[i.first] = fila.front();
                    }else if(pais[fila.front()] != i.first){
                        return true;
                    }
                }
                fila.pop();
            }
            return false;
        };
        void retirar_aresta(int u, int v){
            for(vector<pair<int, int>>::iterator i = this->adj[u].begin(); i != this->adj[u].end(); i++){
                if((*i).first == v){
                    this->adj[u].erase(i);
                    break;
                }
            }
            for(vector<pair<int, int>>::iterator i = this->adj[v].begin(); i != this->adj[v].end(); i++){
                if((*i).first == u){
                    this->adj[v].erase(i);
                    this->peso -= (*i).second;
                    break;
                }
            }

        }
        int kruskal(){
            Grafo* T = new Grafo(this->nVertices);
            vector<pair<pair<int, int>, int > > arestas = this->arestas;
            sort(arestas.begin(), arestas.end(), ordPeso);
            int ps = 0;
            for(int i = 0; i < arestas.size(); i++){
                T->adiciona_aresta(arestas[i].first.first, arestas[i].first.second, arestas[i].second);
                if(!T->temCicloDesconexo()){
                    ps += arestas[i].second;
                }else{
                    T->retirar_aresta(arestas[i].first.first, arestas[i].first.second);
                }
            }
            delete T;
            return ps;
        }

};

int main(){
    int n;
    int m;
    cin >> n;
    cin >> m;
    Grafo* g = new Grafo(n);
    for(int i = 0; i < m; i++){
        int u;
        int v;
        int p;
        cin >> u;
        cin >> v;
        cin >> p;
        g->adiciona_aresta(u - 1, v - 1, p);
    }
    cout << g->kruskal() << endl;
    delete g;
    return 0;
}