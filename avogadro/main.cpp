#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
const int maxn = 1e5+5;
bool visit[maxn];

int n, a[2][maxn], p[maxn], pos[maxn];

vector<int> scc[2][maxn];
int compid[2][maxn], ncomp[2];

int lo[maxn], disc[maxn], onstack[maxn], dfst=0;
stack<int> s;

void dfs(int u, int i) {
	lo[u]=disc[u]=++dfst;
	s.push(u);
	onstack[u] = true;
	int v = a[i][pos[u]];
	if (!disc[v]){
		dfs(v,i);
		lo[u] = min(lo[u], lo[v]);
	} else if (onstack[v]) lo[u] = min(lo[u], disc[v]);
	if (lo[u]==disc[u]) {
		++ncomp[i];
		int v;
		do {
			v = s.top(); s.pop();
			onstack[v] = false;
			compid[i][v] = ncomp[i];
			scc[i][ncomp[i]].push_back(v);
		} while (v!=u);
	}
}

void dfsreset() {
	dfst=0;
	memset(lo, 0, sizeof lo); 
	memset(disc, 0, sizeof disc); 
}

int sink[2][maxn];

void find_sinks(int i) {
	for (int c = 1; c <= ncomp[i]; ++c) sink[i][c] = 1;
	for (int u = 1; u <= n; ++u) {
		int v = a[i][pos[u]];
		if (compid[i][u] != compid[i][v]) sink[i][compid[i][u]] = 0;
	}
}

bool removed[maxn];

void remove(int u) {
	if (removed[u]) return;
	removed[u]= true;
	for (int v : scc[0][compid[0][u]]) remove(v);
	for (int v : scc[1][compid[1][u]]) remove(v);
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", p+i);
	for (int r = 0; r < 2; ++r) 
		for (int i = 1; i <= n; ++i) scanf("%d", &a[r][i]); 
	for (int i = 1; i <= n; ++i) pos[p[i]] = i;
	for (int i = 1; i <= n; ++i) if (!disc[i]) dfs(i, 0);
	dfsreset();
	for (int i = 1; i <= n; ++i) if (!disc[i]) dfs(i, 1);
	find_sinks(0); find_sinks(1);
	for (int u = 1; u <= n; ++u) {
		if (!removed[u]) {
			int c0 = compid[0][u], c1 = compid[1][u];
			if (!sink[0][c0] || !sink[1][c1]) remove(u); 
		}
	}
	int cnt = 0;
	for (int i = 1; i <= n; ++i) if (removed[i]) ++cnt;
	printf("%d\n", cnt);
}