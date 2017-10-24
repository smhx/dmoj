#include <cstdio>
#include <vector>
#include <algorithm>
#define MAXN 100005
#define INF 1000000009

using namespace std;
typedef pair<int, int> ii;

int d[MAXN];
ii pre[MAXN];

bool visit[MAXN];

vector<ii> adj[MAXN];

void dfs(int u, int p, int& x) {
	visit[u] = true;
	if (d[u] > d[x]) x = u;
	for (ii e : adj[u]) {
		int v = e.second, w = e.first;
		if (v != p) {
			d[v]=d[u]+w;
			pre[v] = ii(w, u);
			dfs(v, u, x);
		}
	}
}

int travelTime(int N, int M, int L, int A[], int B[], int T[]) {
	for (int i = 0; i < M; ++i) {
		adj[A[i]].push_back(ii(T[i], B[i]));
		adj[B[i]].push_back(ii(T[i], A[i]));
	}
	int maxdia = 0;
	int h1=-INF, h2=-INF, h3=-INF;
	for (int u = 0; u < N; ++u) {
		if (!visit[u]) {
			int h=INF;
			int v=u, w=u;
			dfs(u, -1, v);
			d[v] = 0;
			pre[v] = ii(0, v);
			dfs(v, -1, w);
			h = INF;
			for (int x = w, plen = 0;;) {
			    h = min(h, max(plen, d[w]-plen));
			    plen += pre[x].first;
			    x = pre[x].second;
			    if (x==v) break;
			}
			if (h >= h1) {
				h3=h2;
				h2=h1;
				h1=h;
			} else if (h >= h2) {
				h3=h2;
				h2=h;
			} else if (h >= h3) {
				h3=h;
			}
			maxdia = max(maxdia, d[w]);
		}
	}

	return max(maxdia, max(L+h1+h2, 2*L+h2+h3));
}

int main() {
	freopen("data.txt", "r", stdin);
	int N, M, L, A[MAXN], B[MAXN], T[MAXN];
	scanf("%d%d%d", &N, &M, &L);
	for (int i = 0; i < M; ++i) {
		scanf("%d%d%d", A+i, B+i, T+i);
	}
	printf("%d\n", travelTime(N, M, L, A, B, T));
}