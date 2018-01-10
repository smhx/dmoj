#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
#include <bits/stdc++.h>
using namespace std;
using namespace __gnu_pbds;
typedef pair<int,int> ii;
typedef tree<
ii,
null_type,
less<ii>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

const int MAXN = 100005;
int N, M, order[MAXN], ds[MAXN];

ordered_set os[MAXN];

int find(int x) {return ds[x]==x ? x : ds[x] = find(ds[x]);}

void merge(int x, int y) {
	int xr = find(x), yr = find(y);
	if (xr==yr) return;
	if (os[xr].size() > os[yr].size()) swap(xr,yr);
	ds[xr] = yr;
	for (auto it = begin(os[xr]); it != end(os[xr]); ++it) os[yr].insert(*it);
}

void init() {
	for (int i = 1; i <= N; ++i) {
		ds[i] = i; os[i].insert(ii(order[i], i));
	}
}

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; ++i) scanf("%d", order+i);
	init();
	for (int i = 0; i < M; ++i) {
		int a, b; scanf("%d%d", &a, &b);
		merge(a,b);
	}
	int Q; scanf("%d", &Q);
	while (Q--) {
		char op; int x;
		scanf(" %c %d", &op, &x);
		if (op=='B') {
			int y; scanf("%d", &y);
			merge(x,y);
		} else {
			int k; scanf("%d", &k);
			int xr = find(x);
			if (k > os[xr].size()) printf("-1\n");
			else {
				auto it = os[xr].find_by_order(k);
				printf("%d\n", it->second);
			}
		}
	}
}