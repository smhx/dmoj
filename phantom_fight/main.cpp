#include <cstdio>
#include <algorithm>
#include <cstring>
#define MAXN 5003
#define MAXM 20004

using namespace std;

struct ghost {int s, m;} G[MAXN];
int N, M, dp[2][MAXM][2];

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; ++i)
		scanf("%d%d", &G[i].s, &G[i].m);

	for (int m = 0; m < MAXM/2; ++m) {

		if (m >= G[N].s) {
			dp[N&1][m][0] = 1;
			dp[N&1][m][1] = m-G[N].s+G[N].m;
		} else {
			dp[N&1][m][0] = 0;
			dp[N&1][m][1] = m;
		}
	}

	for (int i = N-1; i; --i) {
		for (int m = 0; m < MAXM/2; ++m) {
			int g1 = 0, rem1=0, g2=0, rem2=0;
			if (m >= G[i].s) {
				g1 = 1 + dp[(i+1)&1][m-G[i].s+G[i].m][0];
				rem1 = dp[(i+1)&1][m-G[i].s+G[i].m][1];
			}

			g2 = dp[(i+1)&1][m][0];
			rem2 = dp[(i+1)&1][m][1];
			
			if (g1>g2){
				dp[i&1][m][0] = g1;
				dp[i&1][m][1] = rem1;
			} else if (g1 < g2) {
				dp[i&1][m][0] = g2;
				dp[i&1][m][1] = rem2;
			} else {
				dp[i&1][m][0] = g1; //or g2
				dp[i&1][m][1] = max(rem1, rem2);
			}
		}

	}

	printf("%d %d\n", dp[1][M][0], dp[1][M][1]);
}