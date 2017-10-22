#include <cstdio>
#include <algorithm>
#include <cstdlib>
#define MOD 1000000007
typedef long long ll;
int N; ll A[501][501];
ll gcd(ll a, ll b){ return b == 0 ? a : gcd(b, a % b);}
ll power(ll x, int y) {
    if (y == 0) return 1;
    ll p = power(x, y/2) % MOD;
    p = (p * p) % MOD;
    return (y%2 == 0)? p : (x * p) % MOD;
}
ll fftd() {
    ll uf=1, ans=1;
    for (int j=1; j<N; ++j) {
        if (A[j][j]==0) {
            for (int l=j+1; l<=N; ++l) 
                if (A[l][j]) {std::swap(A[j], A[l]); uf *= -1; break;}
        }
        if (A[j][j]==0) return 0;
        for (int i=j+1; i<=N; ++i) 
            if (A[i][j]) {
                ll d = gcd(std::abs(A[j][j]), std::abs(A[i][j]) ), b=A[j][j]/d, c=A[i][j]/d;
                uf = (uf*b)%MOD;
                for (int k=j+1; k<=N; ++k) A[i][k] = (b*A[i][k]-c*A[j][k])%MOD;
            }
    }
    for (int i=1; i<=N; ++i) ans = (ans*A[i][i])%MOD;
    ans = (ans*power(uf, MOD-2))%MOD;
    return (ans<0) ? ans+MOD : ans;
}

int main() {
    scanf("%d", &N);
    for (int i=1; i<=N; ++i) 
        for (int j=1; j<=N; ++j) 
            scanf("%lld", &A[i][j]);
    printf("%lld\n", fftd());
}
// ll real = (A[1][1]*( (A[2][2]*A[3][3])%MOD-(A[3][2]*A[2][3])%MOD ) )%MOD;
// real -= (A[1][2]*((A[2][1]*A[3][3])%MOD-(A[2][3]*A[3][1])%MOD ) )%MOD;
// real += (A[1][3]*( (A[2][1]*A[3][2])%MOD-(A[2][2]*A[3][1])%MOD ) )%MOD;
// real %= MOD;
// if (real<0) real+=MOD;
