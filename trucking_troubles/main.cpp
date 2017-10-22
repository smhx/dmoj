#include <cstdio>
#include <algorithm>
#include <vector>
#include <functional>
#define MAXN 10005
#define MAXM 100005
#define INF 1000000000
using namespace std;
typedef pair<int, pair<int, int> > edge;

#ifdef ONLINE_JUDGE 
#define getchar() (*_pbuf ? *_pbuf++ : (_buf[fread_unlocked(_pbuf = _buf, 1, 1048576, stdin)] = 0, *_pbuf++))
char _buf[1048577], *_pbuf = _buf;
#endif

int readint() {
	int c, o = 0;
	while ((c = getchar()) < '0');
	do {
		o = o * 10 + (c - '0');
	} while ((c = getchar()) >= '0');
	return o;
}

int N, M, D,isdest[MAXN], visit[MAXN];
edge edges[MAXM];
vector<int> dest, adj[MAXN];

void dfs(int u) {
	if (visit[u]) return;
	if (isdest[u]) --D;
	visit[u] = 1;
	for (size_t i = 0; i < adj[u].size(); ++i) dfs(adj[u][i]);
}

int main() {
// 	freopen("data.txt", "r", stdin);
	N = readint(); M = readint(); D = readint();
	for (int i = 0; i < M; ++i) {
		edges[i].second.first = readint(); edges[i].second.second = readint(); edges[i].first = readint();
	}
	for (int i = 0; i < D; ++i) {
		int d; d = readint(); 
		dest.push_back(d);
		isdest[d] = 1;
	}
	dest.push_back(1);
	sort(edges, edges+M, greater<edge>() );	
	int bound = INF;
	for (int i = 0; i < M; ++i) {
		if (!D) {
			if (bound==INF) printf("ERROR bound is INF\n");
			printf("%d\n", bound);	
			return 0;
		}
		bound = edges[i].first;
		int u = edges[i].second.first, v = edges[i].second.second;
		adj[u].push_back(v);
		adj[v].push_back(u);
		dfs(u);
		dfs(v);
	}
}
