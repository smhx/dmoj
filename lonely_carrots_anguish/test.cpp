#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
struct wavelet_tree{
	int lo, hi;
	wavelet_tree *l, *r;
	vector<int> b;
 
	//nos are in range [x,y]
	//array indices are [from, to)
	wavelet_tree(int *from, int *to, int x, int y){
		lo = x, hi = y;
		if(lo == hi or from >= to) return;
		int mid = (lo+hi)/2;
		auto f = [mid](int x){return x <= mid;};
		b.reserve(to-from+1);
		b.push_back(0);
		for(auto it = from; it != to; it++)
			b.push_back(b.back() + f(*it));
		//see how lambda function is used here	
		auto pivot = stable_partition(from, to, f);
		l = new wavelet_tree(from, pivot, lo, mid);
		r = new wavelet_tree(pivot, to, mid+1, hi);
	}
 
	//count of nos in [l, r] Less than or equal to k
	int LTE(int l, int r, int k) {
		if(l > r or k < lo) return 0;
		if(hi <= k) return r - l + 1;
		int lb = b[l-1], rb = b[r];
		return this->l->LTE(lb+1, rb, k) + this->r->LTE(l-lb, r-rb, k);
	}
 
	~wavelet_tree(){
		delete l;
		delete r;
	}
};

vector<int> tree[200005];
int n, q, depth[200005], dfsorder[200005], lo[200005], hi[200005], par[200005], dfst=0, maxdepth = 0;
int ordered_depth[200005];
void dfs(int u, int p) {
	par[u] = p;
	lo[u] = hi[u] = ++dfst;
	dfsorder[dfst] = u;
	depth[u] = 1 + depth[p];
	maxdepth = max(depth[u], maxdepth);
	for (int v : tree[u]) {
		if (v != p) {
			dfs(v, u);
			hi[u] = max(hi[u], hi[v]);
		}
	}
}
int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i < n; ++i) {
		int a, b; scanf("%d%d", &a, &b);
		tree[a].push_back(b); tree[b].push_back(a);
	}
	dfs(1, 0);
	for (int i = 1; i <= n; ++i) printf("%d ", dfsorder[i]);
	for (int i = 1; i <= n; ++i) ordered_depth[i] = depth[dfsorder[i]];
	wavelet_tree wtree(ordered_depth+1, ordered_depth+1+n, 0, maxdepth);
	scanf("%d", &q);
	while (q--) {
		int u, d; scanf("%d%d", &u, &d);
		ll cnt = wtree.LTE(lo[u], hi[u], depth[u]+d);
		ll np = cnt*cnt+cnt+1;
		for (int v : tree[u]) {
			if (v != par[u]) {
				ll c = wtree.LTE(lo[v], hi[v], depth[u]+d);
				np -= c*c;
			}
		}
		
		// c1, c2, ... (c1+...+ck)^2-c1^2-c2^2...-ck^2+(c1+c2+...+ck)+1
		// so you have to loop through the children ...
		// which is worst case O(n).
	}
}