#include <algorithm>
#include <cstdio>
using namespace std;

struct Edge {
    int bgn, end, w;
    bool orig;
    Edge() {}
    Edge(int b, int e, int we, bool o) : bgn(b), end(e), w(we), orig(o) {}

    bool operator<(const Edge &e) const { return w == e.w ? orig : w < e.w; }
};

int N, M, D, d = 0, maxi;
Edge edges[200001];
int F[100001];

int find(int n) { return F[n] == n ? n : (F[n] = find(F[n])); }

bool merge(int a, int b) {
    int aroot = find(a), broot = find(b);
    if (aroot != broot) {
        F[aroot] = broot;
        return true;
    }
    return false;
}

void MST() {
    sort(edges, edges + M);

    for (int i = 1; i <= N; i++) F[i] = i;

    int tree = 0;
    for (maxi = 0; maxi < M && tree < (N - 1); maxi++) {
        Edge e = edges[maxi];

        if (merge(e.bgn, e.end)) {
            ++tree;
            if (!e.orig) ++d;
        }
    }
    --maxi;
}

void enhance() {
    if (edges[maxi].orig) return;
    for (int i = 1; i <= N; i++) F[i] = i;

    int maxw = edges[maxi].w;

    for (int j = 0; j < M; j++) {
        Edge e = edges[j];

        if (find(e.bgn) == find(e.end)) continue;

        if ((e.w < maxw) || (e.w == maxw && e.orig))
            merge(e.bgn, e.end);

        else if (e.orig && e.w <= D) {
            --d;
            return;
        }
    }
}

int main() {
    scanf("%d%d%d", &N, &M, &D);
    for (int i = 0, a, b, c; i < M; i++) {
        scanf("%d%d%d", &a, &b, &c);
        edges[i] = Edge(a, b, c, i < N - 1);
    }
    MST();
    enhance();
    printf("%d\n", d);
    return 0;
}