#include <cstdio>
#include <vector>
#include <functional>
#include <queue>
#define MAXN 100005
#define MAXM 200005
#define INF 1000000000
using namespace std;

typedef pair<int, int> ii;
vector<ii> adj[MAXN];
int N, M, X, Y, Q, cold[MAXN], warm[MAXN], visit[MAXN];
pair<int, ii> edges[MAXM]; // (w, (a, b))

void dijkstra(int src, int* dist) {
    priority_queue<ii, vector<ii>, greater<ii> > pq;
    for (int i = 1; i <= N; ++i) dist[i] = INF;
    dist[src]=0;
    pq.push(ii(0, src));
    while (!pq.empty()) {
        ii front = pq.top(); pq.pop();
        int d = front.first, u = front.second;
        if (d > dist[u]) continue;
        for (size_t i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i].second, w = adj[u][i].first;
            if (w+d < dist[v]) {
                dist[v] = w+d;
                pq.push(ii(dist[v], v));
            }
        }
    }
}


int main() {
    // freopen("data.txt", "r", stdin);
    scanf("%d%d%d%d", &N, &M, &X, &Y);
    for (int i = 1, a, b, w; i <= M; ++i) {
        scanf("%d%d%d", &a, &b, &w);
        adj[a].push_back(ii(w, b));
        adj[b].push_back(ii(w, a));
        edges[i] = pair<int, ii>(w, ii(a, b) );
    }
    dijkstra(X, warm);
    dijkstra(Y, cold);
    scanf("%d", &Q);
    while (Q--) {
        int F, L;
        scanf("%d%d", &F, &L);
        if (F==1) {
            if (warm[L]==cold[L]) printf("%d\n", warm[L]);
            else printf("-1\n");
        } else {
            int u = edges[L].second.first, v = edges[L].second.second, w = edges[L].first;
            
            if ( (warm[u] < cold[u] && warm[v] < cold[v]) ||  (cold[u] < warm[u] && cold[v] < warm[v]) || 
                (warm[v] < cold[v] && warm[u] < cold[u]) || (cold[v] < warm[v] && cold[u] < warm[u]) ) {
                    printf("-1\n");
            } 
            else if  ( (warm[u] < cold[u] && warm[v] == cold[v]) ||  (cold[u] < warm[u] && cold[v] == warm[v]) || 
                (warm[v] < cold[v] && warm[u] == cold[u]) || (cold[v] < warm[v] && cold[u] == warm[u]) ) {

                    if (warm[u]==cold[u]) swap(u, v);

                    // u then v.
                    int *first, *second;
                    if (warm[u]<cold[u]) first = warm, second = cold;
                    else first = cold, second = warm;

                    if (first[v]==first[u]+w) printf("-1\n");
                    else printf("%d\n", first[v]);

            } else if  ( (warm[u] < cold[u] && warm[v] > cold[v]) ||  (cold[u] < warm[u] && cold[v] > warm[v]) ) {
                    int *first, *second;
                    if (warm[u] < cold[u]) first = warm, second = cold;
                    else first = cold, second = warm;

                    // somewhere in middle
                    printf("%f\n", (w + first[u] + second[v]) * 0.5f );
            } else {
                printf("%d\n", min(warm[u], warm[v]));
            }
            
           
        }
    }
}