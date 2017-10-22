#include <cstdio>
#include <algorithm>
#include <cstdlib>
#define MOD 1000000007
typedef long long ll;
int N; ll A[501][501];
ll gcd(ll a, ll b){
    a=std::abs(a), b=std::abs(b);
    return b == 0 ? a : gcd(b, a % b);
}
ll power(ll x, int y) {
    if (y == 0)
        return 1;
    ll p = power(x, y/2) % MOD;
    p = (p * p) % MOD;
    return (y%2 == 0)? p : (x * p) % MOD;
}
inline ll inverse(ll a) {
    return power(a, MOD-2);
}

ll fftd() {
    ll uf=1, ans=1;
    for (int j=1; j<N; ++j) {
        if (A[j][j]==0) {
            printf("in here\n");
            for (int l=j+1; l<=N; ++l) {
                if (A[l][j]) {
                    std::swap(A[j], A[l]);
                    uf *= -1;
                    break;
                }
            }
        }
        if (A[j][j]==0) return 0;
        for (int i=j+1; i<=N; ++i) {
            if (A[i][j]) {
                ll d = gcd(A[j][j], A[i][j]), b=A[j][j]/d, c=A[i][j]/d;
                uf *=b;
                uf %= MOD;
                for (int k=j+1; k<=N; ++k){
                    A[i][k] = b*A[i][k]-c*A[j][k];
                    A[i][k]%=MOD;
                }
            }
        }
    }
    for (int i=1; i<=N; ++i) {
        ans *= A[i][i];
        ans %= MOD;
    }
    ans *= inverse(uf);
    ans %= MOD;
    if (ans < 0) return ans+MOD;
    return ans;
}

int main() {
    scanf("%d", &N);
    for (int i=1; i<=N; ++i) 
        for (int j=1; j<=N; ++j) 
            scanf("%lld", &A[i][j]);
    printf("%lld\n", fftd());
}
