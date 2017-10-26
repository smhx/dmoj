#include <cstdio>
#include <vector>
#include <algorithm>
#define MAXN 100005
#define INF 1000000000000000LL
using namespace std;
typedef long long ll;
typedef pair<ll, int> E;
int N, M, Q;
bool visit[MAXN];
ll h, r1, r2,d[MAXN];
vector<E> adj[MAXN];

E pre[MAXN];

void dfs(int u, int p, int& x) {
	visit[u] = true;
	if (d[u] > d[x]) x = u;
	for (E e : adj[u]) {
		int v = e.second, w = e.first;
		if (v != p) {
			pre[v] = {w, u};
			d[v] = w+d[u];
			dfs(v,u, x);
		}
	}
}

int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d%d%d", &N, &M, &Q);
	for (int i = 0, u, v, l; i < M; ++i){
		scanf("%d%d%d", &u, &v, &l);
		adj[u].push_back({l, v});
		adj[v].push_back({l, u});
	}

	for (int u = 1; u <= N; ++u) {
		if (!visit[u]) {
			int v=u, w;
			dfs(u, -1, v);
			d[v] = 0;
			pre[v] = {v, 0};
			w = v;
			dfs(v, -1, w);
			if (Q==1) h += 1+d[w];
			else {
				ll r = INF, psum=0;
				int x = w;
				while (1) {
					r = min(r, max(psum, d[w]-psum));
					if (x==v) break;
					psum += pre[x].first;
					x = pre[x].second;
				}

				if (r >= r1) {
					r2 = r1;
					r1 = r;
				} else if (r >= r2) r2 = r;
			}
		}

	}
	if (Q==2) h = max(r1, 1+r2);
	else --h;
	printf("%lld\n", h);
}