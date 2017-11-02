#include <cstdio>
#include <vector>
using namespace std;
const int MAXN = 200005;
int N, color[MAXN], cnt[MAXN][2];
bool onstack[MAXN];
vector<int> bad, adj[MAXN];


int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d", &N);
	for (int i = 0, p, x, y; i < 5; ++i) {
		scanf("%d", &p);
		while (p--) {
			scanf("%d%d", &x, &y);
			adj[x].push_back(y);
			adj[y].push_back(x);
		}
	}

	for (int u = 1; u <= N; ++u) {
		cnt[u][0] = cnt[u][1] = 0;
		for (int v : adj[u]) ++cnt[u][color[v]];
		
		if (cnt[u][color[u]] > 2) {
			bad.push_back(u);
			onstack[u] = true;
		}
	}

	while (!bad.empty()) {
		int u = bad.back(); bad.pop_back();

		onstack[u] = false;

		if (cnt[u][color[u]] < 3) continue;


		for (int v : adj[u]) {
			--cnt[v][color[u]];
			++cnt[v][color[u]^1];
			if (cnt[v][color[v]] > 2 && !onstack[v]) {
				bad.push_back(v);
				onstack[v] = true;
			}
		}

		color[u] ^= 1;
	}

	for (int u = 1; u <= N; ++u) printf("%c", color[u] ? 'A' : 'B');
	
	printf("\n");
}
