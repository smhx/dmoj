#include <cstdio>
#include <algorithm>
using namespace std;
int n, high=-1, numcyc=0, numround=0, cycsize[10005], adj[10005], visited[10005], ord[10005], cyc[10005], rnd[10005];

void dfs(int u) {
	int v = u, cycle=0; ++numround;
	while (1) {
		if (visited[v] && rnd[v]==numround) {
			cycle=1;
			break;
		} else if (visited[v]) break;
		visited[v]=1; 
		rnd[v]=numround;
		if (adj[v]==0) break;
		v=adj[v];
	}
	if (cycle) {
		++numcyc;
		int w = adj[v];
		cycsize[numcyc]=0;
		while (1) {
			cyc[w]=numcyc; ++cycsize[numcyc];
			if (w==v) {
				ord[w]=0; break;
			}
			else {
				ord[w]=cycsize[numcyc];
				w=adj[w];
			}
		}
	} 
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		adj[x]=y;
		high = max(high, max(x, y));
	}
	for (int u=1; u<=high; ++u) {
		if (!visited[u]) dfs(u);
	}
	while (1) {
		int x, y;
		scanf("%d%d", &x, &y);
		if (x==0 && y==0) break;
		if (cyc[x]!=cyc[y] || cyc[x] == 0) {
			printf("No\n");
		} else {
			int sep = (ord[y] > ord[x]) ? ord[y]-ord[x] : cycsize[cyc[x]]+ord[y]-ord[x];
			printf("Yes %d\n", sep-1);
		}
	}
}

