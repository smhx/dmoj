#include <cstdio>
#include <vector>
#include <algorithm>
#define MAXM 100005
#define MAXN 50005
#define LOG 22
#define INF 1000000000

using namespace std;
typedef pair<int, int> ii;

struct edge {
	int u, v, w;
	bool operator<(const edge& e) const {return w<e.w;}
} edges[MAXM];

int N, M, ds[MAXM], intree[MAXM], p[MAXN][LOG], wt[MAXN][LOG], h[MAXN];

int find(int x) {return x==ds[x] ? x : (ds[x] = find(ds[x]));}

vector<ii> adj[MAXN];

void dfs(int u) {
	for (ii pair : adj[u]) {
		int v = pair.second, w = pair.first;
		if (v==p[u][0]) continue;
		p[v][0] = u;
		h[v] = 1+h[u];
		wt[v][0] = w; // weight from v to p[v][j]
		dfs(v);
	}
}

int anc(int u, int i) {
    int v = u;
    for (int j = LOG-1; j >= 0;  --j) 
        if ((i>>j)&1) v = p[v][j];
    printf("%d\n", v);
    return v;
}

int lca(int u, int v) { // returns (lca, dist)
    if (h[u] < h[v]) v = anc(v, h[v]-h[u]);
    else if (h[u] > h[v]) u = anc(u, h[u]-h[v]);
    int d = 0; // d is the distance up to lca(u, v)
    if (u==v) return u;
    for (int i = LOG-1; i >= 0 && u!=v; --i) {
        //should you add the i'th bit to d?
        if (p[u][i] && p[v][i] && p[p[u][i]][0] != p[p[v][i]][0]) {
            d |= 1 << i;
            u = p[u][i];
            v = p[v][i];
        } 
    }
    return p[u][0]; // dist is d+1
}

int maxw(int u, int d) {
	int v = u, toret = 0;
	for (int j = LOG-1; j >= 0; --j) {
		if ( (d>>j)&1 ) {
			toret = max(toret, wt[v][j]);
			v=p[v][j];
		}
	}
	return toret;
}

int main() {
	// freopen("data.txt", "r", stdin);
	scanf("%d%d", &N, &M);
	if (N==1) printf("-1\n");
	for (int i = 0; i < M; ++i) scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].w);

	// Standard MST

	sort(edges, edges+M);

	for (int i = 1; i <= N; ++i) ds[i] = i;

	int tree = 0, tidx = 0, treesum=0;

	while (tree < N-1 && tidx < M) {
		int x = edges[tidx].u, y = edges[tidx].v;
		int xr = find(x), yr = find(y);
		if (xr != yr) {
			ds[yr] = xr;
			intree[tidx] = 1;
			++tree;
			treesum += edges[tidx].w;
		}
		++tidx;
	}

	if (tree != N-1) {
		printf("-1\n");
		return 0;
	}

	// Construct MST adj list

	for (int e = 0; e < M; ++e) {
		if (intree[e]) {
			int u = edges[e].u, v = edges[e].v, w = edges[e].w;
			adj[u].push_back(ii(w, v));
			adj[v].push_back(ii(w, u));
		}
	}

	// label with parent, height, and weights
	dfs(1);
	for (int k = 1; 1<<k <= N; ++k) {
		for (int u = 1; u <= N; ++u) {
			if (!adj[u].empty()) {
				if (p[u][k-1]) {
					p[u][k] = p[p[u][k-1]][k-1];
					wt[u][k] = max(wt[u][k-1], wt[p[u][k-1]][k-1]);
				}
			}
		}
	}

	int sum = INF;

	for (int e = 0; e < M; ++e) {
		if (!intree[e]) {
			int u = edges[e].u, v = edges[e].v, w = edges[e].w;
			int q = lca(u, v);
			int mwt = max(maxw(u, h[u]-h[q]), maxw(v, h[v]-h[q]));
			if (mwt < w) sum = min(sum, treesum+w-mwt);
		}
	}
	printf("%d\n", sum==INF ? -1 : sum);
}





