#include <cstdio>
#include <queue>
#define MAXN 102
#define MAXM 102
#define INF 1000000000

using namespace std;

int N, M, csgirls=0, cap[MAXN][MAXM], pre[MAXN+MAXM];
bool visit[MAXN+MAXM], flag[MAXN+MAXM];

void augment() { 
	// add nodes 0 and N+M+1
	for (int a = 1; a <= N; ++a) 
		if (flag[a]) cap[0][a] = 1;

	for (int b = 1; b <= M; ++b) 
		if (flag[b+N]) cap[b+N][N+M+1] = 1;
}

int bfs() {
	memset(pre, -1, sizeof pre);
	memset(visit, 0, sizeof visit);

	queue<int> q;
	q.push(0);
	visit[0] = true;

	while (!q.empty() && !visit[N+M+1]) {
		int u = q.front(); q.pop();
		for (int v = 0; v <= N+M+1; ++v) {
			if (cap[u][v] && !visit[v]) {
				visit[v] = true;
				q.push(v);
				pre[v] = u;
			}
		}
	}

	int u = N+M+1, pathcap = INF;
	while (pre[u]!=-1) {
		int v = pre[u];
		if (cap[v][u] < pathcap) pathcap = cap[v][u];
		u = v;
	}

	u = N+M+1;
	while (pre[u]!=-1) {
		int v = pre[u];
		cap[v][u] -= pathcap;
		cap[u][v] += pathcap;
		u = v;
	}

	return pathcap==INF ? 0 : pathcap;
}

int match() {
	int res = 0;
	while (true) {
		int pathcap = bfs();
		if (pathcap==0) break;
		else res += pathcap;
	}
	return res;
}

int main() {
	// freopen("data.txt", "r", stdin);
	scanf("%d%d", &N, &M);
	for (int i = 1, n, b; i <= N; ++i) {
		scanf("%d", &n);
		if (i==1) csgirls += n;
		while (n--) {
			scanf("%d", &b);
			if (i==1) flag[b+N]=true;
			else if (flag[b+N]) {
				flag[i] = true;
				cap[i][b+N]=1;
			}
		}
	}

	augment();
	printf("%d\n", csgirls-match() );
}
