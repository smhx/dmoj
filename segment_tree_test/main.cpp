#include <cstdio>
#include <algorithm>
using namespace std;

int gcd(int a, int b) {return b==0 ? a : gcd(b, a%b);}
const int MAXN = 500005, INF = 1000000000; 
struct node {int l,r,gcd,q,lo;} segt[4*MAXN];
const node NIL = {-1, -1, 0, 0, INF};
int N, M, a[MAXN];

void combine(node a, node b, node& c) {
	c.lo = min(a.lo, b.lo);
	c.gcd = gcd(a.gcd, b.gcd);
	c.q = (a.gcd==c.gcd ? a.q : 0) + (b.gcd==c.gcd ? b.q : 0);
}	

void build(int u, int l, int r) {
	segt[u].l = l, segt[u].r = r;
	if (l==r) {
		segt[u].lo = segt[u].gcd = a[l];
		segt[u].q = 1;
	} else {
		int m = (l+r)/2;
		build(u<<1, l, m); build(u<<1|1, m+1, r);
		combine(segt[u<<1], segt[u<<1|1], segt[u]);
	}
}

void update(int u, int idx, int val) {
	if (segt[u].l == idx && segt[u].r == idx) segt[u].lo = segt[u].gcd = val;
	else {
		int m = (segt[u].l + segt[u].r)/2;
		if (segt[u].l <= idx && idx <= m) update(u<<1, idx, val);
		else update(u<<1|1, idx, val);
		combine(segt[u<<1], segt[u<<1|1], segt[u]);
	}
}

node query(int u, int l, int r) { // returns index of node
	if (r < segt[u].l || l > segt[u].r) return NIL;
	else if (l <= segt[u].l && segt[u].r <= r) return segt[u];
	node left = query(u<<1, l, r), right = query(u<<1|1, l, r);
	node x;
	combine(left, right, x);
	return x;
}

int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; ++i) {
		scanf("%d", a+i);
	}
	build(1, 1, N);
	while (M--) {
	    int a, b; char cmd;
	    scanf(" %c %d %d", &cmd, &a, &b);
	    if (cmd=='C') {
	        update(1, a, b);
	    } else {
	    	node x = query(1, a,b);
	    	if (cmd=='M') printf("%d\n", x.lo);
	    	else if (cmd=='G') printf("%d\n", x.gcd);
	    	else printf("%d\n", x.q);
	    }
	}
}