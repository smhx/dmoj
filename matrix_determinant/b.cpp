#include <cstdio>
#define MOD 1000000007
typedef long long ll;
ll A[501][501]; int n;
ll determinant() {
    for (int i=0; i<n-1; ++i){
        for (int j=i+1; j<n; ++j){
            for (int k=i+1; k<n; ++k){
                // A[j][k] %= MOD; A[i][i] %= MOD; A[i][k] %= MOD;
                A[j][k] = A[j][k]*A[i][i]-A[j][i]*A[i][k];
                A[j][k] %= MOD;
                if (i) {
                //     // There should not be division!!!
                //     printf("A[j][k]=%lld, A[i-1][i-1]=%lld, A[%d][%d]/A[%d][%d]=%lld\n", A[j][k], A[i-1][i-1], j, k, i-1, i-1, A[j][k]/A[i-1][i-1]);
                    A[j][k] /= A[i-1][i-1];
                }
            }
        }
    }
    A[n-1][n-1] %= MOD;
    // return A[n-1][n-1];
    return (A[n-1][n-1] < 0) ? A[n-1][n-1]+MOD : A[n-1][n-1];
}

int main() {
    scanf("%d", &n);
    for (int i=0; i<n; ++i) 
        for (int j=0; j<n; ++j)
            scanf("%lld", &A[i][j]);
    ll sol = determinant();
    ll real = A[0][0]*(A[1][1]*A[2][2]-A[2][1]*A[1][2]);
    real -= A[0][1]*(A[1][0]*A[2][2]-A[1][2]*A[2][0]);
    real += A[0][2]*(A[1][0]*A[2][1]-A[1][1]*A[2][0]);
    printf("sol=%lld, real=%lld\n", sol, real);
    /*
    00 01 02
    10 11 12
    20 21 22
    */
    return 0;
}