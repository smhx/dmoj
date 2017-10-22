#include <cstdio>
#include <algorithm>
#define MAXN 10600
using namespace std;
int t, n, k, w, A[MAXN], dp[MAXN][2][2], best[MAXN], sum[MAXN];
int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d", &n, &k, &w);
        for (int i = 1; i <= n; i++) scanf("%d", A+i);
        for (int i = 1; i <= n; ++i) sum[i] = sum[i-1]+A[i];
        for (int h = 1; h <= n; ++h) {
            int b=0; best[h]=0;
            for (int j = 1; j <= w && j <= h; ++j) {
                int cursum=sum[h]-sum[h-j];
                if (cursum > b) b = cursum, best[h] = j;
            }
        }
        for (int s = 1; s <= k; ++s) {
            for (int h = 1; h <= n; ++h) {
                for (int l = 0; l < 2; ++l) {
                    // what if best[h]=0?
                    
                    int next = (l) ? h-best[h] : max(0, h-w);
                    int leave = dp[h-1][s%2][0];
                    int take = sum[h]-sum[next]+dp[next][(s-1)%2][1];
                    dp[h][s%2][l] = max(take, leave);
                }
            }
        }
        printf("%d\n", dp[n][k%2][1] );
    }
}

/*
 TC 1:
    41059
    113735
    139975
    153154
 TC 2:
    226173
    224664
    229045
    271413

*/