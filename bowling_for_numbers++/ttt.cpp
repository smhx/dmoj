#include <cstdio>
#include <algorithm>
#define MAXN 10600
#define MAXK 505
using std::max;
int t, n, k, w, A[MAXN], dp[2][MAXN][2], best[MAXN], sum[MAXN];
int main() {
    freopen("data.txt", "r", stdin);
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d", &n, &k, &w);
        for (int i = 1; i <= n; i++) scanf("%d", A+i);
        for (int i = 1; i <= n; ++i) sum[i] = sum[i-1]+A[i];
        for (int h = 1; h <= n; ++h) {
            if (best[h-1]<w) {
                best[h] = (sum[h]-sum[h-best[h-1]]>0) ? best[h-1]+1 : 0;
            } else {
                int b=0; best[h]=0;
                for (int j = 1; j <= w && j <= h; ++j) {
                    int cursum=sum[h]-sum[h-j];
                    if (cursum > b) b = cursum, best[h] = j;
                }
            }
        }
        for (int s = 1; s <= k; ++s) {
            for (int h = 1; h <= n; ++h) {
                for (int l = 0; l < 2; ++l) {
                    int &c = dp[s%2][h][l];
                    c = dp[s%2][h-1][0];
                    if (l) {
                        for (int next = h-1; next >= h-w && next > 0; --next) c = max(c, sum[h]-sum[next]+dp[(s-1)%2][next][1]);
                    } else {
                        int next = max(0, h-w);
                        c = max(c, sum[h]-sum[next]+dp[(s-1)%2][next][1]);
                    }
                }
            }
            printf("s=%d\n", s);
            for (int h = 1; h <= n; ++h) {
                for (int l = 0; l < 2; ++l) {
                    printf("dp[%d][%d][%d]=%d ", s%2, h, l, dp[s%2][h][l]);
                }
                printf("\n");
            }
        }
        printf("%d\n", dp[k%2][n][1]);
    }
}
/*
    for 
*/
