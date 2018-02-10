#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
typedef long long ll;
const int MAXN = 10005;
int N, M, color[MAXN];
ll mem[MAXN];
const ll MOD = 1e9;
vector<int> adj[MAXN];

bool cycle = false;

void dfs(int u) {
	color[u]=2;
	for (int v : adj[u]) {
		if (color[v]==2) cycle = true;
		else if (!color[v]) dfs(v);
	}
	color[u]=1;
}

bool zero = false;
ll cnt(int u) {
	if (mem[u]!=-1LL) return mem[u];
	if (u==2) {return mem[u]=1LL;}
	mem[u] = 0LL;
	for (int v : adj[u]) {
		mem[u] += cnt(v);
		if (mem[u]>= MOD) zero = true;
		mem[u] %= MOD;
	}
	return mem[u];
}

int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d%d", &N, &M);
	for (int i = 0, u, v; i < M; ++i) {
		scanf("%d%d", &u, &v);
		adj[u].push_back(v);
	}
	dfs(1);
	if (cycle){
		printf("inf\n");
		return 0;
	}
	for (int i = 0; i < MAXN; ++i) mem[i] = -1LL;
	ll ans = cnt(1);
	
	if (!zero) printf("%lld\n", ans);
	else printf("%09lld\n", ans);
}