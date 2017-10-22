
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
#define MAXN 5003
#define INF 1000000000
using namespace std;

int N, S, leafcnt[MAXN], K, d[MAXN], f[MAXN][MAXN];
vector<int> adj[MAXN], tmpadj[MAXN];

int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d%d", &N, &S);
	for (int i = 0, a, b; i < N-1; ++i) {
		scanf("%d%d", &a, &b);
		adj[b].push_back(a);
		adj[a].push_back(b);
	}

	for (int k = 0; k < N; ++k) {
		for (int u = 1; u <= N; ++u) 
			if (adj[u].size()==1) ++leafcnt[k];

		for (int u = 1; u <= N; ++u) {
			if (adj[u].size() > 1) {
				for (int v : adj[u]) {
					if (adj[v].size()>1)
						tmpadj[u].push_back(v);
				}
			}
		}

		for (int u = 1; u <= N; ++u) {
			adj[u] = vector<int>(tmpadj[u]);
			tmpadj[u].clear();
		}
	}

	for (int k = 0; k < N; ++k) {
		printf("leafcnt[%d] = %d\n", k, leafcnt[k]);
	}
	// let f[k][s] be the minimum d for T[k] and s soldiers 
	for (int s = 0; s <= S; ++s) {

		printf("s = %d\n", s);
		int d = 0;
		for (int k = N-1; k >= 0; --k) {
			if (s==0) {
				f[s][k] = INF;
				continue;
			}
			// printf("  k = %d, d = %d\n", k, d);
			for (; d < N; ++d) {
				printf("    d = %d, new s = %d, mid k = %d, hi k = %d\n", d, s-leafcnt[k+d], k+d, k+2*d+1);
				// if (s==0 && d==0 && leafcnt[k+d]==1) break;
				if (s-leafcnt[k+d] < 0) continue;
				if ( f[s-leafcnt[k+d]][k+2*d+1] <= d) break;
			}
			f[s][k] = d;
			printf("  setting f[s=%d][k=%d]=%d\n", s, k, f[s][k]);
		}
	}

	printf("%d\n", f[S][0]);
}


