#include <cstdio>
int T, N, A[4], S[4], O[4], X[4];
int main() {
    freopen("data.txt", "r", stdin);
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &N);
        for (int i = 0; i < N; ++i) {
            scanf("%d%d%d", A+i, S+i, O+i);
            X[i] = O[i];
        }
        for (int d = 0; 1; ++d){
            bool ok = true;
            for (int i = 0; i < N; ++i) {
                if (X[i] % (A[i]+S[i]) < A[i]) ok = false;
            }
            if (ok) {
                printf("%d\n", d);
                break;
            }
            bool returned = true;
            for (int i = 0; i < N; ++i) if ( (X[i]-O[i] ) % (A[i]+S[i]) ) returned = false;
            if (d && returned) {
                printf("Foxen are too powerful\n");
                break;
            }
            for (int i = 0; i < N; ++i) ++X[i];
        }
        
    }
    
}