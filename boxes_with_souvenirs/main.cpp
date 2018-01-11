#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int MAXN = 1e7+2;
ll ccw[MAXN], cw[MAXN];
ll delivery(int N, int K, int L, int p[]) {
	for (int i = 0; i < N; ++i) {
		if (i>=K) ccw[i] = 1LL*min(L, 2*p[i]) + ccw[i-K];
		else ccw[i] = 1LL*min(L, 2*p[i]);
	}
	cw[N] = 0;
	for (int i = N-1; i>=0; --i) {
		if (i+K < N) cw[i] = 1LL*min(L, 2*(L-p[i])) + cw[i+K];
		else cw[i] = 1LL*min(L, 2*(L-p[i]));
	}
	ll ans = cw[0];
	for (int i = 0; i < N; ++i) ans = min(ans, ccw[i]+cw[i+1]);
	return ans;
}