#include <cstdio>
#include <vector>
#include <queue>
#define MAXN 20004
#define INF 1000000000
using namespace std;
typedef pair<int, int> ii;

int N, M, dist[MAXN], sdist[MAXN];
bool visit[MAXN];
vector<ii> adj[MAXN];

queue<int> q;


void bfs(int src) {
    for (int i = 1; i <= N; ++i) dist[i] = INF, sdist[i]=INF+1;

    dist[src]=0;
    q.push(src);

    while (!q.empty()) {
   
        int u = q.front(); q.pop();
        int d=dist[u];

        visit[u] = false;

        for (size_t i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i].second, w = adj[u][i].first;

            if (w+d < dist[v]) {
            	sdist[v] = dist[v];
            	dist[v] = w+d;

                if (w+sdist[u] > dist[v] && w+sdist[u] < sdist[v]) sdist[v] = w+sdist[u];
                if (!visit[v]) {
                    visit[v] = true;
                    q.push(v);
                }

            } else if (w+d < sdist[v] && w+d > dist[v]) {
            	sdist[v] = w+d;
                if (!visit[v]) {
                    visit[v] = true;
                    q.push(v);
                }
            } else if (w+sdist[u] < sdist[v] && w+sdist[u] > dist[v]) {
            	sdist[v] = w+sdist[u];
            	if (!visit[v]) {
                    visit[v] = true;
                    q.push(v);
                }
                
            }
        }
    }
}

int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d%d", &N, &M);

	for (int i = 0, a, b, w; i < M; ++i) {
		scanf("%d%d%d", &a, &b, &w);
		adj[a].push_back(ii(w, b)); 
	}
    bfs(1);
    
	printf("%d\n", sdist[N]>=INF ? -1 : sdist[N]);

}