#include <cstdio>
#define MAXN 2005
#define MOD 1000000007
typedef long long ll;
int N, M, x[MAXN];
ll times[MAXN];

ll powmod(int x, int p) {
    if (p==0) return 1LL;
    ll y = powmod(x, p/2)%MOD;
    return (p%2==0) ? (y*y)%MOD : (((y*y)%MOD)*x)%MOD;
}

int main() {
    freopen("data.txt", "r", stdin);
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) scanf("%d", x+i);
    scanf("%d", &M);
    // times[i][j] = CHOOSE (M-1+i-j, i-j)
    times[0] = 1;
    for (int diff = 1; diff < N; ++diff) {
        times[diff] = ((times[diff-1]*(M-1+diff) )%MOD*powmod(diff, MOD-2) )%MOD;
    }
    for (int i = 1; i <= N; ++i) {
        ll val = 0;
        for (int j = 1; j <= i; ++j) {
            val += times[i-j]*x[j];
            val %= MOD;
        }
        printf("%lld ", val);
    }
    printf("\n");
}