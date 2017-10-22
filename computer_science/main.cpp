#include <cstdio>
#include <algorithm>
#define MAXN 200005
#define INF 2000000001
using namespace std;

int N, K, a[MAXN], L=0;

int main() {
    // freopen("data.txt", "r", stdin);
    scanf("%d%d", &N, &K);
    for (int i = 0; i < N; ++i) scanf("%d", a+i);
    sort(a, a+N);
    for (int i = 0; i < N;) {
        if (i+K-1 >= N-1) {
            L = max(L, a[N-1]-a[max(0, N-K)]);
            break;
        } else {
            int l = i;
            for (int j = i; i-j < K && j; --j) 
                if (a[l+K-1]-a[l] > a[j+K-1]-a[j]) l = j;
            L = max(a[l+K-1]-a[l], L);
            i = l + K;
        }
    }
    
    printf("%d\n", L);
}

