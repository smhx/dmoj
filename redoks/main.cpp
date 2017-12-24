#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 250005;
struct node {int l,r,lazy, freq[10];} segt[4*MAXN];
const node NIL = node();
int N, M, a[MAXN], tmp[10];

void combine(node a, node b, node& c) {
	for (int i = 0; i < 10; ++i) c.freq[i]=a.freq[i]+b.freq[i];
}	

void apply(node& u, int val) {
	for (int i = 0; i < 10; ++i) tmp[(i+val)%10] = u.freq[i];
	for (int i = 0; i < 10; ++i) u.freq[i] = tmp[i];
	if (u.l != u.r) u.lazy = (u.lazy+val)%10;
}

void pushdown(int u) {
	apply(segt[u<<1], segt[u].lazy);
	apply(segt[u<<1|1], segt[u].lazy);
	segt[u].lazy=0;
}

void build(int u, int l, int r) {
	segt[u].l = l, segt[u].r = r;
	if (l==r) {
		segt[u].freq[a[l]]=1;
	} else {
		int m = (l+r)/2;
		build(u<<1, l, m); build(u<<1|1, m+1, r);
		combine(segt[u<<1], segt[u<<1|1], segt[u]);
	}
}
void update(int u, int l, int r, int val) {
	if (l > segt[u].r || r < segt[u].l) return;
	if (segt[u].lazy) pushdown(u);
	if (l <= segt[u].l && segt[u].r <= r) {
		apply(segt[u], val);
	} else {
		update(u<<1, l, r, val);
		update(u<<1|1, l, r, val);
		combine(segt[u<<1], segt[u<<1|1], segt[u]);
	}
}

node query(int u, int l, int r) { 
	if (r < segt[u].l || l > segt[u].r) return NIL;
	if (segt[u].lazy) pushdown(u);
	if (l <= segt[u].l && segt[u].r <= r) return segt[u];
	node left = query(u<<1, l, r), right = query(u<<1|1, l, r);
	node x;
	combine(left, right, x);
	return x;
}

int main() {
	// freopen("data.txt", "r", stdin);
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; ++i) {
		char c;
		scanf(" %c", &c);
		a[i] = c-'0';
	}
	build(1, 1, N);
	while (M--) {
	    int a,b; scanf("%d%d", &a, &b);
	    node n = query(1, a, b);
	    int sum = 0;
	    for (int i =0; i < 10; ++i) sum += i * n.freq[i];
	    printf("%d\n", sum);
	    update(1, a, b, 1);
	}
}