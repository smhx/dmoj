#include <bits/stdc++.h>
using namespace std;
int TEST = 10;
const int MAXN = 1005;
int N, a[MAXN], b[MAXN], sum[MAXN], dp[MAXN];
int main() {
	freopen("data.txt", "r", stdin);
	while (TEST--) {
		scanf("%d", &N);
		for (int i = 1; i <= N; ++i) {
			scanf("%d%d", a+i, b+i);
			sum[i] = sum[i-1]+a[i]+b[i];
		}
		memset(dp, 0, sizeof dp);
		for (int i = N; i; --i) {
			if (i > N-4) dp[i] = sum[N]-sum[i-1];
			else 
				for (int j = i; j <= i+4; ++j) 
					dp[i] = max(dp[i], -1+sum[j-1]-sum[i-1]+a[j]+dp[j+1]);
		}
		printf("%d\n", dp[1]);
	}
}