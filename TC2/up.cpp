#include <iostream>
#include <algorithm>
#include <limits>
#include <vector>
#include <cstdio>

#define Inf numeric_limits<int>::max()
#define INT_MAX 0x3f3f3f
using namespace std;
#define potencial(a, b, c) (a + b - c)
class Grafo{
    private:
    public:
        int qtdVertices; 
        vector<vector<int>> capacidade;
        vector<vector<int>> custo;
        vector<vector<int>> flowg;
        vector<vector<int>> adj;
        vector<int> deg;
        vector<int> pai;
        vector<int> d;
        vector<int> pi;
        Grafo(int n){
            this->qtdVertices = n;
            for(int i = 0; i < n; i++){
                vector<int> vecCap(n, 0);
                vector<int> vecCost(n, 0);
                vector<int> vecFnet(n, 0);
                vector<int> vecAdj(n, 0);
                this->capacidade.push_back(vecCap);
                this->custo.push_back(vecCost);
                this->flowg.push_back(vecFnet);
                this->adj.push_back(vecAdj);
                this->deg.push_back(0);
                this->pai.push_back(0);
                this->d.push_back(0);
                this->pi.push_back(0);
            }
        };

        bool dijkstra(int s, int t)
        {
            for (int i = 0; i < this->qtdVertices; i++){
                d[i] = Inf; 
                pai[i] = -1;
            }
            d[s] = 0;
            pai[s] = -this->qtdVertices - 1;
            while (1)
            {
                int u = -1, melhorDist = Inf;
                for (int i = 0; i < this->qtdVertices; i++){
                    if (pai[i] < 0 && d[i] < melhorDist){
                        melhorDist = d[u = i];
                    }
                }
                if (melhorDist == Inf){
                    break;
                }
                pai[u] = -pai[u] - 1;
                for (int i = 0; i < deg[u]; i++)
                {
                    int v = adj[u][i];
                    if (pai[v] >= 0){
                        continue;
                    }
                    if (flowg[v][u] && d[v] > potencial(d[u], pi[u], pi[v]) - custo[v][u]){
                        d[v] = potencial(d[u], pi[u], pi[v]) - custo[v][u], pai[v] = -u - 1;
                    }
                    if (flowg[u][v] < capacidade[u][v] && d[v] > potencial(d[u], pi[u], pi[v]) + custo[u][v]){
                        d[v] = potencial(d[u], pi[u], pi[v]) + custo[u][v], pai[v] = -u - 1;
                    }
                }
            }
            
            for (int i = 0; i < this->qtdVertices; i++){
                if (pi[i] < Inf){
                    pi[i] += d[i];
                }
            }
            return pai[t] >= 0;
        };

        int flowGrafo(int s, int t, int &fcost, int &d, int k)
        {
            int saldo;
            for(int& i: deg){
                i = 0;
            }
            for (int i = 0; i < this->qtdVertices; i++){
                for (int j = 0; j < this->qtdVertices; j++){
                    if (capacidade[i][j] || capacidade[j][i]){
                        adj[i][deg[i]++] = j;
                    }
                }
            }
            for(int& i : pi){
                i = 0;
            }
            for(int i = 0; i < flowg.size(); i++){
                for(int j = 0; j < flowg[i].size(); j++){
                    flowg[i][j] = 0;
                }
            }
            int flow = fcost = 0;

            while (dijkstra(s, t)){
                int bot = INT_MAX;
                for (int v = t, u = pai[v]; v != s; u = pai[v = u])
                {
                    int fl = flowg[v][u];
                    if(!(fl)){
                        fl = (capacidade[u][v] - flowg[u][v]);
                    }
                    bot = min(bot, fl);
                }
                if (k >= d){    
                    saldo = d;
                    d = 0;
                }
                else{
                    saldo = k;
                    d -= k;
                }

                for (int v = t, u = pai[v]; v != s; u = pai[v = u]){
                    if (flowg[v][u]){
                        flowg[v][u] -= bot;
                        fcost -= bot * custo[v][u] * saldo;
                    }
                    else{
                        flowg[u][v] += bot;
                        fcost += bot * custo[u][v] * saldo;
                    }
                }

                flow += bot;
                if (d == 0){
                    break;
                }
            }

            return flow;
        }
        
};

int main(){
    int numV, m, inst = 1;
    Grafo *g;
    while (scanf("%d%d", &numV, &m) != EOF)
    {
        g = new Grafo(numV);
        for (int i = 0; i < numV; i++)
            for (int j = 0; j < numV; j++)
                g->capacidade[i][j] = 0;

        int a, b, c, cp, n, d, k;
        int s, t;
        s = 0;
        t = numV - 1;
        for (int i = 0; i < m; i++)
        {
            scanf("%d%d%d", &a, &b, &c);
            a--;
            b--;
            g->custo[a][b] = c;
            g->custo[b][a] = c;
            g->capacidade[a][b] = 1;
            g->capacidade[b][a] = 1;
        }
        scanf("%d%d", &d, &k);
        int fcost;
        int flow = g->flowGrafo(s, t, fcost, d, k);
        printf("Instancia %d\n", inst++);
        if (d)
            puts("impossivel");
        else
            printf("%d\n", fcost);
        putchar('\n');
        delete g;
    }
    return 0;
}