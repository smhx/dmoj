#include <iostream>
#include <algorithm>
#define MAXN 1000005
#define LOG 22
using namespace std;

int N, Q, A[MAXN], intm[MAXN][LOG], hi[MAXN][LOG];

int lowerBound(int x, int r, int M) { 
    for (int lg = LOG; lg >= 0; --lg) 
        if (x + (1<<lg)<= r) 
            if (hi[x+1][lg] <= M) 
                x = x + (1<<lg) ;
    return x+1;
}

int intimidation(int l, int r) {
    if (l==r) return 1;
    int lg;
    for (lg=0; l+(1<<lg)-1 <= r; ++lg);
    --lg;
    int ans = 0;
    ans += intm[l][lg];
    int M = hi[l][lg];
    int x = l + (1<<lg) - 1;
    if (x==r) return ans;
    x = lowerBound(x, r, M);
    if (x != r+1) ans += intimidation(x, r);
    return ans;
}

int main() {
    // freopen("test1.txt", "r", stdin);
    scanf("%d%d", &N, &Q);
    for (int i = 1; i <= N; ++i) scanf("%d", A+i);
    for (int i = 1; i <= N; ++i) hi[i][0] = A[i], intm[i][0] = 1;
    for (int k = 1; k < LOG; ++k) {
        for (int i = 1; i <= N; ++i) {
            if (i + (1<<k) -1 > N) continue;
            hi[i][k] = max(hi[i][k-1], hi[i+(1<<(k-1) )][k-1] );
            intm[i][k] = intm[i][k-1];
            int x = i + (1<<(k-1))-1;
            x = lowerBound(x, i+(1<<k)-1, hi[i][k-1]);
            if (x != i+(1<<k))
                intm[i][k] += intimidation(x, i+(1<<k)-1);
        }
    }
    
    while (Q--) {
        int l, r; scanf("%d%d", &l, &r);
        printf("%d\n", intimidation(l, r));
    }
}