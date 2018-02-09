#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> ii;

const int maxn = 5e4+4, up=1, dead=2;
vector<ii> adj[maxn];

int n, p[maxn], state[maxn];

unordered_set<int> colours;

void dfs(int u, int par, int col, bool d) {

	printf("dfs(%d, %d, %d, %d)\n", u, par, col, d);

	if (d) state[u] |= dead;

	if (!d) {
		colours.clear();
		for (ii e : adj[u]) {
			if (e.second != par) {
				if (colours.find(e.first) != colours.end()) {d = true; break;}
				colours.insert(e.first);
			}
		}
	}

	for (ii e : adj[u]) {
		if (e.second != par) {
			if (e.first == col) {
				state[e.second] |= dead;
				state[u] |= up;
			}
		}
	}

	int active = -1;

	for (ii e : adj[u]) {
		int v = e.second;
		if (v != par) {
			// printf("	u = %d, v = %d\n", u, v);
			dfs(v, u, e.first, d);
			if (state[v] & up) {
				state[u] |= up;
				state[u] |= dead;
				// printf("	from u = %d, v = %d, v is up, state u now %d\n", u, v, state[u]);

				if (active == -1) active = v; // v, you're still alive!
				else active = -2; // everyone is dead
			}
		}
	}

	if (active == -2) {
		for (ii e : adj[u]) state[e.second] |= dead;
	} else if (active != -1) {
		for (ii e : adj[u]) if (e.second != active) state[e.second] |= dead;
	}
	
}


int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d", &n);
	for (int i = 1, a, b, c; i < n; ++i) {
		scanf("%d%d%d", &a, &b, &c);
		adj[a].push_back({c, b});
		adj[b].push_back({c, a});
	}
	dfs(1, 0, 0, 0);
	if (state[1] & up) return !printf("0\n");
	queue<int> q;
	for (int i = 1; i <= n; ++i) {
		if ((state[i]&dead) == 0) {
			q.push(i);
		}
	}
	printf("%lu\n", q.size());
	for (; !q.empty(); q.pop()) printf("%d\n", q.front());
}