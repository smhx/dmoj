#include <cstdio>
#include <algorithm>
#define MAXN 1003
int N, dp[MAXN][MAXN], S[MAXN]; // 0 is min, 1 is max

int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d", &N);

	for (int i = 1; i <= N; ++i) {
		scanf("%d", S+i);
		S[i] += S[i-1];
	}

	for (int l = 1; l <= N; ++l) {
		for (int i = 1; i+l-1 <= N; ++i) {
			int j = i+l-1;
			dp[i][j] = S[j]-S[i-1]-std::min(dp[i+1][j], dp[i][j-1]);
		}
	}

	printf("%d\n", dp[1][N]);
}