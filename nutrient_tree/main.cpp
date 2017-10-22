#include <cstdio>
#define MAXN 100
#define MAXX 2505
int X, dp[MAXN * 4][MAXX], tree[MAXN * 4];

void input(int p) {
    // base case. The first is a digit
    // You're setting tree[2*p+1], tree[2*p+2]
    // If you have a (
    int x = -1;
    scanf("%d", &x);
    if (x == -1) {
        scanf(" (");
        input((p << 1) + 1);
        input((p << 1) + 2);
    } else {
        tree[p] = x;
    }
}

int main() { input(0); }