#include <cstdio>
#include <cstdlib>
#include <algorithm>
int memo[1<<10][1<<10][2], leg[1<<10][1<<10], L, R, W, l[11], r[11];
bool legal(int lmask, int rmask) {
    if (leg[lmask][rmask]==1) return true;
    if (leg[lmask][rmask]==-1) return false;
    int lSum=0, rSum=0;
    for (int i = 0; i < L; i++) if (lmask&(1<<i)) lSum += l[i];
    for (int i = 0; i < R; i++) if (rmask&(1<<i)) rSum += r[i];
    if (std::abs(lSum-rSum)<=W) {leg[lmask][rmask]=1; return true;}
    leg[lmask][rmask]=-1; return false;
}
int steps(int lmask, int rmask, int turn) {
    if (memo[lmask][rmask][turn]) return memo[lmask][rmask][turn];
    if (lmask==(1<<L)-1 && rmask==(1<<R)-1) return 0;
    int sol=1000000000;
    for (int i = 0; i < L; i++) {
        if (lmask & (1<<i) ) continue;
        if (legal(lmask|(1<<i), rmask)) sol = std::min(turn+steps(lmask|(1<<i), rmask, 0), sol);
    }
    for (int i = 0; i < R; i++) {
        if (rmask & (1<<i) ) continue;
        if (legal(lmask, rmask|(1<<i)))
            sol = std::min((turn+1)%2+steps(lmask, rmask|(1<<i), 1), sol);
    }
    memo[lmask][rmask][turn]=sol; return sol;
}
int main() {
    scanf("%d%d%d", &L, &R, &W);
    for (int i = 0; i < L; i++) scanf("%d", &l[i]);
    for (int i = 0; i < R; i++) scanf("%d", &r[i]);
    printf("%d\n", 1+std::min(steps(0, 0, 0), steps(0, 0, 1)));
}
