#include <cstdio>
#include <algorithm>
#define MAXN 100005

using namespace std;
typedef long long ll;

ll N, D[MAXN], W[MAXN], dp[MAXN][2];

int main() {
	// freopen("data.txt", "r", stdin);
	scanf("%lld", &N);
	for (int i = 1; i <= N; ++i) scanf("%lld%lld", D+i, W+i);
	for (int i = 1; i <= N; ++i) {
		dp[i][0] = max(0LL, D[i]-W[i-1]) + dp[i-1][0];
		dp[i][0] = min(dp[i][0], D[i]+dp[i-1][1]);
		dp[i][1] = max(0LL, D[i]-W[i+1]-W[i-1]) + dp[i-1][0];
		dp[i][1] = min(dp[i][1],  max(0LL, D[i]-W[i+1]) + dp[i-1][1] );
	}

	printf("%lld\n", dp[N][0]);
}

