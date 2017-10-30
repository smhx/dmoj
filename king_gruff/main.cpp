#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#define MAXN 100005
#define INF 1000000009
using namespace std;
typedef pair<int, int> ii;
struct E {
	int from, to, l, c, minp;
	bool operator<(const E& e) const {return minp < e.minp;}
} edges[MAXN];
typedef priority_queue<ii, vector<ii>, greater<ii> > minheap;

vector<E> adj[MAXN], radj[MAXN];

int N, M, A, B, Q, D, fromsrc[MAXN], todest[MAXN], s[MAXN], len[MAXN];

void pfs(int src, vector<E> *G, int* dist) {
	minheap pq;
	for (int i = 1; i <= N; ++i) dist[i] = INF;
	dist[src] = 0;
	pq.push({0, src});
	while (!pq.empty()) {
		ii t = pq.top(); pq.pop();
		int u = t.second, d = t.first;
		if (d > dist[u]) continue;
		for (E e : G[u]) {
			if (d + e.l < dist[e.to]) {
				dist[e.to] = d+e.l;
				pq.push({dist[e.to], e.to});
			}
		}
	}
}

int main() {
	// freopen("data.txt", "r", stdin);
	scanf("%d%d%d%d", &N, &M, &A, &B);
	for (int i = 0, x, y, l, c; i < M; ++i) {
		scanf("%d%d%d%d", &x, &y, &l, &c);
		edges[i] = {x, y, l, c};
		adj[x].push_back({x, y, l, c});
		radj[y].push_back({y, x, l, c});
	}

	pfs(A, adj, fromsrc);
	pfs(B, radj, todest);

	for (int i = 0; i < M; ++i) {
		edges[i].minp = edges[i].l + fromsrc[edges[i].from] + todest[edges[i].to];
	}
	sort(edges, edges+M);
	
	vector<ii> v;

	for (int i = 0, sum = 0; i < M && edges[i].minp < INF; ) {
		int p = edges[i].minp;
		int j = i;
		for (; j < M && edges[j].minp == p; ++j);
		for (; i != j; ++i) sum += edges[i].c;
		v.push_back({p, sum});
	}
	
	scanf("%d", &Q);
	while(Q--) {
		scanf("%d", &D);
		auto it = upper_bound(v.begin(), v.end(), ii(D+1, -1)); // look for first with D strictly greater
		if (it==v.begin()) printf("0\n");
		else {
			--it;
			printf("%d\n", it->second);
		}
	}
}
