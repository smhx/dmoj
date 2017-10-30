#include <cstdio>

int main() {
    freopen("data.txt", "r", stdin);
    while (1) {
        int a[30], d[30];
        int n; scanf("%d", &n);

        // printf("n = %d\n", n);
        if (n==0) return 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d", a+i);
            // printf("%d ", a[i]);
        }
        // printf("\n");
        for (int i = 0; i <n-1; ++i) {
            d[i] = a[i+1]-a[i];
            // printf("%d ", d[i]);
        }
        // printf("\n");

        if (n==1) {
            printf("0\n");
            continue;
        }
        
        for (int k = 1; k < n; ++k) {
            // k is length of cycle
            bool works = true;
            for (int i = k; i < n-1; ++i) {
                if (d[i]!=d[i%k]) works = false;
            }
            
            if (works) {
                printf("%d\n", k);
                break;
            }
        }
    }
}