#include <cstdio>
#include <vector>
using namespace std;

const int maxn = 100005;

vector<int> adj[maxn];
int n, r, deg[maxn];

int dfst=0, disc[maxn], low[maxn], p[maxn];	
void tarjan(int u){
	disc[u]=low[u]=++dfst;
	for (int v : adj[u]) {
		if (!disc[v]) {
			p[v] = u;
			tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if (v!=p[u]){
			low[u] = min(low[u], disc[v]);
		}
	}
}

int main() {
	freopen("data.txt", "r", stdin);
	int n,r;
	scanf("%d%d", &n, &r);
	for (int i = 0, u, v; i < r; ++i) {
		scanf("%d%d", &u, &v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	tarjan(1);
	for (int u = 1; u <= n; ++u) 
		for (int v : adj[u]) 
			if (low[u]!=low[v]) ++deg[low[u]];
	int cnt = 0;
	for (int u = 1; u <= n; ++u) if (deg[u]==1) ++cnt;
	if (cnt%2==0) printf("%d\n", cnt/2);
	else printf("%d\n", cnt/2+1);
}