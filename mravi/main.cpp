#include <cstdio>
#include <vector>
#include <cmath>
#define MAXN 1003
using namespace std;

struct E {int v, frac, pow;};
int N, K[MAXN];
vector<E> adj[MAXN]; 

double dfs(int u, int p) {
	if (K[u]!=-1) return double(K[u]);
	double d = 0.0;
	for (E e : adj[u]) {
		if (e.v != p) {
			double vd = dfs(e.v, u);
			if (e.pow) vd = 100.0/double(e.frac) * min(vd, sqrt(vd));
			else vd = 100.0/double(e.frac) * vd;
			d = max(d, vd);
		}
	}
	return d;
}

int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d", &N);
	for (int i = 0, A, B, X, T; i < N-1; ++i) {
		scanf("%d%d%d%d", &A, &B, &X, &T);
		adj[A].push_back({B, X, T});
		adj[B].push_back({A, X, T});
	}
	for (int i = 1; i <= N; ++i) scanf("%d", K+i);
 	printf("%lf\n", dfs(1, 0) );
}