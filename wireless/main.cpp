#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;
int M, N, K, maxrate = 0, samerate = 0;
int L[1005][30005];
inline int dsqrd(int x1, int y1, int x2, int y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}
int main() {
    freopen("data.txt", "r", stdin);
    scanf("%d%d%d", &M, &N, &K);
    for (int i = 0; i < K; ++i) {
        int x, y, R, B;
        scanf("%d%d%d%d", &x, &y, &R, &B);

        // printf("x = %d, y = %d, R = %d\n", x, y, R);
        // int hi = y, lo = y;
        for (int X = max(1, x - R); X <= min(x + R, N); ++X) {
            int dy = (int)sqrt( (float) ( R*R - (X-x) * (X-x) ) );
            L[X][min(M, dy + y)] += B;
            L[X][max(0, y - dy - 1)] -= B;
            // printf("    X = %d, Y=%d, lo=%d\n", X, dy+y, y-dy-1);
            
        }
    }
    // printf("\n\n");
    for (int x = 1; x <= N; ++x) {
        // printf("x = %d\n", x);
        int tot = 0;
        for (int y = M; y > 0; --y) {
            tot += L[x][y];
            // printf("    y = %d, tot now %d\n", y, tot);
            
            if (tot > maxrate)
                maxrate = tot, samerate = 1;
            else if (tot == maxrate)
                samerate++;
        }
    }
    printf("%d\n%d\n", maxrate, samerate);
}
