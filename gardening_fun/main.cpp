#include <cstdio>
#include <algorithm>
const int MAXV = 102;
int N, A, B, C, v[200005], dp[2][MAXV+5];
int main() {
	scanf("%d%d%d%d", &N, &A, &B, &C);
	for (int i = 1; i <= N; ++i) scanf("%d", v+i);
	for (int i = N; i; --i) {
		for (int m = MAXV; m >= v[i]; --m) dp[i&1][m] = m*A+C*(m-v[i])*(m-v[i])+dp[(i^1)&1][m];
		for (int m = v[i]-1; m >= 0; --m) dp[i&1][m] = std::min(C*(m-v[i])*(m-v[i])+m*A+dp[(i^1)&1][m], dp[i&1][m+1]+B);
		for (int m = 1; m <= MAXV; ++m) dp[i&1][m] = std::min(dp[i&1][m], dp[i&1][m-1]);
	}
	printf("%d\n", dp[1][0]);
}
