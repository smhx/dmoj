#include <vector>
#include <utility>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;
std::vector<std::pair<long long, int>> drd(long long N) {
    std::vector<std::pair<long long, int>> res;
    int exponent = 0;
    long long pwr = 1;
    // stage 1
    while (N/pwr >= 10ll) {
        for (int d = 1; d <= 9; d++) {
            res.push_back({d, exponent});
        }
        pwr *= 10; exponent++;
    }
    // stage 2
    long long l = pwr;
    long long p = 1;
    while (l < N) {
        if (l + pwr <= N) {
            res.push_back({p, exponent});
            l += pwr;
            p++;
        } else {
            pwr /= 10; --exponent;
            p *= 10;
        }
    }
    return res;
}


int digsum(ll x) {
    int sum=0;
    while (x) {
        sum += x%10LL;
        x /= 10LL;
    }
    return sum;
}


ll mem[20][300];

ll nways(int n, int s) {
    if (mem[n][s]!=-1) return mem[n][s];
    if (s==0) return mem[n][s] = 1LL;
    if (s > 9*n) return mem[n][s] = 0LL;
    if (n==1) return mem[n][s] = 1LL;
    mem[n][s] =0LL;
    for (int i = 0; i <= 9 && i <= s; ++i) 
        mem[n][s] += nways(n-1,s-i);    
    return mem[n][s];
}

ll cntR[500], cntL[500];

void solve(ll R, ll cnt[]) {
    vector<pair<long long, int> > x = drd(R);
    for (auto y : x) {
        int dsum = digsum(y.first);
        for (int i = 0; i <= 9*y.second; ++i) 
            cnt[i+dsum] += nways(y.second, i);
    }
}

int main() {
    ll L, R;
    memset(mem, -1, sizeof mem);
    scanf("%lld %lld", &L, &R);
    solve(R+1, cntR);
    solve(L, cntL);
    int num=0;
    for (int i = 0; i < 500; ++i) 
        if (cntR[i] - cntL[i] > 0) ++num;
    printf("%d\n", num);
}