#include <cstdio>
#include <vector>
#define MAXN 1000005
using namespace std;
typedef long long ll;
int n;
ll a, b, c, s[MAXN], dp[MAXN];
vector<ll> M, B;

inline ll f(ll x) {return a * x * x + b * x + c;}

bool bad(int l1,int l2,int l3){return (B[l3]-B[l1])*(M[l1]-M[l2])<(B[l2]-B[l1])*(M[l1]-M[l3]);}

unsigned int ptr;
ll query(ll x) {
    if (M.size()==0) return 0;
    if (ptr >= M.size()) ptr = M.size()-1;
    for (; ptr < M.size() -1 && M[ptr+1] * x + B[ptr+1] > M[ptr] * x + B[ptr]; ++ptr);
    ll ans = M[ptr] * x + B[ptr];
    return ans > 0 ? ans : 0;
}

void add(ll slope, ll intrcp) {
    M.push_back(slope); B.push_back(intrcp);
    while (M.size()>=3 && bad(M.size()-3, M.size()-2, M.size()-1) ) {
        M.erase(M.end()-2); B.erase(B.end()-2);
    }
}

int main() {
    scanf("%d%lld%lld%lld", &n, &a, &b, &c);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", s+i);
        s[i] += s[i-1];
    }
    
    for (int i = 1; i <= n; ++i) {
        dp[i] = f(s[i]) + query(s[i]);
        add(-2 * a * s[i], a * s[i] * s[i] - b * s[i] + dp[i]);
    }
    printf("%lld\n", dp[n]);
}