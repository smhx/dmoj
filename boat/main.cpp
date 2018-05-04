#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 1e9+7;
const int maxn = 505;

int n, npress=0;
ll a[maxn], b[maxn], press[2*maxn], dp[maxn][2*maxn], inv[maxn];

ll powmod(ll x, ll e) {
	if (e==0) return 1LL;
	ll half = powmod(x, e/2);
	if (e%2==0) return (half*half)%mod;
	return ((half*half)%mod * x)%mod;
}

int main() {
	// freopen("data.txt", "r", stdin);
	scanf("%d", &n);
	for (ll i = 1; i <= n; ++i) inv[i] = powmod(i, mod-2);
	for (int i = 1; i <= n; ++i) {
		scanf("%lld %lld", a+i, b+i);
		press[++npress] = a[i];
		press[++npress] = b[i]+1;
	}
	sort(press+1, press+1+npress);
	npress = unique(press+1, press+1+npress)-press-1;
	for (int i = 1; i <= n; ++i) {
		a[i] = lower_bound(press+1, press+1+npress, a[i])-press;
		b[i] = lower_bound(press+1, press+1+npress, b[i]+1)-press;
	}
	for (int p = 0; p <= npress; ++p) dp[0][p] = 1;
	for (int i = 1; i <= n; ++i) {
		for (int p = a[i]; p < b[i]; ++p) {
			ll d = press[p+1]-press[p];
			dp[i][p] = (d * dp[i-1][p-1])%mod;
			ll ways = d-1;
			ll k = 1;
			for (int j = i-1; j; --j) {
				if (a[j] <= p && p < b[j]) {
					++k;
					ways = (ways * (d+k-2LL)) % mod;
					ways = (ways * inv[k]) % mod;
					dp[i][p] = (dp[i][p] + dp[j-1][p-1] * ways) % mod;
				}
			}
		}
		// currently, dp[i][p] holds the number where i must be used on p
		for (int p = 1; p <= npress; ++p) {
			dp[i][p] = (dp[i][p] + dp[i][p-1]) % mod;
		}
		// now dp[i][p] holds the number where i must be used on [1, p]
		// there's still the case where i is not used at all!
		for (int p = 0; p <= npress; ++p) {
			dp[i][p] = (dp[i][p] + dp[i-1][p]) % mod;
		}
	}
	printf("%lld\n", (dp[n][npress]-1+mod)%mod);
}
