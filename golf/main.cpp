#include <cstdio>
#include <algorithm>
using namespace std;
int D, N, g[32], dp[5285];

int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d%d", &D, &N);
	for (int i = 0; i < N; ++i) scanf("%d", g+i);
	dp[0] = 0;
	for (int i = 1; i <= D; ++i) {
		dp[i] = 1000000000;
		for (int j = 0; j < N; ++j) {
			if (i >= g[j]) dp[i] = min(dp[i], 1+dp[i-g[j]]);
		}
	}
	if (dp[D]== 1000000000) printf("Roberta acknowledges defeat.\n");
	else printf("Roberta wins in %d strokes.\n", dp[D]);
}
