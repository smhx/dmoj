#include <cstdio>

using namespace std;

void print(int k, int N) {
    for (int i = 0; i < 2*N; i++) {
        if (i < k) {
            printf("*");
            continue;
        }
        if (i >= 2*N-k) {
            printf("*");
            continue;
        }
        printf(" ");
    }
    printf("\n");
}

int main () {
    int N;
    scanf("%d", &N);
    int k = 1;
    for (int i = 0; i < N; i++) {
        print(k, N);
        if (i >= (N-1)/2) {
            k-=2;
        } else {
            k+=2;
        }
    }
    return 0;
}