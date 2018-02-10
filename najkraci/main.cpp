#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
typedef long long ll;
typedef priority_queue<ii, vector<ii>, greater<ii> > minheap;
const int MAXN = 1505, MAXM = 5005, INF = 1e9, MOD=1e9+7;

struct edge {int a, b, w;} e[MAXM];
int N, M, dist[MAXN];
vector<int>  adj[MAXN], dag[MAXN], rdag[MAXN];
ll in[MAXN], out[MAXN], ans[MAXM];

minheap pq;
bool active[MAXM], visit[MAXN];

void search(int src) {
	pq = minheap();
	for (int i = 1; i <= N; ++i) {
		dist[i] = INF;
		dag[i].clear();
		rdag[i].clear();
	}
	memset(active, 0, sizeof active);
	dist[src] = 0;
	pq.push(ii(0,src));
	while (!pq.empty()) {
		int u = pq.top().second, d = pq.top().first; 
		pq.pop();
		if (dist[u] < d) continue;
		for (int eid : adj[u]) {
			int v = e[eid].b, w = e[eid].w;
			if (dist[v] == w+d) {
				rdag[v].push_back(eid);
			} else if (dist[v] > w+d) {
				dist[v] = w+d;
				pq.push(ii(dist[v], v));
				rdag[v].clear();
				rdag[v].push_back(eid);
			}
		}
	}

	for (int i = 1; i <= N; ++i) {
		for (int j : rdag[i]) {
			dag[e[j].a].push_back(j);
			active[j] = true;
		}
	}
}

void dfsOut(int u) {
	visit[u] = 1;
	out[u] = 1;
	for (int ei : dag[u]){
		int v = e[ei].b;
		if (!visit[v]) dfsOut(v);
		out[u] += out[v];
	}
}

void dfsIn(int u, int src) {
	visit[u] = 1;
	if (u==src) in[u] = 1;
	else {
		for (int ei : rdag[u]) {
			int v = e[ei].a;
			if (!visit[v]) dfsIn(v, src);
			in[u] += in[v];
		}
	}
}

void solve(int u) {
	search(u);

	memset(visit, 0, sizeof visit);
	memset(out, 0, sizeof out);
	dfsOut(u);

	memset(visit, 0, sizeof visit);
	memset(in, 0, sizeof in);

	for (int i = 1; i <= N; ++i) if (!visit[i]) dfsIn(i, u);

	for (int i = 1; i <= M; ++i) 
		if (active[i]) ans[i] = (ans[i]+(in[e[i].a]*out[e[i].b])%MOD)%MOD;
}

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= M; ++i) {
		scanf("%d%d%d", &e[i].a, &e[i].b, &e[i].w);
		adj[e[i].a].push_back(i);
	}
	for (int u = 1; u <= N; ++u) solve(u);
	for (int i = 1; i <= M; ++i) printf("%lld\n", ans[i]);
}