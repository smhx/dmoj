/*input

*/
#include <bits/stdc++.h>
using namespace std;
using int64 = long long;
using ii = pair<int,int>;
const int MAXN = 5e5+5;

int n;
int64 L, a[MAXN], b[MAXN];

struct node {
	int64 val, lzy;
	vector<int> ilzy;
} seg[4*MAXN];

void update_var(int u, int l, int r, int i, int tl, int tr) {
	if (l > tr || r < tl) return;
	if (l <= tl && tr <= r) {
		seg[u].ilzy.push_back(i);
	} else {
		int tm = (tl+tr)/2;
		update_var(2*u, l, r, i, tl, tm);
		update_var(2*u+1, l, r, i, tm+1, tr);
	}
}

void update_const(int u, int l, int r, int64 v, int tl, int tr) {
	if (l > tr || r < tl) return;
	if (l <= tl && tr <= r) {
		seg[u].lzy += v;
	} else {
		int tm = (tl+tr)/2;
		update_const(2*u, l, r, v, tl, tm);
		update_const(2*u+1, l, r, v, tm+1, tr);
	}
}

void solve() {
	cin >> n >> L;
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (int i = 0; i < n; ++i) cin >> b[i];

	for (int i = 0; i < n; ++i) {
		--a[i];
		--b[i];
	}

	sort(a, a+n); sort(b, b+n);

	int j1 = 0, j2 = 0, j3 = 0;
	
	for (int i = 0; i < n; ++i) {
		while (j1 < n && b[j1] < a[i]-L/2) ++j1;
		while (j2 < n && b[j2] < a[i]) ++j2;
		while (j3 < n && b[j3] < a[i]+L/2) ++j3;


	}
}

int main() {
	for (int i = 0; i < 10; ++i) {
		solve();
	}
}