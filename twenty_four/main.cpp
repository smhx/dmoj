#include <bits/stdc++.h>
using namespace std;

int N, n, c[5], dp[25][50];

bool good(int x, int mask) {
	if (dp[x][mask]!=-1) return dp[x][mask];

	if (mask==0) return dp[x][mask]=0;

	int k=0; while (1<<k != (mask&-mask)) ++k;

	if ((mask&-mask) == mask) return dp[x][mask] = c[k]==mask;
	
	return 0;
}
int main() {
	scanf("%d", &N);
	while (N--) {
		memset(dp, -1, sizeof dp);
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) scanf("%d", c+i);
		bool found = false;
		for (int x = 24; x && !found; --x) {
			for (int mask = 1; !found && (mask < 1<<n); ++mask) found = good(x, mask);
		}
	}
}