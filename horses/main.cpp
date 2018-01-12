#include <cstdio>
#include <cmath>

typedef long long ll;
typedef long double ld; // lolololololol it WA's on last couple cases with normal double precision
const int MAXN = 500005, MOD = 1e9+7;

int N, X[MAXN], Y[MAXN];
ld logsum[MAXN];

ll powmod(int x, int exp) {
	if (exp==0) return 1LL;
	ll half = powmod(x, exp/2);
	if (exp&1) return (((half*half)%MOD) * 1LL*x)%MOD;
	return ((half*half)%MOD);
}

/* SEGMENT TREE */

struct node {
	int l, r, maxidx; 
	bool islazy; // just in case floating point is not precise
	ld maxlog,lazy;
	node():l(0),r(0),maxidx(0),islazy(0),maxlog(-1.0),lazy(0.0){}
} segt[4*MAXN];

inline void combine(node a, node b, node& c) {
	if (a.maxlog >= b.maxlog) c.maxlog = a.maxlog, c.maxidx = a.maxidx;
	else c.maxlog = b.maxlog, c.maxidx = b.maxidx;
}	

inline void apply(node& u, ld val) {
	u.maxlog += val;
	if (u.l != u.r) u.islazy = true, u.lazy += val;
}

inline void pushdown(int u) {
	apply(segt[u<<1], segt[u].lazy);
	apply(segt[u<<1|1], segt[u].lazy);
	segt[u].lazy=0.0;
	segt[u].islazy = false;
}

void build(int u, int l, int r) {
	segt[u].l = l, segt[u].r = r;
	if (l==r) {
		segt[u].maxidx = l; // or r
		segt[u].maxlog = logsum[l]+log(ld(Y[l])); // or r
	} else {
		int m = (l+r)/2;
		build(u<<1, l, m); build(u<<1|1, m+1, r);
		combine(segt[u<<1], segt[u<<1|1], segt[u]);
	}
}

void update(int u, int l, int r, ld val) {
	if (l > segt[u].r || r < segt[u].l) return;
	if (segt[u].islazy) pushdown(u);
	if (l <= segt[u].l && segt[u].r <= r) {
		apply(segt[u], val);
	} else {
		update(u<<1, l, r, val);
		update(u<<1|1, l, r, val);
		combine(segt[u<<1], segt[u<<1|1], segt[u]);
	}
}

/* BIT */

ll bit[MAXN];
void bitUpdate(int x, ll v) {
	for (++x; x <= N; x += x&-x) bit[x] = (bit[x]*v)%MOD;
}

ll bitSum(int x) {
	ll res = 1LL;
	for (++x; x; x-=x&-x) res = (res*bit[x])%MOD;
	return res;
}

inline int money() {
	if (segt[1].islazy) pushdown(1);
	int idx = segt[1].maxidx;
	return (bitSum(idx) * Y[idx])%MOD;
}

int init(int _N, int _X[], int _Y[]) {
	// Copy values
	N = _N;
	for (int i = 0; i < N; ++i) X[i] = _X[i], Y[i] = _Y[i];

	// compute logsum
	logsum[0] = log(ld(X[0]));
	for (int i = 1; i < N; ++i) logsum[i] = log(ld(X[i])) + logsum[i-1];

	// build segtree and bit
	build(1, 0, N-1);
	for (int i = 0; i <= N; ++i) bit[i] = 1LL;
	for (int i = 0; i < N; ++i) bitUpdate(i, 1LL*X[i]);

	return money();
}

int updateX(int pos, int val) {
	ld delta = log(ld(val))-log(ld(X[pos]));
	update(1, pos, N-1, delta);
	ll inverse = powmod(X[pos], MOD-2);
	bitUpdate(pos, inverse);
	bitUpdate(pos, val);
	X[pos] = val;
	return money();
}

int updateY(int pos, int val) {
	ld delta = log(ld(val))-log(ld(Y[pos]));
	update(1, pos, pos, delta);
	Y[pos] = val;
	return money();
}

#ifndef DMOJ
int tmpN, tmpX[MAXN], tmpY[MAXN];
int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d", &tmpN);
	for (int i = 0; i < tmpN; ++i) scanf("%d%d", tmpX+i, tmpY+i);
	printf("%d\n",init(tmpN, tmpX, tmpY));
	int Q; scanf("%d", &Q);
	while (Q--) {
		char type; int pos, val; scanf(" %c %d %d", &type, &pos, &val);
		if (type=='X') {
			printf("%d\n", updateX(pos, val));
		} else {
			printf("%d\n", updateY(pos,val));
		}
	}
}
#endif
