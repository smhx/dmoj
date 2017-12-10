#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
typedef long long ll;

typedef pair<ll,int> pli;
const int MAXN = 100005, LOG = 20;
const ll INF = 10000000000000LL;

int N, p[MAXN];
ll dist[MAXN], cost[MAXN], c[MAXN], d[MAXN];

// sparse tables
int minC[MAXN][LOG], anc[MAXN][LOG];

int dfsTime=0, dfsPlanet[MAXN];
vector<pli> back[MAXN];

void dfs(int u) {
	dfsPlanet[dfsTime++] = u;
	for (pli e : back[u]) {
		dist[e.second] = dist[u]+ e.first;
		dfs(e.second);
	}
}

void build() {
	c[N] = INF; // sentinel
	for (int u = 1; u < N; ++u) {
		anc[u][0] = p[u];
		if (c[u] <= c[p[u]]) minC[u][0] = u;
		else minC[u][0] = p[u];
	}
	for (int k = 1; k < LOG; ++k) {
		for (int u = 1; u < N; ++u) {
			anc[u][k] = anc[anc[u][k-1]][k-1]; // correct
			int a = minC[u][k-1]; 
			int b = minC[anc[u][k-1]][k-1]; 
			if (c[a] <= c[b]) minC[u][k] = a;
			else minC[u][k] = b;
		}
	}
}

int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d", &N);
	for (int i = 1; i < N; ++i) {
		scanf("%d%lld%lld", p+i, d+i, c+i);
		back[p[i]].push_back({d[i], i});
	}
	p[N] = N;
	dfs(N);
	build();
	for (int i = 1; i < N; ++i) {
		int u = dfsPlanet[i];
		int v = u;
		for (int k = LOG-1; k >= 0; --k) {
			if (anc[v][k]!=0) {
				if (c[minC[v][k]]>=c[u]) {
					v = anc[v][k];
				}
			}
		}
		v = p[v];
		cost[u] = (dist[u]-dist[v])*c[u] + cost[v];
	}

	for (int u = 1; u < N; ++u) {
		printf("%lld\n", cost[u]);
	}
}