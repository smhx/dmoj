#include <cstdio>
#include <algorithm>
#define MAXN 1000006
using namespace std;
typedef long long ll;
int k, n;

ll c[MAXN], dp[MAXN];

int main() {
	// freopen("data.txt", "r", stdin);
	scanf("%d%d", &k, &n);
	for (int i = 1; i <= n; ++i)
		scanf("%lld", c+i);

	if (k==1 && n >= 2) return !printf("%lld\n", max(c[1], c[2]));

	if (n < k-1) return !printf("-1\n");

	dp[1] = c[1];
	dp[2] = c[1]+c[2];
	for (int i = 3; i < k; ++i) 
		dp[i] = max(c[i]+c[i-1], c[i]+dp[i-2]);
	
	ll ans = dp[k-1];
	if (n >= k) ans = max(ans, c[k]);
	printf("%lld\n", ans);
}