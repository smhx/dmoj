#include <cstdio>
#include <queue>
#include <functional>
#include <vector>
using namespace std;
typedef pair<int,int> ii;
typedef priority_queue<ii, vector<ii>, greater<ii> > minheap;
const int MAXN = 5005, INF = 1000000000;
int N, K, T, D, dist[MAXN], P[MAXN];
vector<ii> adj[MAXN];
minheap pq;

int main() {
// 	freopen("data.txt", "r", stdin);
	scanf("%d%d", &N, &T);
	for (int i = 0; i < T; ++i) {
		int x, y, c;
		scanf("%d%d%d", &x, &y, &c);
		adj[x].push_back({c,y});
		adj[y].push_back({c,x});
	}
	for (int i = 1; i <= N; ++i) dist[i] = INF;

	scanf("%d", &K);
	for (int i = 0; i < K; ++i) {
		int z, pz; scanf("%d%d", &z, &pz);
		dist[z] = pz;
		pq.push(ii(pz, z));
	}

	scanf("%d", &D);

	while (!pq.empty()) {
		int u, d;
		tie(d,u) = pq.top();
		pq.pop();
		if (d > dist[u]) continue;
		if (u==D) break;
		for (ii e : adj[u]) {
			if (d + e.first < dist[e.second]) {
				dist[e.second] = d+e.first;
				pq.push(ii(dist[e.second], e.second));
			}
		}
	}
	printf("%d\n", dist[D]);
}