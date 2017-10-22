#include <cstdio>
#include <algorithm>
int t, n, k, w, A[30002], c[30001][501], sum[30001];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d", &n, &k, &w);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", A+i);
        }
        for (int i=1; i<=n; ++i) {
            if (i==1) sum[i]=A[i];
            else sum[i]=A[i]+sum[i-1];
        }
        for (int s=0; s<=k; ++s) {
            for (int h=1; h<=n; ++h) {
                if (s==0) c[h][s]=0;
                else if (h<=w) c[h][s]=sum[h];
                else c[h][s]=std::max(c[h-1][s], c[h-w][s-1]+sum[h]-sum[h-w]);
            }
        }
        printf("%d\n", c[n][k]);
    }
}
