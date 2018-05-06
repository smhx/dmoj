#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll sum[100005];
inline ll f(int l, int r) {
	return sum[r]-sum[(l+r)/2]+sum[l-1]- sum[(l+r)/2-((r-l+1)&1)];
}
int besthub(int R, int L, int *X, ll B) {
	for (int i = 1; i <= R; ++i) sum[i] = sum[i-1] + X[i-1];
	int best = 0;
	for (int i = 0; i < R; ++i) {
		int lo = i, hi = R-1;
		while (lo < hi) {
			int mid = hi-(hi-lo)/2;
			if (f(i+1,mid+1) <= B) lo = mid;
			else hi = mid-1;
		}
		best = max(best, lo-i+1);
	}
	return best;
}