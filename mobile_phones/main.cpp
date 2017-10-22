#include <cstdio>
#define MAXN 1025
int N, table[MAXN][MAXN];

void update(int x, int y, int a) {
    // printf("UPDATING %d, %d, %d\n", x, y, a);
    for (; x <= N; x += x&-x) 
        for (int z = y; z <= N; z += z&-z) 
            table[x][z] += a;
}
int query(int x, int y) {
    // printf("Querying %d, %d\n",x, y);
    int ans = 0;
    for (;x; x -= x&-x) 
        for (int z = y; z; z -= z&-z) 
            ans += table[x][z];
    return ans;
}

int main() {
    // freopen("mobiles/mobiles_3.in", "r", stdin);
    // freopen("my.txt", "w", stdout);
    while (1) {
        int q; scanf("%d", &q);
        if (q==0) {
            scanf("%d", &N);

            // printf("SIZE IS %d\n", N);
        } else if (q==1) {
            int X, Y, A;
            scanf("%d%d%d", &X, &Y, &A);
            update(X+1, Y+1, A);
        } else if (q==2){
            int L, B, R, T;
            scanf("%d%d%d%d", &L, &B, &R, &T);
            ++L, ++B, ++R, ++T;
            int ans = query(R, T)-query(L-1, T)-query(R, B-1)+query(L-1, B-1);
            printf("%d\n", ans);
        } else {
            return 0;
        }
    }
}