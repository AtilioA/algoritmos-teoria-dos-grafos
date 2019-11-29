#include <cstdio>
#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;

#define NN 100
#define INT_MAX 0x3f3f3f

// adjacency matrix (fill this up)
int cap[NN][NN];

// cost per unit of flow matrix (fill this up)
int cost[NN][NN];

// flow network and adjacency list
int fnet[NN][NN], adj[NN][NN], deg[NN];

// Dijkstra's successor and depth
int par[NN], d[NN]; // par[source] = source;

// Labelling function
int pi[NN];

#define CLR(a, x) memset(a, x, sizeof(a))
#define Inf (INT_MAX / 2)

// Dijkstra's using non-negative edge weights (cost + potential)
#define Pot(u, v) (d[u] + pi[u] - pi[v])
bool dijkstra(int n, int s, int t)
{
    for (int i = 0; i < n; i++)
        d[i] = Inf, par[i] = -1;
    d[s] = 0;
    par[s] = -n - 1;

    while (1)
    {
        // find u with smallest d[u]
        int u = -1, bestD = Inf;
        for (int i = 0; i < n; i++)
            if (par[i] < 0 && d[i] < bestD)
                bestD = d[u = i];
        if (bestD == Inf)
            break;

        // relax edge (u,i) or (i,u) for all i;
        par[u] = -par[u] - 1;
        for (int i = 0; i < deg[u]; i++)
        {
            // try undoing edge v->u
            int v = adj[u][i];
            if (par[v] >= 0)
                continue;
            if (fnet[v][u] && d[v] > Pot(u, v) - cost[v][u])
                d[v] = Pot(u, v) - cost[v][u], par[v] = -u - 1;

            // try edge u->v
            if (fnet[u][v] < cap[u][v] && d[v] > Pot(u, v) + cost[u][v])
                d[v] = Pot(u, v) + cost[u][v], par[v] = -u - 1;
        }
    }

    for (int i = 0; i < n; i++)
        if (pi[i] < Inf)
            pi[i] += d[i];

    return par[t] >= 0;
}
#undef Pot

int saldo;

int mcmf3(int n, int s, int t, int &fcost, int &d, int k)
{
    // build the adjacency list
    CLR(deg, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (cap[i][j] || cap[j][i])
                adj[i][deg[i]++] = j;

    CLR(fnet, 0);
    CLR(pi, 0);
    int flow = fcost = 0;

    // repeatedly, find a cheapest path from s to t
    while (dijkstra(n, s, t))
    {
        // get the bottleneck capacity
        int bot = INT_MAX;
        for (int v = t, u = par[v]; v != s; u = par[v = u])
        {
            //bot <?= fnet[v][u] ? fnet[v][u] : ( cap[u][v] - fnet[u][v] );
            bot = min(bot, fnet[v][u] ? fnet[v][u] : (cap[u][v] - fnet[u][v]));
        }

        if (k >= d)
        { //Mais assentos que amigos.       
            saldo = d;
            d = 0;
        }
        else
        {
            saldo = k;
            d -= k;
        }

        // update the flow network
        for (int v = t, u = par[v]; v != s; u = par[v = u])
            if (fnet[v][u])
            {
                fnet[v][u] -= bot;
                fcost -= bot * cost[v][u] * saldo;
            }
            else
            {
                fnet[u][v] += bot;
                fcost += bot * cost[u][v] * saldo;
            }

        flow += bot;
        if (d == 0)
            break;
    }

    return flow;
}

//----------------- EXAMPLE USAGE -----------------

int main()
{
    int numV, m, inst = 1;
    while (scanf("%d%d", &numV, &m) != EOF)
    {
        //cin >> numV;
        for (int i = 0; i < numV; i++)
            for (int j = 0; j < numV; j++)
                cap[i][j] = 0;

        int a, b, c, cp, n, d, k;
        int s, t;
        s = 0;
        t = numV - 1;

        // fill up cap with existing capacities.
        // if the edge u->v has capacity 6, set cap[u][v] = 6.
        // for each cap[u][v] > 0, set cost[u][v] to  the
        // cost per unit of flow along the edge i->v
        for (int i = 0; i < m; i++)
        {
            scanf("%d%d%d", &a, &b, &c);
            a--;
            b--;
            cost[a][b] = c;
            cost[b][a] = c;
            cap[a][b] = 1;
            cap[b][a] = 1;
        }
        scanf("%d%d", &d, &k);
        int fcost;
        int flow = mcmf3(numV, s, t, fcost, d, k);
        printf("Instancia %d\n", inst++);
        if (d)
            puts("impossivel");
        else
            printf("%d\n", fcost);
        putchar('\n');
    }
    //system("PAUSE");
    return 0;
}