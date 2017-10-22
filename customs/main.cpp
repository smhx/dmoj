#include <cstdio>
#include <vector>
#define MAXN 100005
#define MOD 1000000007
using namespace std;

int N, M, dfscnt=0, lowlink[MAXN], dfsidx[MAXN], p[MAXN];

int color[MAXN];

vector<int> adj[MAXN];
typedef long long ll;

void dfs(int u, bool& found) {
    int cycles = 0;
    lowlink[u] = dfsidx[u] = ++dfscnt;
    for (int v : adj[u]) {
        if (found) return;
        if (dfsidx[v]==0) {
            p[v] = u;
            dfs(v, found);
            if (lowlink[v] < dfsidx[u]) ++cycles;
            lowlink[u] = min(lowlink[u], lowlink[v]);
        } else if (v != p[u]) {
            lowlink[u] = min(lowlink[u], dfsidx[v]);
            if (dfsidx[v] < dfsidx[u]) ++cycles;
        }
        if (cycles ==  2) found = true;
    }
}

void dfs2(int u, ll& prod) {
    color[u] = 2;
    for (int v : adj[u]) {
        if (!color[v]) 
            dfs2(v, prod);
        else if (color[v]==2 && v!=p[u]) {
            // cycle
            ll sz = 1;
            for (int x = u; x != v; x = p[x]) ++sz;

            prod *= sz;
            prod %= MOD;
        }
        
    }
    color[u] = 1;
}

int main() {
    freopen("data.txt", "r", stdin);
    scanf("%d%d", &N, &M);
    for (int i = 0, a, b; i < M; ++i) {
        scanf("%d%d", &a, &b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    bool multicycle = false;
    bool cacti = true;
    dfs(1, multicycle);

    if (multicycle) cacti = false;

    printf("multicycle = %d\n", multicycle);

    for (int i = 2; i <= N && cacti; ++i) {
        if (!dfsidx[i]) {
            printf("unconnected\n");
            cacti = false; // not connected
        }
    }
    
    if (!cacti) {
        printf("safe\n");
        return 0;
    }

    ll prod = 1;
    for (int i = 1; i <= N; ++i) {
        if (!color[i]) dfs2(i, prod);
    }
    
    printf("%lld\n", prod);
}

