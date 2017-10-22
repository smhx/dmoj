#include <cstdio>
#include <cstring>
#define MAXN 100005
using namespace std;
typedef long long ll;

int state[MAXN], tmpstate[MAXN];
ll N, T;

inline int normal(ll x) {
    x %= N;
    if (x<0) x += N;
    return x;
}


int main() {
    // freopen("data.txt", "r", stdin);
    scanf("%lld%lld", &N, &T);
    for (int i = 0; i < N; ++i) {
        char c; scanf(" %c", &c);
        state[i] = c-'0';
    }
    
    for (int k = 63-__builtin_clzll(T); k >= 0; --k) {
        if ( T&(1LL<<k)) {
            for (int i = 0; i < N; ++i) {
                int a = normal( (ll)i - (1LL << k) ) ;
                int b = normal( (ll)i + (1LL << k) ) ; 
                tmpstate[i] = (state[a] + state[b]) & 1;
            }
            memcpy(state, tmpstate, sizeof(int) * N);
            T -= (1LL<<k);
        }
    }
    
    for (int i = 0; i < N; ++i) printf("%d", state[i]);    
    printf("\n");
   
}
