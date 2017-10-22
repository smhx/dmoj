#include <cstdio>
#include <cstring>
#define MAXN 105

int N, M, numBridges = 0, adj[MAXN][MAXN], visit[MAXN];

void dfs(int u) {
    visit[u] = 1;
    for (int v = 1; v <= N; ++v) 
        if (adj[u][v] && !visit[v]) 
            dfs(v);
        
}

int main() {
    for (int _ = 0; _ < 5; ++_) {
        scanf("%d%d", &N, &M);
        numBridges = 0;
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= N; ++j) {
                adj[i][j] = 0;
            }
        }
        for (int i = 0, a, b; i < M; ++i) {
            scanf("%d%d", &a, &b);
            adj[a][b] = adj[b][a] = 1;
        }
        for (int i = 1; i < N; ++i) {
            for (int j = i+1; j <= N; ++j) {
                if (adj[i][j]) {
                    adj[i][j] = adj[j][i] = 0;
                    memset(visit, 0, sizeof visit);
                    dfs(1);
                    bool c = true;
                    for (int u = 1; u <= N; ++u) 
                        if (!visit[u]) c = false;
                    if (!c) ++numBridges;
                    
                    adj[i][j] = adj[j][i] = 1;
                }
                
            }
        }
        printf("%d\n", numBridges);
    }
    
}