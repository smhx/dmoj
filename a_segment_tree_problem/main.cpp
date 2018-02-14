#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAX = 2e6+6;
struct node {ll l, r, cnt, cost, lazy;} segt[8*MAX];
const node NIL = node();
int N;

inline void combine(node a, node b, node& c) {
	c.cnt = a.cnt + b.cnt;
	c.cost = a.cost + b.cost;
}

void apply(int u, ll val) {
	if (val == -1) {
		segt[u].cnt = segt[u].cost = 0;
		if (segt[u].l != segt[u].r) segt[u].lazy = -1;
	} else {
		segt[u].cnt += val*(segt[u].r-segt[u].l+1);
		segt[u].cost += val*(segt[u].r*(segt[u].r+1)/2 - segt[u].l*(segt[u].l-1)/2);
		if (segt[u].l != segt[u].r) {
			if (segt[u].lazy == -1) {
				segt[u].lazy = val;
				segt[u<<1].lazy = -1;

				segt[u<<1|1].lazy = -1;
				segt[u<<1].cnt = segt[u<<1].cost = segt[u<<1|1].cnt = segt[u<<1|1].cost = 0;
			}
			else segt[u].lazy += val;
		}
	}
}

void pushdown(int u) {
	apply(u<<1, segt[u].lazy);
	apply(u<<1|1, segt[u].lazy);
	segt[u].lazy=0;
}

void build(int u, int l, int r) {
	segt[u].l = l, segt[u].r = r;
	if (l==r) {
		segt[u].cost = segt[u].cnt = segt[u].lazy = 0;
	} else {
		int m = (l+r)/2;
		build(u<<1, l, m); build(u<<1|1, m+1, r);
		combine(segt[u<<1], segt[u<<1|1], segt[u]);
	}
}

void update(int u, int l, int r, int val) {
	if (segt[u].lazy!=0) pushdown(u);

	if (l > segt[u].r || r < segt[u].l) return;
	if (l <= segt[u].l && segt[u].r <= r) {
		apply(u, val);
	} else {
		update(u<<1, l, r, val);
		update(u<<1|1, l, r, val);
		combine(segt[u<<1], segt[u<<1|1], segt[u]);
	}
}

// not really necessary
node query(int u, int l, int r) { 
	if (r < segt[u].l || l > segt[u].r) return NIL;
	if (segt[u].lazy!=0) pushdown(u);
	if (l <= segt[u].l && segt[u].r <= r) return segt[u];
	node left = query(u<<1, l, r), right = query(u<<1|1, l, r);
	node x;
	combine(left, right, x);
	return x;
}

ll buyamt(int u, ll Q) {
	if (segt[u].lazy!=0) pushdown(u);
	ll numbought = 0;
	if (segt[u].cost <= Q) {
		numbought = segt[u].cnt;
		segt[u].cnt = segt[u].cost = 0;
		if (segt[u].l != segt[u].r) segt[u].lazy = -1;
	} else {
		if (segt[u].l == segt[u].r) {
			numbought = Q/segt[u].l; // or r
			segt[u].cnt -= numbought;
			segt[u].cost -= numbought*segt[u].l;
		} else {
			if (segt[u<<1].cost >= Q) {
				numbought = buyamt(u<<1, Q);
			} else {
				Q -= segt[u<<1].cost;
				numbought = buyamt(u<<1, segt[u<<1].cost) + buyamt(u<<1|1, Q);
			}
			combine(segt[u<<1], segt[u<<1|1], segt[u]);
		}
	}
	return numbought;
}

ll buylow(int u, ll L) {
	if (segt[u].lazy!=0) pushdown(u);
	ll paid = 0;
	if (segt[u].cnt <= L) {
		paid = segt[u].cost;
		segt[u].cnt = segt[u].cost = 0;
		if (segt[u].l != segt[u].r) segt[u].lazy = -1;
	} else {
		if (segt[u].l == segt[u].r) {
			paid = segt[u].l * L;
			segt[u].cnt -= L;
			segt[u].cost -= L*segt[u].l;
		} else {
			if (segt[u<<1].cnt >= L) {
				paid = buylow(u<<1, L);
			} else {
				L -= segt[u<<1].cnt;
				paid = buylow(u<<1, segt[u<<1].cnt) + buylow(u<<1|1, L);
			}
			combine(segt[u<<1], segt[u<<1|1], segt[u]);
		}
	}
	return paid;
}

ll buyhigh(int u, ll L) {
	if (segt[u].lazy!=0) pushdown(u);
	ll paid = 0;
	if (segt[u].cnt <= L) {
		paid = segt[u].cost;
		segt[u].cnt = segt[u].cost = 0;
		if (segt[u].l != segt[u].r) segt[u].lazy = -1;
	} else {
		if (segt[u].l == segt[u].r) {
			paid = segt[u].l * L;
			segt[u].cnt -= L;
			segt[u].cost -= L*segt[u].l;
		} else {
			if (segt[u<<1|1].cnt >= L) {
				paid = buyhigh(u<<1|1, L);
			} else {
				L -= segt[u<<1|1].cnt;
				paid = buyhigh(u<<1|1, segt[u<<1|1].cnt) + buyhigh(u<<1, L);
			}
			combine(segt[u<<1], segt[u<<1|1], segt[u]);
		}
	}
	return paid;
}

ll cost(int u, ll L) {
	if (segt[u].lazy!=0) pushdown(u);
	ll c;
	if (segt[u].l == segt[u].r) c = segt[u].l;
	else {
		// check if it's on the left or right
		if (segt[u<<1].cnt >= L) c = cost(u<<1, L);
		else {
			L -= segt[u<<1].cnt;
			c = cost(u<<1|1, L);
		}
	}
	return c;
}

int main() {
	int Q; scanf("%d", &Q);
	build(1, 1, MAX-1);
	char cmd[10];

	while (Q--) {
		scanf(" %s", cmd);
		if (strcmp(cmd, "ADD") == 0) {
			ll K; int P; scanf("%lld %d", &K, &P);
			update(1, P, P, K);
		} else if (strcmp(cmd, "ADDRANGE") == 0) {
			int A, B; scanf("%d%d", &A, &B);
			update(1, A, B, 1LL);
		} else if (strcmp(cmd, "BUYAMT") == 0) {
			ll Q; scanf("%lld", &Q);
			ll ans = buyamt(1, Q);
			printf("%lld\n", ans);
		} else if (strcmp(cmd, "BUYLOW") == 0) {
			ll L; scanf("%lld", &L);
			printf("%lld\n", buylow(1, L));
		} else if (strcmp(cmd, "BUYHIGH") == 0) {
			ll L; scanf("%lld", &L);
			printf("%lld\n", buyhigh(1, L));
		} else if (strcmp(cmd, "COST") == 0) {
			ll L; scanf("%lld", &L);
			node root = query(1, 1, MAX-1);
			if (root.cnt < L) printf("-1\n");
			else {
				printf("%lld\n", cost(1, L));
			}
		} else if (strcmp(cmd, "NUMCONES") == 0) {
			node root = query(1, 1, MAX-1);
			printf("%lld\n", root.cnt);
		} else {
			node root = query(1, 1, MAX-1);
			printf("%lld\n", root.cost);
		}
	}
}