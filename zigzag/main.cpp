#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
const int MAXN = 10004, N_TEST=10, MOD = 1e9+7;
int N, q[N_TEST], dp[MAXN];
int main() {
	// freopen("data.txt", "r", stdin);
	for (int i = 0; i < N_TEST; ++i) {
		scanf("%d", q+i);
		N = max(N, q[i]);
	}

	vector<ll> pre, cur;
	pre = {1, 1};
	dp[0]=dp[1]=dp[2]=1;
	for (int i=3; i <= N; ++i) {
		cur.clear();
		cur.push_back(1LL);
		for(int i = 0; i + 1 < pre.size(); ++i) cur.push_back((pre[i]+pre[i+1])%MOD);
		cur.push_back(1LL);
		pre = cur;
		ll ans=0;
		for (int j = 0; j < i; j += 2) {
			ll add = cur[j];
			add = (add * 1LL * dp[j]) % MOD;
			add = (add * 1LL * dp[i-j-1]) % MOD;
			ans = (ans + add)%MOD;
		}
		dp[i] = ans;
	}

	for (int i = 0; i < N_TEST; ++i) {
		printf("%d\n", dp[q[i]]);
	}
}