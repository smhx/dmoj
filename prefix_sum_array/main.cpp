#include <cstdio>
#define MAXN 2001
#define MOD 1000000007
typedef long long ll;
int N, M, x[MAXN];

ll powmod(int x, int p) {
    if (p==0) return 1LL;
    ll y = powmod(x, p/2)%MOD;
    return (p%2==0) ? (y*y)%MOD : (((y*y)%MOD)*x)%MOD;
}

ll choose(int n, int k) {
    ll ans = 1;
    int small = (n-k < k) ? n-k : k;
    int big = n-small;
    for (ll i = big+1; i <= n; ++i) {
        ans = (ans*i)%MOD;
    }
    for (ll i = 1; i <= small; ++i) {
        ans = (ans*powmod(i, MOD-2) )%MOD;
    }
    return ans;
}
inline ll factor(int i, int j) {
    return choose(M-1+i-j, i-j); 
}
// can you precompute it???? Goes from (M-1, 0) to (M-1+2000, 2000)
// That's 2000 values!
int main() {
    freopen("data.txt", "r", stdin);
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) scanf("%d", x+i);
    scanf("%d", &M);
    // precompute factor[i][j].

    for (int i = 1; i <= N; ++i) {
        ll val = 0;
        for (int j = 1; j <= i; ++j) {
            val += factor(i, j)*x[j];
            val %= MOD;
        }
        printf("%lld ", val);
    }
    printf("\n");
}