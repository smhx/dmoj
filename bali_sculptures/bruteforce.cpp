#include <cstdio>
#include <algorithm>
using namespace std;
#define MAXN 2005
#define INF (1LL<<60)
typedef long long ll;
int N, A, B, Y[MAXN]; ll sum[MAXN];
ll bruteforce(int lo, int tor, int steps) {
    // printf("in bruteforce(%d, %d, %d)\n", lo, tor, steps);
    if (steps > B) return INF;
    if (lo >= N) {
        return steps < A ? INF : 0;
    }
    ll m = INF;
    for (int i = lo; i < N; ++i) {
        ll s = (lo) ? sum[i]-sum[lo-1] : sum[i];
        m = min(m, tor|s|bruteforce(i+1, s|tor, steps+1));
    }
    // printf("RETURNING FROM (%d, %d, %d) => %d\n", lo, tor, steps, m);
    return m;
}
int main() {
    freopen("data.txt", "r", stdin);
    scanf("%d%d%d", &N, &A, &B);
    for (int i = 0; i < N; ++i) scanf("%d", Y+i);
    sum[0] = Y[0];
    for (int i = 1; i < N; ++i) sum[i] = sum[i-1]+Y[i];
    printf("%lld\n", bruteforce(0, 0, 0));
}

/*
    Algorithm is correct. Now time to optimize...
    The expensive step in bruteforce is the loop from lo to N-1, and then calling brute force each time.
    There is optimal substructure. Now determine overlapping subproblems!

    At each step, you're at a certain lo, and you have a tor. The answer will change
    depending on the tor value. 
    Initially tor is 000000000. Each time, you OR it with some sums.

    Approach it like this.

    For every binary place, try your best not to add it in. 
    So for every binary place, search every GOOD range (N^12 * log(10^9)) passes.

    What does this mean?

    Initially look at the highest fucking binary place. 
    for p = MAX_BP to 0
        // If there is one remaining good one, choose that
        // If there are no good ones, what do you do?
        // Or if there are multiple good ones, what do you do?
        Does it matter which one you choose?
        for i = 0 to N-1
            for j = i to N-1
                if (i, j) is BAD 
                else if sum(i, j) & (1 << p) mark (i, j) as BAD 
    

    Assume that for some binary place p, there are multiple good ones

    Every (i, j) is either GOOD, BAD, or UNDECIDED.

    In the end, you will have a set of (i, j) as good that do not overlap and cover 0 to N-1.
    Initially everything is UNDECIDED. If you can avoid a binary place, mark the ones
    that do not as BAD. Mark everything else as undecided.

    This allows you to filter out a set of ranges. But which ones do you choose? The minimum?

    Define a state by the             
*/