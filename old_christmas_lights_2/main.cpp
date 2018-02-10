/*input

*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
using namespace std;
typedef pair<int,int> ii;
typedef pair<int, ii> diff_t;

const int MAXN = 50004, LOG = 17, SQRT = 2;
int N, Q, c[MAXN];

vector<int> adj[MAXN];

int dfst=0, p[MAXN], h[MAXN], disc[MAXN], finish[MAXN], node[MAXN];

void dfs(int u) {
	disc[u] = ++dfst;
	node[dfst] = u;
	for (int v : adj[u]) {
		if (v!=p[u]) {
			p[v] = u;
			h[v] = h[u]+1;
			dfs(v);
		}
	}
	finish[u] = ++dfst;
	node[dfst] = u;
}

int st[MAXN][LOG];

void buildLCA() {
	for (int u = 1; u <= N; ++u) st[u][0] = p[u];
	for (int k = 1; k < LOG; ++k) 
		for (int u = 1; u <= N; ++u) st[u][k] = st[st[u][k-1]][k-1];
}

void anc(int &u, int d) {for (int k = LOG-1; k >=0; --k) if (d&(1<<k)) u = st[u][k];}

int lca(int u, int v) {
	if (h[u] < h[v]) anc(v, h[v]-h[u]);
	else if (h[u] > h[v]) anc(u, h[u]-h[v]);
	if (u==v) return u; // or v
	for (int k = LOG-1; k>=0; --k)
		if (st[u][k]!=st[v][k]) u = st[u][k], v = st[v][k];
	return p[u]; // or p[v]
}

struct query {
	int l, r, lca, id;
	bool operator<(const query& q) const {return (l-1)/SQRT!=(q.l-1)/SQRT?l<q.l:r<q.r;}
} q[MAXN];

int ans[MAXN];
bool active[MAXN];

multiset<int> vals, diffs;

int press[MAXN], K;

struct bset {
	const static int END = -1;
	int bit[MAXN];
	int next(int x) {
		// next one with sum >= sum(x)
		return 0;
	}
	int prev(int x) {
		return 0;
	}

	int lower_bound(int sum) {
		// first with sum >= x
		int cursum=0, x = 1;

		if (bit[x] >= sum) return x;

		for (int k = LOG-1; k >= 0; --k) {
			if (x + (1<<k) <= K && cursum + bit[1<<k] < sum) {
				x += 1<<k;
				sum += bit[1<<k];
			}
		}
		if (x==K) return END;
		return x+1;
	}
};

void remove(int u) {
	auto it = vals.find(c[u]), pre = vals.end();
	auto nxt = next(it);
	if (it != vals.begin()) pre = prev(it);
	if (pre != vals.end()) diffs.erase(diffs.find(*it-*pre));
	if (nxt != vals.end()) diffs.erase(diffs.find(*nxt-*it));
	if (pre != vals.end() && nxt != vals.end()) diffs.insert(*nxt - *pre);
	vals.erase(it);
}

void add(int u) {
	auto it = vals.lower_bound(c[u]), pre = vals.end();
	if (it != vals.begin()) pre = prev(it);
	if (it != vals.end()) diffs.insert(*it - c[u]);
	if (it != vals.begin()) diffs.insert(c[u]-*pre);
	if (it != vals.begin() && it != vals.end()) diffs.erase(diffs.find(*it-*pre));
	vals.insert(c[u]);
}

void check(int u) {
	if (active[u]) remove(u);
	else add(u);
	active[u] ^= 1;
}

inline int query() {return *diffs.begin();}

void MO() {
	sort(q, q+Q);
	int curL = 1, curR = 1;
	for (int i = 0; i < Q; ++i) {
		while (curR <= q[i].r) check(node[curR++]);
		while (curR > q[i].r+1) check(node[--curR]); 
		while (curL > q[i].l) check(node[--curL]);
		while (curL < q[i].l) check(node[curL++]); 
		int d = query();
		if (q[i].lca!=-1) {
			auto it = vals.lower_bound(c[q[i].lca]);
			if (it != vals.end()) d = min(d, *it - c[q[i].lca]);
			if (it != vals.begin()) d = min(d, c[q[i].lca]-*prev(it));
		}
		ans[q[i].id] = d;
	}
}

#ifdef DMOJ
#define getchar() (*_pbuf ? *_pbuf++ : (_buf[fread_unlocked(_pbuf = _buf, 1, 1048576, stdin)] = 0, *_pbuf++))
char _buf[1048577], *_pbuf = _buf;

#endif



int read_int() {
	int c, o = 0;
	while ((c = getchar()) < '0');
	do {
		o = (o<<3)+(o<<1) + (c - '0');
	} while ((c = getchar()) >= '0');
	return o;
}

int main() {
	freopen("data.txt", "r", stdin);
	// scanf("%d%d", &N, &Q);
	N =read_int(); Q = read_int();
	for (int i = 1; i <=N; ++i) {
		c[i] = read_int();
		press[++K] = c[i];
	}
	for (int i = 1; i < N; ++i) {
		// int a, b; scanf("%d%d", &a, &b);
		int a = read_int(); int b = read_int();
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	dfs(1);
	buildLCA();

	sort(press+1, press+1+K);
	K = unique(press+1, press+1+K)-press-1;
	for (int i = 1; i <= N; ++i) c[i] = lower_bound(press+1, press+1+K, c[i])-press;

	for (int i = 0; i < Q; ++i) {
		// int u,v; scanf("%d%d", &u, &v);
		int u = read_int(); int v = read_int();
		if (disc[v] < disc[u]) swap(u, v);
		int w = lca(u,v);
		if (w==u) {
			q[i].l = disc[u], q[i].r = disc[v];
			q[i].lca = -1;
		} else {
			q[i].l = finish[u], q[i].r = disc[v];
			q[i].lca = w;
		}
		q[i].id = i;
	}
	MO();
	for (int i = 0; i < Q; ++i) printf("%d\n", ans[i]);
}