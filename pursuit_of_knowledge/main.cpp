/*input
7 6 8
2 3
5 7
1 7
3 4
4 3
1 2
3
1 7
4 2
1 4
*/
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

const int MAX = 1003;

int N, M, T, Q, d[MAX][MAX];

vector<int> adj[MAX];


int main() {
	scanf("%d%d%d", &N, &M, &T);

	for (int i = 0, a, b; i < M; ++i) {
		scanf("%d%d", &a, &b);
		adj[a].push_back(b);
	}

	memset(d, -1, sizeof d);
	
	for (int src = 1; src <= N; ++src) {
		queue<int> q;
		q.push(src);
		d[src][src] = 0;
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int v : adj[u]) {
				if (d[src][v]==-1) {
					d[src][v] = 1+d[src][u];
					q.push(v);
				}
			}
		}
	}

	scanf("%d", &Q);
	while (Q--) {
		int a,b; scanf("%d%d", &a, &b);
		if (d[a][b] == -1){
			printf("Not enough hallways!\n");
		} else {
			printf("%d\n", T * d[a][b]);
		}
	}
}