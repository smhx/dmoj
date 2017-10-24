#include <cstdio>
#include <vector>
#define MAXN 100005
using namespace std;

int N, M, apho, rsum=0, dia, best[MAXN];
bool pho[MAXN];

vector<int> adj[MAXN], radj[MAXN];

bool trim(int u, int p) {
    bool haspho = pho[u];
    for (int v : adj[u]) {
        if (v != p) {
            if ( trim(v, u) ) {
                radj[u].push_back(v);
                radj[v].push_back(u);
                haspho = true;
                ++rsum;
            }
        }
    }
    return haspho;
}

void dfs(int u, int p) {
    for (int v : radj[u]) {
        if (v!=p) {
            dfs(v, u);
            if (best[u]+best[v]+1 > dia) dia = best[u]+best[v]+1;
            if (best[u] < best[v]+1) best[u] = best[v]+1;
        }
    }
}

int main() {
    // freopen("data.txt", "r", stdin);
    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; ++i) {
        scanf("%d", &apho);
        pho[apho] = true;
    }
    for (int i = 0, a, b; i < N-1; ++i ) {
        scanf("%d%d", &a, &b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    trim(apho, -1);
    dfs(apho, -1);
    printf("%d\n", 2*rsum - dia);
}