#include <cstdio>
#include <algorithm>
#define MAXN 5005
typedef long long ll;
int N, H;
ll g[MAXN], h[MAXN], q[MAXN], t[MAXN], dp[2][MAXN][2];

int main() {
    freopen("data.txt", "r", stdin);
    scanf("%d%d", &N, &H);
    for (int i = 0; i < N; ++i)
        scanf("%lld%lld%lld%lld", g+i, h+i, q+i, t+i);
    
    for (int T = 0; T <= H; ++T) {
        dp[0][T][0] = h[0] > T ? 0 : g[0] + dp[0][T-h[0]][1];
        dp[0][T][1] = (T / t[0]) * q[0];
    }

    for (int x = 1; x < N; ++x) {
        for (int T = 0; T <= H; ++T) {
            dp[x&1][T][0] = std::max(h[x] > T ? 0 : g[x] + dp[x&1][T-h[x]][1], dp[(x+1)&1][T][0]);

            dp[x&1][T][1] = std::max(t[x] > T ? dp[(x+1)&1][T][0] : q[x] + dp[x&1][T-t[x] ][1], dp[(x+1)&1][T][0]);            
        }
    }
    printf("%lld\n", dp[(N-1)&1][H][0]);
}