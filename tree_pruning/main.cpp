#include <cstdio>
#include <vector>
#define INF 1000000009
#define MAXN 305
using namespace std;


int N, D, color[MAXN], w[MAXN], b[MAXN], dp[MAXN][2*MAXN];
vector<int> ch[MAXN];

// color is 1 for white, 0 for black
// difference is white - black

void dfs(int u) {

    w[u] = color[u];
    b[u] = color[u]^1;

    for (int v : ch[u]) {
        dfs(v);
        w[u] += w[v];
        b[u] += b[v];
    }

    dp[u][w[u]-b[u]+N] = 0;

    for (int v : ch[u]){
        int diff = (w[u]-w[v])-(b[u]-b[v]) + N;
        dp[u][diff]=min(dp[u][diff], 1);
    }

    int delta = color[u]==0 ? -1 : 1;

    if (ch[u].size()==2) {
        dp[u][delta+N] = min(dp[u][delta+N], 2);
    }


    for (int v : ch[u]) {
        for (int s = 0; s <= 2*N; ++s) {
            int diff = (w[u]-w[v])-(b[u]-b[v])+s;
            if (diff>=0 && diff <= 2*N) {
                dp[u][diff] = min(dp[u][diff], dp[v][s]);
            }
        }

    }   

    // Case 4: You cut one edge, and cut inside the other
    for (int v : ch[u]) {
        for (int w : ch[u]) {
            if (v==w) continue;
            for (int s = 0; s <= 2*N; ++s) {
                int diff = delta + s;
                if (diff>=0 && diff <= 2*N) 
                    dp[u][diff] = min(dp[u][diff], dp[w][s]+1);
            }
        }
    }

    // Case 4: You cut both inside
    if (ch[u].size()==2) {
        int v = ch[u][0], w = ch[u][1];
        for (int sv = 0; sv <= 2*N; ++sv) {
            for (int sw = 0; sw <= 2*N; ++sw) {
                int diff = sv+sw+delta-N;
                if (diff>=0 && diff <= 2*N) 
                    dp[u][diff] = min(dp[u][diff], dp[w][sw]+dp[v][sv]);
            }
        }
    }
}


int main() {
    freopen("data.txt", "r", stdin);
    scanf("%d%d", &N, &D);

    for (int u = 0; u < N; ++u)
        for (int s = 0; s <= 2*N; ++s)
            dp[u][s] = INF;

    for (int i = 0; i < N; ++i) {
        int u, numc; scanf("%d", &u);
        scanf("%d%d", color+u, &numc);
        while (numc--) {
            int v; scanf("%d", &v);
            ch[u].push_back(v);
        }
    }
    dfs(0);
    printf("%d\n", dp[0][D+N] == INF ? -1 : dp[0][D+N]);
}