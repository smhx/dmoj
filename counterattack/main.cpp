#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
const int INF = 1e9;
int n, m, d1[5005], d2[5005];
vector<ii> adj[5005];

void pfs() {

	for (int i = 1; i <= n; ++i) {
		d1[i] = INF;
		d2[i] = INF+1;
	}

	priority_queue<ii, vector<ii>, greater<ii>> pq;
	pq.push({0, 1});
	d1[1] = 0;
	while (!pq.empty()) {
		int d, u; tie(d, u) = pq.top(); pq.pop();
		assert(d2[u] > d1[u]);
		if (d >= d2[u]) continue;
		else if (d > d1[u]) {
			d2[u] = d;
		} else if (d<d1[u]) {
			d2[u] = d1[u];
			d1[u] = d;
		}
		for (auto x : adj[u]) {
			pq.push({x.first+d, x.second});
		}
	}
}

int main() {
	// freopen("data.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; ++i) {
		int a, b, w;
		scanf("%d%d%d", &a, &b, &w);
		adj[a].push_back({w, b});
		adj[b].push_back({w, a});
	}
	pfs();
	printf("%d\n", d2[n]);
}