#include <cstdio>
#include <algorithm>
#define MAXN 100005
#define INF 1000000000000000LL
using namespace std;

typedef long long ll;

char cmd;
int Q, N;
ll A[MAXN], S[MAXN];

struct node {
	ll msum, lsum, rsum, totsum;
	node() : msum(-INF), lsum(-INF), rsum(-INF), totsum(-INF) {}
	node(ll m, ll l, ll r, ll t) : msum(m), lsum(l), rsum(r), totsum(t) {}
} segt[4*MAXN];

void push(node& u, const node& l, const node& r) {
	u.msum = max(l.msum, max(r.msum,  l.rsum+r.lsum ));
	u.lsum = max(l.lsum, l.totsum+r.lsum);
	u.rsum = max(r.rsum, r.totsum+l.rsum);
	u.totsum = l.totsum + r.totsum;
}

void build(int u, int l, int r) {
	if (l==r) {
		segt[u].totsum = segt[u].lsum=segt[u].rsum=segt[u].msum=A[l];
	} else {
		int m = (l+r)>>1;
		build(u<<1, l, m);
		build(u<<1|1, m+1, r);
		push(segt[u], segt[u<<1], segt[u<<1|1]);
	}
}

node query(int u, int tl, int tr, int l, int r) {
	if (tl > r || tr < l) return node();
	if (l <= tl && tr <= r) return segt[u];
	int m = (tl+tr) >> 1;
	node toret, left = query(u<<1, tl, m, l, r), right = query(u<<1|1, m+1, tr, l, r);
	push(toret, left, right);
	return toret;
}

void update(int u, int tl, int tr, int i, ll x) {
	if (tr < i || tl > i) return;
	if (tl==tr) {
		segt[u].totsum=segt[u].lsum=segt[u].rsum=segt[u].msum= x;
		return;
	}
	int m = (tl+tr)>>1;
	update(u<<1, tl, m, i, x);
	update(u<<1|1, m+1, tr, i, x);
	push(segt[u], segt[u<<1], segt[u<<1|1]);
}

int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d%d", &N, &Q);
	for (int i = 1; i <= N; ++i) 
		scanf("%lld", A+i);

	build(1, 1, N);
	while (Q--) {
		scanf(" %c", &cmd);
		if (cmd=='Q') {
			int l, r; scanf("%d%d", &l, &r);
			printf("%lld\n", query(1, 1, N, l, r).msum);
		} else {
			int i; ll x; scanf("%d%lld", &i, &x);
			update(1, 1, N, i, x);
		}
	}
}