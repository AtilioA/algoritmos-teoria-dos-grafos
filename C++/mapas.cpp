#include <iostream>
#include <vector>
#include <limits>
#include <sstream>
#include <algorithm>

using namespace std;

bool encontrar(vector<int> vt, int v){
    for(int k : vt){
        if(k == v){
            return true;
        }
    }
    return false;
}
class Grafo{
    private:
        vector<vector<pair<int, int> > > adj;
        int nVertices;
        int peso;
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

            this->adj[v].push_back(ida);
            this->adj[u].push_back(volta);
            this->peso += peso;
        }

        int prim(){
            int peso = 0;
            vector<int> Vl;
            Vl.push_back(0);
            vector<int> L;
            vector<int> V;
            vector<int> diff;
            for(int i = 0; i < this->nVertices; i++){
                V.push_back(i);
            }
            for(int i = 0; i < this->nVertices; i++){
                L.push_back(numeric_limits<int>::max());
            }
            for(pair<int, int> k : this->adj[0]){
                L[k.first] = k.second;
            }
            set_difference(V.begin(), V.end(), Vl.begin(), Vl.end(), inserter(diff, diff.end()));
            
            while(!diff.empty()){
                vector<int> pesosDiff;
                for(int i : diff){
                    pesosDiff.push_back(L[i]);
                }
                int minPeso = *min_element(pesosDiff.begin(), pesosDiff.end());
                int w = 0;
                for(int i = 0; i < L.size(); i++){
                    if(L[i] == minPeso && encontrar(diff, i)){
                        w = i;
                        break;
                    }
                }
                int u = Vl[0];
                for(pair<int, int> ar : this->adj[w]){
                    if(ar.second < this->getPeso(u, w) && encontrar(Vl, ar.first)){
                        u = ar.first;
                    }
                }
                peso+=this->getPeso(u, w);
                Vl.push_back(w);
                sort(Vl.begin(), Vl.end());
                diff.clear();
                set_difference(V.begin(), V.end(), Vl.begin(), Vl.end(), inserter(diff, diff.end()));
                for(int v : diff){
                    int p = this->getPeso(v, w);
                    if(p < L[v]){
                        L[v] = p;
                    }
                }
            }
            return peso;
        };
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
    cout << g->prim() << endl;
    delete g;
    return 0;
}