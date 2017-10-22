#include <cstdio>
#include <algorithm>
int main() {
    int N, K; scanf("%d%d", &N, &K);
    if (N <= K) printf("%d\n", K-N);
    else printf("%d\n", std::min(N%K, K-(N%K)));
}