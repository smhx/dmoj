#include <cstdio>
#include <queue>
#include <vector>
#include <utility>
#include <functional>
#define MAXK 205
#define MAXN 2005
#define INF 1000000000
#define mp make_pair
using namespace std;

typedef pair<int, pair<int, int> > triple; 
typedef pair<int, triple> quad;
int K, N, M, dist[MAXN][MAXK], a, b;
vector<triple> adj[MAXN]; 
priority_queue<quad, vector<quad>, greater<quad> > pq; 
int main() {
    freopen("s4/s4.13.in", "r", stdin);
    scanf("%d%d%d", &K, &N, &M);
    for (int i = 0; i < M; ++i) {
        int a, b, t, h; scanf("%d%d%d%d", &a, &b, &t, &h);
        adj[a].push_back( mp(t, mp(h, b))  );
        adj[b].push_back( mp(t, mp(h, a))  );
    }
    scanf("%d%d", &a, &b);
    for (int i = 1; i <= N; ++i) for (int j = 1; j <= K; ++j) dist[i][j] = INF;
    dist[a][K]=0;
    pq.push(mp(0, mp(K, mp(a, -1) ) ));
    while (!pq.empty()) {
        quad _ = pq.top(); pq.pop();
        int d = _.first; int h = _.second.first; int u = _.second.second.first;
        int p = _.second.second.second;
        if (d > dist[u][h]) continue;
        if (u==b) {
            printf("%d\n", d>=INF ? -1 : d);
            return 0;
        }
        for (size_t i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i].second.second; 
            if (v==p) continue;
            int w = adj[u][i].first; 
            int damage = adj[u][i].second.first;
            if (h-damage <= 0) continue;
            if (w+d < dist[v][h-damage]) {
                dist[v][h-damage] = w+d;
                pq.push(mp(w+d, mp(h-damage, mp(v, u) ) ) );
            }
        }
    }
    printf("%d\n", -1);
}
