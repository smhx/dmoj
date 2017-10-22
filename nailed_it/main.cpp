#include <cstdio>
using namespace std;

int L[2001], S[4001], N, _;
int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &_);
        ++L[_];
    }

    int max = -1;
    int numMax = 0;

    for (int i = 1; i < 2001; i++) {
        if (!L[i]) continue;
        printf("i is %d\n", i);
        for (int j = i; j < 2001; j++) {
            if (!L[j]) continue;
            printf("    j is %d\n", j);
            int sum= i+j;
            int k;
            if (i==j) {
                k = L[i] >> 1;
            } else {
                k = L[i] < L[j] ? L[i] : L[j];
            }
            S[sum] += k;
            if (S[sum]==max) {
                numMax++;
            }
            else if (S[sum] > max) {
                max = S[sum];
                numMax = 1;
            }
        }
    }

    printf("%d %d\n", max, numMax);
    return 0;
}