/*input
6 5
1 2
2 3
3 4
4 6
4 5
1
5
*/
#include <cstdio>	
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int MAX_N = 105;
const int MAX_M = 40;
const int INF = 1000000000;

int N, M, W, antd[MAX_N], d[MAX_N], dp[MAX_M][MAX_N];
vector<int> adj[MAX_N];

void bfs(int x) {
	memset(d, -1, sizeof d);
	queue<int> q;
	q.push(x);
	d[x] = 0;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		if (d[u] < antd[u]) antd[u] = d[u];
		for (int v : adj[u]) {
			if (d[v]==-1) {
				d[v] = 1+d[u];
				q.push(v);
			}
		}
	}
}

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 0, a, b; i < M; ++i) {
		scanf("%d%d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	for (int i = 1; i <= N; ++i) antd[i] = INF;

	scanf("%d", &W);

	for (int i = 0, x; i < W; ++i) {
		scanf("%d", &x);
		bfs(x);
	}


	for (int t = MAX_M-1; t >= 0; --t) {
		for (int u = 1; u <= N; ++u) {
			if (t >= 4 * antd[u]) dp[t][u] = INF;
			else if (u==N) dp[t][u] = 0;
			else {
				dp[t][u] = INF;
				for (int v : adj[u]) 
					if (dp[t+1][v] < dp[t][u]) dp[t][u] = 1+dp[t+1][v];
			}
		}
	}

	printf("%d\n", dp[0][1]!=INF ? dp[0][1] : -1);
}


