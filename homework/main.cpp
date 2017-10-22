#include <cstdio>

const int MAX = 10000005;
int T, A, B, K, primacity[MAX];

int main() {
    for (int i = 2; i < MAX; ++i)
        if (!primacity[i])
            for (int j = i; j < MAX; j += i) ++primacity[j];

    scanf("%d", &T)
    for (int t = 1; t <= T; ++t) {
        scanf("%d%d%d", &A, &B, &K);
        int ans = 0;
        for (int i = A; i <= B; ++i)
            if (primacity[i] == K) ++ans;
        printf("Case #%d: %d\n", t, ans);
    }
}
