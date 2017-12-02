/*input
2 3
2 7 5
1 9 5
*/
#include <cstdio>
#include <algorithm>
using namespace std;
const int SIZE = 55, INF = 1000000000;
int N, M, R[SIZE][SIZE], presum[SIZE][SIZE], dp[SIZE][SIZE][SIZE][SIZE];
int f(int r1, int r2, int c1, int c2) {
	if (dp[r1][r2][c1][c2]!=-1) return dp[r1][r2][c1][c2];
	int sum1 = 0;
	for (int r = r1; r <= r2; ++r)
		for (int c = c1; c <= c2; ++c)
			sum1 += R[r][c];
	int sum = presum[r2][c2]-presum[r1-1][c2]-presum[r2][c1-1]+presum[r1-1][c1-1];
	if (sum!=sum1) {
		printf("sum = %d, sum1 = %d, r1 = %d, r2 = %d, c1 =%d, c2=%d\n", sum, sum1, r1, r2, c1, c2);
	}
	int ans = INF;
	for (int c = c1; c < c2; ++c) 
		ans = min(ans, sum+f(r1,r2,c1,c)+f(r1,r2,c+1,c2) );
	for (int r = r1; r < r2; ++r) 
		ans = min(ans, sum+f(r1,r,c1,c2)+f(r+1,r2,c1,c2) );
	return dp[r1][r2][c1][c2]=ans;
}
int main() {
	memset(dp, -1, sizeof dp);
	scanf("%d%d", &N, &M);
	for (int r = 1; r <= N; ++r) {
		for (int c = 1; c <= M; ++c) {
			scanf("%d", &R[r][c]);
			dp[r][r][c][c] = 0;
		}
	}
	for (int r = 1; r <= N; ++r) 
		for (int c = 1; c <= M; ++c) 
			presum[r][c] = R[r][c]+presum[r][c-1]+presum[r-1][c]-presum[r-1][c-1];
	printf("%d\n", f(1, N, 1, M));
}