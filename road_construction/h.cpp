#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>
#include <cstring>
using namespace std;
typedef pair<int,int> ii;
const int maxn = 1005, inf = 1000000000;
int n, r;

vector<int> adj[maxn], bctree[maxn], comp[maxn];

int dfst = 0, nblocks=0, nart=0, disc[maxn], low[maxn], p[maxn], mem[2*maxn];
stack<ii> dfstack;

void processblock(ii e) {
	++nblocks;
	printf("block %d: ", nblocks);
	while (1) {
		ii f = dfstack.top();
		dfstack.pop();
		if (comp[f.first].empty()) comp[f.first].push_back(nblocks);
		else if (comp[f.first].back() != nblocks) comp[f.first].push_back(nblocks);
		if (comp[f.second].empty()) comp[f.second].push_back(nblocks);
		else if (comp[f.second].back() != nblocks)comp[f.second].push_back(nblocks);
		printf("(%d, %d) ", f.first, f.second);
		if(f==e) break;
	} 
	printf("\n");
}

void dfs(int u) {
	disc[u]=low[u]=++dfst;
	for (int v : adj[u]) {
		if (!disc[v]) {
			p[v] = u;
			dfstack.push({u,v});
			dfs(v);
			if (low[v] >= disc[u]) processblock({u,v});
			low[u] = min(low[u], low[v]);
		} else if (v != p[u] && disc[v] < disc[u]) {
			low[u] = min(low[u], disc[v]);
			dfstack.push({u,v});
		}
	}
}

void computebct() {
	printf("nblocks = %d\n", nblocks);

	for (int u = 1; u <= n; ++u) {
		printf("comp[%d]: ", u);
		for (int x : comp[u]) printf("%d ", x);
		printf("\n");
	}


	for (int u = 1; u <= n; ++u) {

		if (comp[u].size()>1) {
			++nart;
			printf("artnode[%d] = %d\n", u, nart+nblocks);
			for (int c : comp[u]) {
				bctree[c].push_back(nart+nblocks);
				bctree[nart+nblocks].push_back(c);
			}
		}
	}
	printf("nart = %d\n", nart);
	for (int u = 1; u <= nart + nblocks; ++u) {
		sort(bctree[u].begin(), bctree[u].end());
		bctree[u].erase(unique(bctree[u].begin(), bctree[u].end()), bctree[u].end());
		printf("bctree[%d]: ", u);
		for (int x : bctree[u]) printf("%d ", x);
		printf("\n");
	}
}

int dp(int,int);

int dfs2(int u, int p, int sum, int hang) {
	printf("u=%d, p=%d, sum = %d, hang = %d\n", u,p,sum, hang);
	if (bctree[u].size()==1) return sum+hang;

	if (bctree[u].size()==2) {
		int v = bctree[u][0]!=p ? bctree[u][0] : bctree[u][1];
		printf("cont to v =%d\n", v);

		return dfs2(v, u, sum, hang);
	}

	int ans = inf;
	int totsum = 0;
	for (int v : bctree[u]) if (v!=p) totsum += dp(v, u);
	for (int v : bctree[u]) {
		if (v!=p) {
			int tmpsum = sum + totsum - dp(v,u);
			int tmphang = hang + bctree[u].size()-2;
			ans = min(ans, dfs2(v, u, tmpsum, tmphang));
		}
	}
	return ans;
}

int dp(int u, int par) {
	if (mem[u]!=-1) return mem[u];
	// if (bctree[u].size()==1) return 0;
	return mem[u]=dfs2(u, par, 0, 0);
}

int solve() {
	if (nblocks+nart == 1) return 0;

	if (nblocks+nart == 2) {
		printf("ERROR bctsize = 2\n");
		return -1;
	}
	memset(mem, -1, sizeof mem);
	int root = 1;
	if (bctree[1].size()==1) root = bctree[1][0];
	int ans = bctree[root].size()-1;
	for (int v : bctree[root]) {
		ans += dp(v, root);
	}
	return ans;
}

int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d%d", &n, &r);
	for (int i = 0, v, w; i < r; ++i) {
		scanf("%d%d", &v, &w);
		adj[v].push_back(w);
		adj[w].push_back(v);
	}
	dfs(1);
	computebct();
	printf("finished computing\n");
	printf("%d\n", solve());
}