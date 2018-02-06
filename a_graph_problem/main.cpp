#include <bits/stdc++.h>
using namespace std;

const int MAX = 5005;

struct edge {int from, to, t1, t2;} e[MAX];

int N, M, K, S, T, cnt=0, visit[MAX];
vector<int> adj[MAX], mp;

bool dfs(int u, int k) {
	visit[u] = 1;
	if (u==T) return true;
	for (int id : adj[u]) {
		int v = e[id].to;
		if (!visit[v] && e[id].t1 <= k && k <= e[id].t2) {
			if (dfs(v, k)) return true;
		}
	}
	return false;
}

int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d%d%d%d%d", &N, &M, &K, &S, &T);
	for (int i = 0; i < M; ++i) {
		scanf("%d%d%d%d", &e[i].from, &e[i].to, &e[i].t1, &e[i].t2);
		mp.push_back(e[i].t1); mp.push_back(e[i].t2+1);

		adj[e[i].from].push_back(i);
		// adj[e[i].to].push_back(i);
	}

	sort(mp.begin(), mp.end());
	mp.erase(unique(mp.begin(), mp.end()), mp.end());

	int state = -1;

	for (int k = 0; k < mp.size(); ++k) {
		memset(visit, 0, sizeof visit);
		if (!dfs(S, mp[k])) {
			if (state != -1) cnt += mp[k]-state;
			state = -1;
		} else {
			if (state==-1) state = mp[k];
		}
	}

	printf("%d\n", cnt);
}