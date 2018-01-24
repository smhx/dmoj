#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5005;
vector<int> adj[MAXN], dadj[MAXN];

int N, M, Q, scc[MAXN];

int dfst=0, ncomps, disc[MAXN], lowlink[MAXN], onstack[MAXN], sz[MAXN];

stack<int> comp;

void tarjan(int u) {
	disc[u] = lowlink[u] = ++dfst;
	onstack[u] = true;
	comp.push(u);
	for (int v : adj[u]) {
		if (!disc[v]) {
			tarjan(v);
			lowlink[u] = min(lowlink[u], lowlink[v]);
		} else if (onstack[v]) {
			lowlink[u] = min(lowlink[u], disc[v]);
		}
	}
	if (disc[u] == lowlink[u]) {
		++ncomps;
		while (1) {
			int v = comp.top(); comp.pop();
			scc[v] = ncomps;
			sz[ncomps]++;
			onstack[v] = false;
			if (v==u) break;
		}
	}
}

int dag[MAXN][MAXN];

void compute_dag() {
	for (int u = 1; u <= N; ++u) scc[u] = ncomps-scc[u]+1;
	for (int i = 1; i < ncomps-i+1; ++i) swap(sz[i], sz[ncomps-i+1]);
	for (int u = 1; u <= N; ++u) {
		for (int v : adj[u]) 
			if (scc[u] != scc[v]) dag[scc[u]][scc[v]] = 1;
	for (int u = 1; u <= ncomps; ++u) 
		for (int v = 1; v <= ncomps; ++v) if (dag[u][v]) dadj[u].push_back(v);
}

int d[MAXN][MAXN];

void compute_dist(int dest) {
	d[dest][dest]=0;
	for (int src = dest-1; src; --src) {
		for (int u : dadj[src]) 
			if (d[u][dest]!=-1) d[src][dest] = max(d[src][dest], sz[src]+d[u][dest]);
}


int main() {
 	//~ freopen("data.txt", "r", stdin);
	scanf("%d%d%d", &N, &M, &Q);
	for (int i = 0; i < M; ++i) {
		int u, v; scanf("%d%d", &u, &v);
		adj[u].push_back(v);
	}
	for (int u = 1; u <= N; ++u) 
		if (!disc[u]) tarjan(u);
	compute_dag();
	memset(d, -1, sizeof d);
	for (int i = 1; i <= ncomps; ++i) compute_dist(i);
	while (Q--) {
		int a, b; scanf("%d%d", &a, &b);
		int u = scc[a], v = scc[b];
		if (u==v) {
			printf("Indeterminate\n");
		} else {
			if (d[u][v] != -1) printf("%d %d\n", a, d[u][v]-sz[u]);
			else if (d[v][u] != -1) printf("%d %d\n", b, d[v][u]-sz[v]);
			else printf("Indeterminate\n");
		}
	}
}
