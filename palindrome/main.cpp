#include <cstdio>
#define MIN(a, b) (((a)<(b))?(a):(b))
#define MAXN 5005
char X[MAXN]; 
int N, dp[2][MAXN];

int main() {
    // freopen("data.txt", "r", stdin);
    scanf("%d %s", &N, X);
    for (int i = N-1; i >= 0; --i) {
        for (int j = i+1; j < N; ++j) {
            if (j==i+1) dp[i%2][j] = (X[i]==X[j]) ? 0 : 1;
            else if (X[i]==X[j]) dp[i%2][j] = dp[(i+1)%2][j-1];
            else dp[i%2][j] = 1+MIN(dp[i%2][j-1], dp[(i+1)%2][j]);
        }
    }
    printf("%d\n", dp[0][N-1]);
}