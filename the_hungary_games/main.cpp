#include <cstdio>
#include <vector>
#include <queue>
#define MAXN 20004
#define INF 1000000000
using namespace std;
typedef pair<int, int> ii;

int N, M, visit[MAXN], dist[MAXN], sdist[MAXN];

vector<ii> adj[MAXN];

priority_queue<ii, vector<ii>, greater<ii> > pq;


int dijkstra(int src, int dst) {
    for (int i = 1; i <= N; ++i) dist[i] = INF, sdist[i]=INF+1;

    dist[src]=0;
    pq.push(ii(0, src));

    while (!pq.empty()) {
        ii front = pq.top(); pq.pop();
        int d = front.first, u = front.second;

        if (d > dist[u]) continue;

        for (size_t i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i].second, w = adj[u][i].first;

            if (w+d < dist[v]) {
            	sdist[v] = dist[v];
            	dist[v] = w+d;

                if (w+sdist[u] > dist[v]) sdist[v] = min(sdist[v], w+sdist[u]);
                pq.push(ii(dist[v], v));

            } else if (w+d < sdist[v] && w+d > dist[v]) {
            	sdist[v] = w+d;

            	pq.push(ii(dist[v], v));
            } else if (w+sdist[u] < sdist[v] && w+sdist[u] > dist[v]) {
            	sdist[v] = w+sdist[u];

            	pq.push(ii(dist[v], v));
            }
        }
    }
    return sdist[dst];
}

int main() {
// 	freopen("data.txt", "r", stdin);
	scanf("%d%d", &N, &M);

	for (int i = 0, a, b, w; i < M; ++i) {
		scanf("%d%d%d", &a, &b, &w);
		adj[a].push_back(ii(w, b)); 
	}
    int ans = dijkstra(1, N);
    if (ans >= INF) ans = -1;
	printf("%d\n", ans);

}