#include <iostream>
#include <vector>
#include <limits>
#include <sstream>
#include <algorithm>

using namespace std;

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
            peso += peso;
        }

        int prim(){
            Grafo* T = new Grafo(this->nVertices);
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
                    cout << i << ":";
                }
                cout << "\n";
                int minPeso = *min_element(pesosDiff.begin(), pesosDiff.end());
                int w = 0;
                cout << minPeso << " PORRA\n";
                for(int i = 0; i < L.size(); i++){
                    if(L[i] == minPeso && *find(diff.begin(), diff.end(), i) == i){
                        w = i;
                    }
                }
                int u = Vl[0];
                for(int i: Vl){
                    cout << i << "<->";
                }
                cout << "\n";
                for(pair<int, int> ar : this->adj[w]){
                    cout << ">>" << u << "<<" << ">>" << w << "<<" << ">>" << ar.first << "<<" << this->getPeso(u, w) << ";" << ar.second << "\n";
                    if(ar.second < this->getPeso(u, w) && *find(Vl.begin(), Vl.end(), ar.first) == ar.first){
                        u = ar.first;
                        cout << ar.first << "EU N QUERO MAIS\n";
                    }
                }
                cout << "(" << u << "," << w << ")" << this->getPeso(u, w) << "\n";
                T->adiciona_aresta(u, w, this->getPeso(u, w));
                cout << "-------------------------------------------------\n";
                Vl.push_back(w);
                sort(Vl.begin(), Vl.end());
                diff.clear();
                set_difference(V.begin(), V.end(), Vl.begin(), Vl.end(), inserter(diff, diff.end()));
                for(int v : diff){
                    cout << "-------------------============================-------\n";
                    int p = this->getPeso(u, w);
                    if(p < L[v]){
                        L[v] = p;
                    }
                }
            }
            int pesoArv = T->getPesoGrafo();
            delete T;
            return pesoArv;
        };
};

int main(){
    Grafo* g = new Grafo(5);
    g->adiciona_aresta(1 - 1, 2 - 1, 15);
    g->adiciona_aresta(1 - 1, 3 - 1, 10);
    g->adiciona_aresta(2 - 1, 3 - 1, 1);
    g->adiciona_aresta(3 - 1, 4 - 1, 3);
    g->adiciona_aresta(2 - 1, 4 - 1, 5);
    g->adiciona_aresta(4 - 1, 5 - 1, 20);
    //g->printVertices();
    cout << g->prim() << endl;
    delete g;
    return 0;
}