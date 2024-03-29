#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct node {
	int val,lmap, rmap;
	int sum;
	node(int v) : val(v), lmap(0), rmap(0), sum(0) {}
};

const int MAXN = 100005, INF = 1000000007;

int N, root, B[MAXN], lo[MAXN], hi[MAXN];
int nv;
bool leaf[MAXN*4];
vector<node> wtree[MAXN*4];

int dfstime = 0, dfsOrder[MAXN];

vector<int> ch[MAXN];

void dfs(int u) {
	lo[u] = hi[u] = ++dfstime;
	dfsOrder[dfstime] = u;
	for (int v : ch[u]) {
		dfs(v);
		hi[u] = max(hi[u], hi[v]);
	}
}


void build(int u) {
	int lo = INF, hi = -1;
	for (int i = 1; i < wtree[u].size(); ++i) {
		int x = wtree[u][i].val;
		lo = min(lo, x), hi = max(hi, x);
	} 

	if (lo==hi) {
		leaf[u] = true;
		for (int i = 1; i < wtree[u].size(); ++i) 
			wtree[u][i].sum = mp[wtree[u][i].val-1] + wtree[u][i-1].sum;
		return; // leaf
	}
	int left = 0, right = 0;
	wtree[u<<1].push_back(node(0));
	wtree[u<<1|1].push_back(node(0));
	for (int i = 1; i < wtree[u].size(); ++i) {
		int x = wtree[u][i].val;
		if (2*x <= hi+lo) {
			wtree[u<<1].push_back(node(x));
			++left;
		} else {
			wtree[u<<1|1].push_back(node(x));
			++right;
		}
		wtree[u][i].lmap = left;
		wtree[u][i].rmap = right;
	}
	for (int i = 1; i < wtree[u].size(); ++i) {
		wtree[u][i].sum = mp[wtree[u][i].val-1] + wtree[u][i-1].sum;
	}
	build(u<<1);
	build(u<<1|1);
}

int query(int u, int l, int r, ll m) {
	if (leaf[u]) {
		ll val = mp[wtree[u][1].val-1];
		int k = min(1LL*(r-l+1), m/val);
		return k;
	}
	int leftr = wtree[u][r].lmap;
	int leftl = l ? wtree[u][l-1].lmap : 0;
	int leftsz = leftr-leftl;
	ll leftsum = wtree[u<<1][leftr].sum - wtree[u<<1][leftl].sum;

	if (leftsum>=m) {
		return query(u<<1, leftl+1, leftr, m);
	} 
	int rightr = wtree[u][r].rmap;
	int rightl = l ? wtree[u][l-1].rmap : 0;
	int ans = leftsz + query(u<<1|1, rightl+1, rightr, m-leftsum);
	return ans;
}

int main() {
// 	freopen("data.txt", "r", stdin);
	ll M;
	scanf("%d%lld", &N, &M);
    for (int i = 1; i <= N; ++i ) {
        scanf("%d%lld%lld", B+i, C+i, L+i);
        if (B[i]==0) root = i;
        else ch[B[i]].push_back(i);
        mp[nv++] = C[i];
    }
    dfs(root);
    sort(mp, mp+nv);
	nv = unique(mp, mp+nv)-mp;
	for (int i = 1; i <= N; ++i) 
		C[i] = lower_bound(mp, mp+nv, C[i]) - mp + 1;

	// Is this the error? YES!

	wtree[1].push_back(node(0));
	for (int i = 1; i <= N; ++i) wtree[1].push_back(C[dfsOrder[i]]);
	// for (int i = 0; i <= N; ++i) wtree[1].push_back(node(C[lo[i]]) );

    build(1);
	ll ans = 0;
    for (int i = 1; i <= N; ++i) {
    	int n = query(1, lo[i], hi[i], M);
    	ans = max(ans, L[i]*ll(n) );
    }
    printf("%lld\n", ans);
}