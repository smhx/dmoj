/*input
8 4
*/
#include <cstdio>
const int MAXN = 255;
typedef long long ll;
int N, K, dp[MAXN][MAXN]; // dp[k][n] is number of ways for k people, n pies

int main() {
    scanf("%d%d", &N, &K);
    for (int n = 1; n <= N; ++n) dp[1][n] = 1;
    for (int k = 2; k <= K; ++k) {
        dp[k][k] = 1;
        for (int n = k+1; n <= N; ++n) {
            for (int i = 1; i*k <= n; ++i) {
                dp[k][n] += dp[k-1][n-i*k+(k-1)];
            }
        }
    }
    printf("%d\n", dp[K][N]);
}