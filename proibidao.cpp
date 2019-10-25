#include <iostream>
#include <vector>
#include <limits>
#include <sstream>

using namespace std;

bool is_in(vector<bool>::iterator it1, vector<bool>::iterator it2, bool val){
    for(vector<bool>::iterator it = it1; it != it2; it++){
        if((*it) == val){
            return 1;
        }
    }
    return 0;
}
template <typename comparavel>
int index(typename vector<comparavel>::iterator it1,typename vector<comparavel>::iterator it2, comparavel val){
    int qtd = 0;
    for(typename vector<comparavel>::iterator it = it1; it != it2; it++){
        if((*it) == val){
            return qtd;
        }
        qtd++;
    }
    return 0;
}

int sum_inf(int i, int j){
    if(j == numeric_limits<int>::max() || i == numeric_limits<int>::max()){
        return numeric_limits<int>::max();
    }else{
        return i + j;
    }
}

class Grafo{
    private:
        vector<vector<pair<int, int>>> adj;
        int nVertices;
        vector<bool> aberto;
    public:
        Grafo(int nVertices){
            for(int i = 0 ; i < nVertices; i++){
                vector<pair<int, int>> k;
                this->aberto.push_back(1);
                this->adj.push_back(k);
            }
            this->nVertices = nVertices;
        };
        void adicionarAresta(int u, int v, int peso){
            pair<int, int> ida;
            pair<int, int> volta;
            ida = make_pair(u, peso);
            volta = make_pair(v, peso);
            this->adj[v].push_back(ida);
            this->adj[u].push_back(volta);
        }
        vector<int> djkstra_proibido(int inicio, int proibido){
            vector<int> dists;
            for(int i = 0; i < this->nVertices; i++){
                dists.push_back(numeric_limits<int>::max());
            }
            dists[inicio] = 0;
            this->aberto[proibido] = 0;
            while(is_in(this->aberto.begin(), this->aberto.end(), 1)){
                int indiceMenor = index<bool>(this->aberto.begin(), this->aberto.end(), 1);
                int cnt = 0;
                for(int dist: dists){
                    if(this->aberto[cnt] && dist < dists[indiceMenor]){
                        indiceMenor = cnt;
                    }
                    cnt++;
                }
                this->aberto[indiceMenor] = 0;
                vector<pair<int, int>> vizinhos = this->adj[indiceMenor];
                for(pair<int, int> vizinho: vizinhos){
                    if(this->aberto[vizinho.first]){
                        int custo = min(dists[vizinho.first], sum_inf(dists[indiceMenor], vizinho.second));
                        dists[vizinho.first] = custo;
                    }
                }
            }
            return dists;
        }
};

int main(){
    string entrada;
    int n;
    int m;
    int a;
    int b;
    int c;
    int e;
    int r;
    while(1){
        getline(cin, entrada);
        if(entrada.empty()){
            break;
        }
        stringstream entrada1(entrada);
        entrada1 >> n;
        entrada1 >> m;
        Grafo *g = new Grafo(n);
        for(int i = 0; i < m; i++){
            getline(cin, entrada);
            stringstream entrada2(entrada);
            entrada2 >> a;
            entrada2 >> b;
            g->adicionarAresta(a - 1, b - 1, 1);
        }
        getline(cin, entrada);
        stringstream entrada3(entrada);
        entrada3 >> c;
        entrada3 >> r;
        entrada3 >> e;
        vector<int> k = g->djkstra_proibido(c - 1, e - 1);
        entrada.erase();
        cout << k[r-1] << '\n';
        delete g;
    }
    return 0;
}