#include <bits/stdc++.h>
#define MAX_VERTS 205
typedef long long ll;
const ll INF = 2e9;
// 1 indexed
struct maxflow_t {
	ll nv, visit[MAX_VERTS], par[MAX_VERTS], g[MAX_VERTS][MAX_VERTS];
	bool dfs(ll u, ll dest) {
		visit[u] = true;
		if (u == dest) return true;
		for (ll v = 1; v <= nv; ++v) {
			if (!visit[v] && g[u][v] != 0) {
				par[v] = u;
				if (dfs(v, dest)) return true;
			}
		}
		return false;
	}
	ll maxflow(ll s, ll t) {
		ll mflow = 0;
		memset(visit, 0, sizeof visit);
		memset(par, 0, sizeof par);
		while (dfs(s,t)) {
			ll pflow = INF;
			for (ll u = t; u != s; u = par[u]) {
				pflow = std::min(pflow, g[par[u]][u]);
			}
			for (ll u = t; u != s; u = par[u]) {
				g[u][par[u]] += pflow;
				g[par[u]][u] -= pflow;
			}
			mflow += pflow;
			memset(par, 0, sizeof par);
			memset(visit, 0, sizeof visit);
		}
		return mflow;
	}
};

#define IN(u) (2*(u)-1)
#define OUT(u) (2*(u))

int main() {
	// freopen("data.txt", "r", stdin);
	ll n, m;
	maxflow_t flow;
	scanf("%lld", &n);
	for (ll u = 1; u < n; ++u) {
		scanf("%lld", &flow.g[IN(u)][OUT(u)]);
	}
	scanf("%lld", &m);
	for (ll i = 0, u, v; i < m; ++i) {
		scanf("%lld%lld", &u, &v);
		flow.g[OUT(u)][IN(v)] = INF;
	}
	flow.nv = 2*n-1;
	printf("%lld\n", flow.maxflow(IN(1), IN(n)));
}