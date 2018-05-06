#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, a, b, v[2005], dp[2018][9000];

#define DP(i,j) dp[i][j+4050]
inline ll clamp(ll x, ll c) {return max(-c, min(c, x));}
int main() {
	// freopen("data.txt", "r", stdin);
	scanf("%lld%lld%lld", &n, &a, &b);
	for (ll i = 0; i < n; ++i) scanf("%lld", v+i);
	sort(v, v+n);
	ll amp = 2*n;
	for (ll i = n-1; i >= 0; --i) {
		printf("i = %lld\n", i);
		DP(i,amp)=DP(i+1, clamp(v[i]+amp-v[i+1],amp))+amp*a;
		for (ll s = amp-1; s >= -amp; --s)
			DP(i,s) = min(DP(i, s+1), DP(i+1, clamp(v[i]+s+1-v[i+1], amp+1))+ (s > 0 ? a*s : -b*s) );
		--amp;
	}
	printf("%lld\n", DP(0, -n));
}
