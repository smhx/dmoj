#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int N, M, K;
vector<int> adj[4005];

int main() {
    // freopen("data.txt", "r", stdin);
    scanf("%d%d%d", &N, &M, &K);
    for (int i = 0, a, b; i < K; ++i) {
        scanf("%d%d", &a, &b);
        adj[a].push_back(b+N);
        adj[b+N].push_back(a);
    }

    for (int i = 1; i <= N+M; ++i) sort(adj[i].begin(), adj[i].end());
    
    for (int u = 1; u < N; ++u) {
        for (int v = u+1; v <= N; ++v) {
            int i = 0, j = 0, cnt=0;
            while (i<(int)adj[u].size() && j < (int)adj[v].size() && cnt != 2) {
                if (adj[u][i] < adj[v][j]) ++i;
                else if (adj[v][j] < adj[u][i]) ++j;
                else ++i, ++j, ++cnt;
            }
            if (cnt==2) {
                printf("NO\n");
                return 0;
            }
        }
    }

    for (int u = N+1; u < N+M; ++u) {
        for (int v = u+1; v <= N+M; ++v) {
            int i = 0, j = 0, cnt=0;
            while (i<(int)adj[u].size() && j < (int)adj[v].size() && cnt != 2) {
                if (adj[u][i] < adj[v][j]) ++i;
                else if (adj[v][j] < adj[u][i]) ++j;
                else ++i, ++j, ++cnt;
            }
            if (cnt==2) {
                printf("NO\n");
                return 0;
            }
        }
    }

    
    printf("YES\n");
}