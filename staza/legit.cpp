#include <cstdio>
#include <vector>
#include <algorithm>
#include <unordered_map>
#define MAXN 10001
#define INF 100000000
using namespace std;

int N, M;
vector<int> adj[MAXN];
unordered_map<int, int> ord[MAXN];
vector<int> cities[MAXN], rings[MAXN]; 
// cities is el in cities. rings[x] is rings for el
int lowlink[MAXN], idx[MAXN], onstack[MAXN], mark[MAXN];
int idxcnt=1, ringcnt=1;
vector<int> hist;
void label(int u) {
    lowlink[u]=idx[u]=idxcnt++;
    onstack[u]=1; hist.push_back(u);
    for (int i = 0; i < (int)adj[u].size(); ++i) {
        int w = adj[u][i];
        if (idx[w]==0) {
            label(w);
            lowlink[u] = min(lowlink[u], lowlink[w]);
        } else if (onstack[w] && idx[w]<lowlink[u]) {
            lowlink[u]=idx[w];
            mark[w] = 1;
            // lowlink[u] = min(lowlink[u], idx[w]);
        }
    }   
    if (lowlink[u]==idx[u]) {
        int cnt=0;
        while (1) {
            int t = hist.back(); hist.pop_back();
            onstack[t]=0;
            rings[t].push_back(ringcnt);
            if (mark[t]) {
                
            }
        }
        // while (1) {
        //     int t = hist.back(); 
        //     hist.pop_back();
        //     onstack[t]=0;
        //     ring[t]=ringcnt;
        //     ord[t]=cnt++;
        //     members[ringcnt].push_back(t);
        //     if (t==u) break;
        // }
        // ++ringcnt;
    }
}
inline int dist(int a, int b, int size) {
    if (size==1) return 0;
    if (a>b) swap(a, b);
    return max(b-a, size-b+a);
}
int maxcourse(int u, int lastr) {
    int m = -INF;
    for (auto r : rings[u]) {
        if (r!=lastr) {
            int size = (int)rings[r].size();
            m = (size==1) ? 0 : size;
            int place = ord[u][r];
            for (int order = 0; order<size; order++) {
                int v = cities[r][order];
                int d = dist(place, order, size);
                for (auto w : adj[v]) {
                    m = max(m, d+1+maxcourse(w, r));
                }
            }
        }
    }
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; ++i) {
        int a, b; scanf("%d%d", &a, &b);
        adj[a].push_back(b); adj[b].push_back(a);
    }
    label(1);
    printf("%d\n", maxcourse(1, -1));
}