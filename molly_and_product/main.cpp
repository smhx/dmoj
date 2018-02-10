/*input
3 6 3 100
*/
#include <cstdio>

typedef long long ll;
const int MOD = 1e7+9;
int N;
ll A, B, M, sum_of_squares = 0, sum = 0;

int main() {
    scanf("%d %lld %lld %lld", &N, &A, &B, &M);
    
    for (int i = 0; i < N; ++i) {
        sum = (sum+A)%MOD;
        sum_of_squares = (sum_of_squares+A*A)%MOD;
        A = (A*B)%M;
    }
    
    printf("%lld\n", ( (sum*sum)%MOD-sum_of_squares%MOD + MOD)%MOD  );
}