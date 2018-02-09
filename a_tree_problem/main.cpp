#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> ii;

const int MAXN = 5e4+5;
vector<ii> adj[MAXN], ch[MAXN];

int N, dfst = 0, disc[MAXN], finish[MAXN], p[MAXN], c[MAXN];

list<int> s;

void init(int u) {
	disc[u] = ++dfst;
	for (ii e : adj[u]) {
		if (e.second != p[u]) {
			p[e.second] = u;
			c[e.second] = e.first;
			ch[u].push_back(e);
			init(e.second);
		}
	}
	finish[u] = ++dfst;
}

void solve(int u) {
	for (ii e : ch[u]) {
		if (e.first == c[u]) {
			for (auto it = s.begin(); it != s.end(); ) {
				int x = *it;
				if ( !(disc[u] <= disc[x] && disc[x] <= finish[u]) || (disc[e.second] <= disc[x] && disc[x] <= finish[e.second] )) {
					it = s.erase(it);
				} else {
					++it;
				}
			}
		}
	}

	for (int i = 0; i < ch[u].size();) {
		int j = i;
		while (j+1 < ch[u].size() && ch[u][i].first == ch[u][j+1].first) ++j;
		if (i != j) {	
			int start = disc[ch[u][i].second], end = finish[ch[u][j].second];
			for (auto it = s.begin(); it != s.end(); ) {
				int x = *it;
				if (start <= disc[x] && finish[x] <= end) {
					it = s.erase(it);
				} else {
					++it;
				}
			}
		}
		i = j+1;
	}

	for (ii e : ch[u]) {
		
		solve(e.second);
		
	}
}

int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d", &N);
	for (int i = 1; i < N; ++i) {
		int a, b, c; scanf("%d%d%d", &a, &b, &c);
		adj[a].push_back({c, b});
		adj[b].push_back({c, a});
	}
	for (int u = 1; u <= N; ++u) sort(adj[u].begin(), adj[u].end());
	init(1);
	for (int u = 1; u <= N; ++u) s.push_back(u);
	solve(1);
	printf("%lu\n", s.size());
	for (int x : s) printf("%d\n", x);
}