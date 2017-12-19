#include <cstdio>
const int MAXN = 31;
int n;
bool dp[MAXN][MAXN][MAXN][MAXN]; // true if winning

int main() {
	// freopen("data.txt", "r", stdin);	
	scanf("%d", &n);
	for (int a = 0; a < MAXN; ++a) {
		for (int b = 0; b < MAXN; ++b) {
			for (int c = 0; c < MAXN; ++c) {
				for (int d = 0; d < MAXN; ++d) {
					if (a>=2 && b >= 1 && d >= 2) dp[a][b][c][d] |= !dp[a-2][b-1][c][d-2];
					if (a>=1 && b>=1 && c>=1 && d>=1) dp[a][b][c][d] |= !dp[a-1][b-1][c-1][d-1];
					if (c>=2 && d>=1) dp[a][b][c][d] |= !dp[a][b][c-2][d-1];
					if (b>=3) dp[a][b][c][d] |= !dp[a][b-3][c][d];
					if (a>=1 && d>=1) dp[a][b][c][d] |= !dp[a-1][b][c][d-1];
				}
			}
		}
	}
	while (n--) {
		int na, nb, nc, nd; scanf("%d%d%d%d", &na, &nb, &nc, &nd);
		if (dp[na][nb][nc][nd]) printf("Patrick\n");
		else printf("Roland\n");
	}
}