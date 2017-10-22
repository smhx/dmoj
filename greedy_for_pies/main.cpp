#include <cstdio>
#include <algorithm>
#define MAXN 3010
#define MAXM 105
using namespace std;
int N, M, A[MAXN], B[MAXM], bsum[MAXM], dp[MAXN][MAXM][MAXM], alone[MAXN];

inline int val(int i, int l, int r) {
    return (l <= r && l <= M) ? dp[i][l][r] : alone[i];
}

int main() {
    // freopen("data.txt", "r", stdin);
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) scanf("%d", A+i);
    scanf("%d", &M);
    for (int i = 1; i <= M; ++i) scanf("%d", B+i);
    for (int i = 1; i <= N; ++i) {
        if (i==1) alone[i] = A[i];
        else if (i==2) alone[i] = max(A[i], A[i-1]);
        else alone[i] = max(A[i]+alone[i-2], alone[i-1]);
    }
    sort(B+1, B+M+1);
    for (int i = 1; i <= M; ++i) bsum[i] = B[i]+bsum[i-1];
    for (int l = 1; l <= M; ++l) {
        for (int r = l; r <= M; ++r) {
            int num = (r-l+1)%2==0 ? (r-l+1)/2 : (r-l+2)/2;
            dp[0][l][r] = bsum[r]-bsum[r-num];
        }
    }
    for (int i = 1; i <= N; ++i) {
        for (int l = M; l >= 1; --l) {
            for (int r = l; r <= M; ++r) {
                int &x = dp[i][l][r];
                x = max(x, dp[i-1][l][r]);
                if (i>1) x = max(x, A[i]+dp[i-2][l][r]);
                x = max(x, A[i]+val(i-1, l+1, r)); 
                x = max(x, B[r]+val(i-1, l, r-1) ); 
                if (l<r) x = max(x, B[r]+val(i, l+1, r-1) ); 
                x = max(x, val(i, l, r-1) );
            }
        }
    }
    printf("%d\n", val(N, 1, M)); 
}   