#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#define MAXN 10005
using namespace std;
vector<int> adj[MAXN], hist, members[MAXN];
int N, M, idxcnt=1, ringcnt=1;
int ring[MAXN], ord[MAXN], visited[MAXN];
int lowlink[MAXN], idx[MAXN], onstack[MAXN];
void label(int u, int last) {
    lowlink[u]=idx[u]=idxcnt++;
    onstack[u]=1; hist.push_back(u);
    for (int i = 0; i < (int)adj[u].size(); ++i) {
        int w = adj[u][i];
        if (w==last) continue;
        if (idx[w]==0) {
            label(w, u);
            lowlink[u] = min(lowlink[u], lowlink[w]);
        } else if (onstack[w]) {
            lowlink[u] = min(lowlink[u], idx[w]);
        }
    }   
    if (lowlink[u]==idx[u]) {
        int cnt=0;
        while (1) {
            int t = hist.back(); 
            hist.pop_back();
            onstack[t]=0;
            ring[t]=ringcnt;
            ord[t]=cnt++;
            members[ringcnt].push_back(t);
            if (t==u) break;
        }
        ++ringcnt;
    }
}
inline int dist(int a, int b, int size) {
    if (size==1) return 0;
    if (a>b) swap(a, b);
    return max(b-a, size-b+a);
    // if (size==1) return 0;
    // if (a < b) return b-a;
    // else return size-(a-b);
}
int maxcourse(int u, int last) {
    printf("In maxcourse(%d)\n", u);
    visited[u]=1;
    int r = ring[u], size = members[r].size();
    int m = size<3 ? 0 : size;
    int place = ord[u];
    for (int i = 0; i < size; ++i) {
        int v = members[r][i];
        int d = dist(place, i, size);
        for (int j = 0; j < (int)adj[v].size(); ++j) {
            int w = adj[v][j];
            if (w==last) continue;
            if (ring[w]!=r && !visited[w]) {
                m = max(m, d+1+maxcourse(w, v));
            }
        }
    }
    printf("FROM maxcourse(%d) returnign %d\n", u, m);
    return m;
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; ++i) {
        int a, b; scanf("%d%d", &a, &b);
        adj[a].push_back(b); adj[b].push_back(a);
    }
    label(1, -1);
    for (int i = 1; i <= N; ++i) {
        printf("ring[%d]=%d, ord[%d]=%d\n", i, ring[i], i, ord[i]);
    }
    printf("%d\n", maxcourse(1, -1));
}
