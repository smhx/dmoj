#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>
#include <cstdlib>
#define MAXN 1605
#define INF 1000000000
using namespace std;
typedef pair<int, int> ii;
typedef pair<ii, ii> i4;
int N, E, S;

vector<ii> adj[MAXN];

priority_queue<i4, vector<i4>, greater<i4> > pq;

int traverse(int src, int dest) {
    pq.push(i4(ii(0, S), ii(-1, src) ) );
    while (!pq.empty()) {
        i4 f = pq.top(); pq.pop();
        int u = f.second.second, pre = f.second.first, d = f.first.first, t = f.first.second;
        if (u==dest) return d;
        for (auto pair : adj[u]) {
            int v = pair.second, w = pair.first;
            if (w > t || v==pre) continue;
            ii cur;
            if (w > 0) cur = ii(d+w, t-w);
            else cur = ii(d-w, t);
            pq.push(i4(ii(cur.first, cur.second), ii(u, v) ));
        }
    }
    return -1;
}

int main() {
	// freopen("data.txt", "r", stdin);
	scanf("%d%d%d", &S, &N, &E);
	for (int i = 0; i < E; ++i) {
		int s, t, d, u;
		scanf("%d%d%d%d", &s, &t, &d, &u);
		if (!u) d*=-1; // d > 0 IFF above ground
		adj[s].push_back(ii(d, t));
		adj[t].push_back(ii(d, s));	
	}
	int t = traverse(N-1, 0);
	printf("%d\n", t);
}