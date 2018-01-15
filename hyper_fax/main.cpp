#include <cstdio>
#include <algorithm>
#include <cstring>
const int MAXN = 2005;
int N, best, x[MAXN], d[MAXN], press[MAXN], dp[MAXN][MAXN][2], pie[MAXN], piesum[MAXN];

int main() {
	// freopen("data.txt", "r", stdin);
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) {
		scanf("%d %d", x+i, d+i);
		press[i] = x[i];
	}
	std::sort(press+1, press+1+N);

	for (int i = 1; i <= N; ++i) {
		x[i] = std::lower_bound(press+1, press+1+N, x[i])-press;
		pie[x[i]] = d[i];
	}

	for (int i = 1; i <= N; ++i) {
		piesum[i] = piesum[i-1]+pie[i];
	}

	memset(dp, -1, sizeof dp);

	best = dp[0][x[1]][0] = dp[0][x[1]][1] = pie[x[1]];

	for (int sz = 1; sz < N; ++sz) {
		for (int i = std::max(1, x[1]-sz); i <= std::min(N-sz, x[1]); ++i) {

			if (i==x[1]) {

				if (dp[sz-1][i][1] - (press[i+sz]-press[i+sz-1]) >= 0) 
					dp[sz][i][1] = std::max(dp[sz][i][1],pie[i+sz] + dp[sz-1][i][1] - (press[i+sz]-press[i+sz-1]) );
				
				if (dp[sz-1][i][0] - (press[i+sz]-press[i]) >= 0) 
					dp[sz][i][1] = std::max(dp[sz][i][1],pie[i+sz] + dp[sz-1][i][0] - (press[i+sz]-press[i]) );

				if (dp[sz][i][1] - (press[i+sz]-press[i]) >= 0) 
					dp[sz][i][0] = dp[sz][i][1] - (press[i+sz]-press[i]);
				
			} else if (i+sz==x[1]) {

				if (dp[sz-1][i+1][0] - (press[i+1]-press[i]) >= 0) 
					dp[sz][i][0] = std::max(dp[sz][i][0], pie[i] + dp[sz-1][i+1][0] - (press[i+1]-press[i]) );

				if (dp[sz-1][i+1][1] - (press[i+sz]-press[i]) >= 0) 
					dp[sz][i][0] = std::max(dp[sz][i][0], pie[i]+dp[sz-1][i+1][1] - (press[i+sz]-press[i]));

				if (dp[sz][i][0] - (press[i+sz]-press[i]) >= 0) 
					dp[sz][i][1] = dp[sz][i][0] - (press[i+sz]-press[i]);

			} else {
				if (dp[sz-1][i][1] - (press[i+sz]-press[i+sz-1]) >= 0) 
					dp[sz][i][1] = std::max(dp[sz][i][1],pie[i+sz] + dp[sz-1][i][1] - (press[i+sz]-press[i+sz-1]) );
				
				if (dp[sz-1][i][0] - (press[i+sz]-press[i]) >= 0) 
					dp[sz][i][1] = std::max(dp[sz][i][1],pie[i+sz] + dp[sz-1][i][0] - (press[i+sz]-press[i]) );
				
				if (dp[sz-1][i+1][0] - (press[i+1]-press[i]) >= 0) 
					dp[sz][i][0] = std::max(dp[sz][i][0], pie[i] + dp[sz-1][i+1][0] - (press[i+1]-press[i]) );
				
				if (dp[sz-1][i+1][1] - (press[i+sz]-press[i]) >= 0) 
					dp[sz][i][0] = std::max(dp[sz][i][0], pie[i]+dp[sz-1][i+1][1] - (press[i+sz]-press[i]));
			}

			if (dp[sz][i][0]>=0 || dp[sz][i][1] >= 0) best = std::max(best, piesum[i+sz]-piesum[i-1]);
		}
	}
	printf("%d\n", best);
}