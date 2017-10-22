#include <cstdio>
#include <cstring>
#include <vector>
#define MAX 150005
#define SQRT 400
using namespace std;
int N, M, Q, A[MAX], bucket[SQRT], last[MAX][SQRT], indx[MAX], L[MAX],
    offset[MAX];
vector<int> statsinline[MAX];
inline int ppl(int x) {
    int n = (int)statsinline[L[x]].size();
    return A[statsinline[L[x]][((indx[x] % n) - (offset[L[x]] % n) + n) % n]];
}
long long sum(int l, int r) {
    long long toret = 0;
    int low = l / SQRT, hi = r / SQRT;
    for (int i = low; i < hi; ++i) toret += bucket[i];
    for (int i = low * SQRT; i < l; ++i) toret -= ppl(i);
    for (int i = hi * SQRT; i <= r; ++i) toret += ppl(i);
    return toret;
}
void run(int l) {
    int pre = 0, first = -1;
    for (int i = 0; i < SQRT; ++i) {
        if (last[l][i] == -1) continue;
        if (first == -1) first = i;
        bucket[i] += pre;
        pre = ppl(last[l][i]);
        bucket[i] -= pre;
    }
    bucket[first] += pre;
    ++offset[l];
}
int main() {
    // freopen("data.txt", "r", stdin);
    memset(last, -1, sizeof last);
    scanf("%d%d%d", &N, &M, &Q);
    for (int i = 0; i < N; ++i) {
        scanf("%d", L + i);
        indx[i] = statsinline[L[i]].size();
        statsinline[L[i]].push_back(i);
        last[L[i]][i / SQRT] = i;
    }
    for (int i = 0; i < N; ++i) {
        scanf("%d", A + i);
        bucket[i / SQRT] += A[i];
    }
    while (Q--) {
        int q, l, r;
        scanf("%d%d", &q, &l);
        if (q == 1) {
            scanf("%d", &r);
            printf("%lld\n", sum(l - 1, r - 1));
        } else
            run(l);
    }
}