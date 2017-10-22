#include <cstdio>
using namespace std;

int P, R, c[11][101][101];

// c[p][r] holds a BIT of size 100
// Queries on this BIT count the num less than or equ to 
// certain val.

void update(int p, int r, int x, int v) {
    for (; x <= 100; x += x&-x) {
        c[p][r][x]+=v;
    }
}
int sum(int p, int r, int x) {
    int s=0;
    for (; x > 0; x -= x&-x) s+=c[p][r][x];
    return s;
}

inline int ceil(int big, int small) {
    return (big%small==0) ? big/small : big/small+1;
}

int main() {
    for (int p = 1; p <= 10; ++p) {
        for (int r = p; r <= 100; ++r) {
            if (p==r) {
                update(p, r, 1, 1);
            }
            else {
                int cnt=0;
                for (int l = ceil(r, p); l <= r-p+1 && 3*l <= 2*r+1; ++l) {
                    int d = sum(p-1, r-l, l);
                    update(p, r, l, d);
                    cnt += d;
                }
            }
        }
    }
    for (int t = 0; t < 10; ++t) {
        scanf("%d%d", &P, &R);
        printf("%d\n", sum(P, R, R));
    }
}