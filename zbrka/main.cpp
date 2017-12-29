#include <cstdio>
#include <algorithm>
const int MAXC = 10005, MOD = 1e9+7;
int N, C, dp[2][MAXC], presum[2][MAXC];

int main() {
	dp[1][0] = 1;
	for (int i = 0; i <= C; ++i) presum[1][i]=1;
	for (int n = 2; n <= N; ++n) {
		for (int c = 0; c <= C; ++c) {
			int lo = std::max(0, c-n+1);
			dp[n&1][c] = presum[~n&1][c];
			if (lo) {
				dp[n&1][c] -= presum[~n&1][lo-1];
				if (dp[n&1][c] < 0) dp[n&1][c] += MOD;
			}
		}
		presum[n&1][0]=dp[n&1][0];
		for (int c = 1; c <= C; ++c) 
			presum[n&1][c] = (presum[n&1][c-1] + dp[n&1][c])%MOD;
	}
	printf("%d\n", dp[N&1][C]);
}