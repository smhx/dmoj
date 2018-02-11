/*input
1 1
*/
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 105, MOD = 1e9+7;
typedef long long ll;
int K;
ll fmem[MAXN], gmem[MAXN][MAXN], comb[MAXN][MAXN];

void choose() {
	for (int n = 0; n < MAXN; ++n) {
		comb[n][0] = 1LL;
		for (int k = 1; k <= n; ++k) {
			comb[n][k] = (comb[n-1][k-1] + comb[n-1][k])%MOD;
		}
	}
}

ll f(int N);

ll g(int N, int L) {
	ll &x = gmem[N][L];
	if (x != -1) return x;

	if (N < L || L > K) return x = 0;

	if (N==0) return x = 1;
	if (L==0) return x = 0;

	x = g(N-1, L-1);
	for (int i = L+1; i <= N; ++i) {
		ll ch = comb[N-1][i-1];
		ll left = g(i-1, L);
		ll right = f(N-i)-g(N-i,K);

		right = (right%MOD + MOD)%MOD;
		x += ( ( (left*right)%MOD ) * ch)%MOD;
		x %= MOD;
	}	

	return x;
}

ll f(int N) {
	ll &x = fmem[N];
	if (x != -1) return x;

	if (N == 0) return x = 1;
		
	x = 0;

	for (int m = 0; m < N; ++m) {
		ll left = f(m);
		ll ch = comb[N-1][m];
		ll right = f(N-m-1)-g(N-m-1, K);
		right = (right%MOD + MOD)%MOD;

		x += ( ( (left*right)%MOD ) * ch)%MOD;
		x %= MOD;
	}

	return x;
}

int main() {
	int N; scanf("%d%d", &N, &K);

	choose();

	memset(fmem, -1, sizeof fmem);
	memset(gmem, -1, sizeof gmem);

	ll a = f(N);

	memset(fmem, -1, sizeof fmem);
	memset(gmem, -1, sizeof gmem);

	--K;

	ll b = f(N);

	ll ans = ( (a-b)%MOD+MOD)%MOD;
	printf("%lld\n", ans);
}

