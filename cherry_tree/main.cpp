#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
const ll MAXN = 10005;
ll N, K, C, c[MAXN], cherries[MAXN], brsum[MAXN], cnt=0;
vector<pll> adj[MAXN];

void dfs(ll u, ll p, ll w) {
	cherries[u]=c[u];
	brsum[u]=w;
	for (pll e : adj[u]) {
		if (e.second != p) {
			dfs(e.second, u, e.first);
			cherries[u]+=cherries[e.second];
			brsum[u]+=brsum[e.second];
		}
	}
	if (u!=1 && cherries[u]>=C && brsum[u] <= K) ++cnt;
}

int main() {
	freopen("data.txt", "r", stdin);
	cin >> N >> C >> K;
	for (int i = 1; i <= N; ++i) cin >> c[i];
	for (int i = 1, a, b, w; i < N; ++i) {
		cin >> a >> b >> w; 
		adj[a].push_back({w,b});
		adj[b].push_back({w,a});
	}
	dfs(1, 0, 0);
	cout << cnt << endl;
}