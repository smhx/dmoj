#include <cstdio>
#include <vector>
#define INF 1000000009
#define MAXN 205
using namespace std;


int N, D, color[MAXN], w[MAXN], b[MAXN], dp[MAXN][2*MAXN];
vector<int> ch[MAXN];

void dfs(int u) {

    w[u] = color[u];
    b[u] = color[u]^1;

    for (int v : ch[u]) {
        dfs(v);
        w[u] += w[v];
        b[u] += b[v];
    }

    dp[u][w[u]-b[u]+N]=0;

    int delta = color[u]==1 ? -1 : 1;
    for (int v : ch[u]) {
        for (int s = 0; s <= N+D; ++s)
            dp[u][s+delta] = min(dp[u][s+delta], dp[v][s]);
    }


    if (ch[u].size()==2) {
        int v = ch[u][0], w = ch[u][1];
        // you can make a sum lft on left and rt on right
        for (int lft = 1; lft <= N; ++lft) {
            for (int rt = 1; rt <= N; ++rt) {
                dp[u][lft+rt+delta] = min(dp[u][lft+rt+delta], );
            }
        }
    }

}


int main() {
    scanf("%d%d", &N, &D);

    for (int u = 0; u < N; ++u)
        for (int s = 0; s <= N+D; ++s)
            dp[u][s] = INF;

    for (int i = 0; i < N; ++i) {
        int u, numc; scanf("%d", &u);
        scanf("%d%d", color+u, &numc);
        while (numc--) {
            int v; scanf("%d", &v);
            ch[u].push_back(v);
        }
    }

    // dp[u][s] to make s-N in T[u]
    dfs(0);

}