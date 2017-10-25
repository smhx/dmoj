#include <cstdio>
#include <algorithm>
#define MAXN 5005
#define INF 1000000000000000LL
typedef long long ll;
using namespace std;
int N;
ll c[MAXN], d[MAXN], dp[MAXN][MAXN];

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) scanf("%lld%lld", c+i, d+i);

	for (int i = N-1; i >= 0; --i) {
		for (int j = N-1; j > i; --j) {
			if (i==j-1) {
				if (d[i]==0) dp[i][j] = INF;
				else if (j+d[i] >= N ) dp[i][j] = c[i];
				else dp[i][j] = dp[i+1][j+d[i]] + c[i];
			} else {
				dp[i][j] = dp[i+1][j];
				if (j+d[i] >= N) dp[i][j] = min(dp[i][j], c[i]);
				else dp[i][j] = min(dp[i][j], c[i]+dp[i+1][j+d[i]]);
			}
		}
	}

	printf("%lld\n", dp[0][1]);
}