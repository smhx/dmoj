#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX_SQRT = 40;
int N, SQRT;

bool adj[MAX_SQRT][MAX_SQRT][MAX_SQRT], visit[MAX_SQRT];
int gadj[MAX_SQRT][MAX_SQRT];

bool dfs(int g, int u, int v) {
	visit[u] = true;
	if (u==v) return true;
	for (int w = 0; w < SQRT; ++w) {
		if (adj[g][u][w] && !visit[w]) {
			if (dfs(g, w, v)) return true;
		}
	}
	return false;
}

bool gdfs(int u, int v) {
	visit[u] = true;
	if(u==v) return true;

	for (int w = 0; w < SQRT; ++w) {
		if (gadj[u][w] && !visit[w]) {
			if (gdfs(w, v)) return true;
		}
	}
	return false;
}

void initialize(int n) {
	N = n;

	for(SQRT=1; SQRT*SQRT < N; ++SQRT);

	printf("SQRT = %d\n", SQRT);

	for (int i = 0; i < SQRT; ++i) {
		for (int j = 0; j < SQRT; ++j) {
			for (int k = 0; k < SQRT; ++k) {
				adj[i][j][k] = true;
			}
			gadj[i][j] = min(SQRT, N-SQRT*(i-1) ) * min(SQRT, N-SQRT*(j-1) );
		}
	}
}

int hasEdge(int u, int v) {
	if (u/SQRT == v/SQRT) {
		memset(visit, 0, sizeof visit);
		adj[u/SQRT][u%SQRT][v%SQRT] = false;
		adj[v/SQRT][v%SQRT][u%SQRT] = false;

		if ( dfs(u/SQRT, u, v) ) {
			return 0;
		} 
		printf("u=%d, v=%d, group = %d not connected\n", u, v, u/SQRT);
		adj[u/SQRT][u%SQRT][v%SQRT] = true;
		adj[v/SQRT][v%SQRT][u%SQRT] = true;
		return 1;
	} 

	int i = u/SQRT, j = v/SQRT;
	if (gadj[i][j]>1) {
		gadj[i][j]--;
		return 0;
	}
	memset(visit, 0, sizeof visit);

	gadj[i][j] = gadj[j][i] = 0;
	if (gdfs(i,j)) {
		return 0;
	} 

	gadj[i][j] = gadj[j][i] = 1;
	return 1;
}

int main() {
	int n; scanf("%d", &n);
	initialize(n);
	for (int i = 0; i < n*(n-1)/2; ++i) {
		int u,v; scanf("%d%d", &u, &v);
		printf("%d\n", hasEdge(u,v));
	}
}