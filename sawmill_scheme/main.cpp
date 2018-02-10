#include <cstdio>
#include <vector>

const int MAXN = 1e6+5;
int N, M;

std::vector<int> adj[MAXN];

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 0; i < M; ++i) {
		int u, v; scanf("%d%d", &u, &v);
		adj[u].push_back(v);
	}
}