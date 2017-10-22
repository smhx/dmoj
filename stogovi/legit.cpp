#include <cstdio>
#include <algorithm>
#define MAXN 300001
using namespace std;
int N, top[MAXN], p[MAXN], anc[MAXN][20], l[MAXN];
int lca(int v, int w) {
    if (l[v]<l[w]) swap(v, w);
    int lg;
    for (lg=1; (1<<lg)<=l[v]; ++lg);
    --lg;
    for (int i = lg; i >= 0; --i) {
        if (l[v]-(1<<i) >= l[w]) v = anc[v][i];
    }
    if (w==v) return v;
    for (int i=lg; i>=0; --i) {
        if (anc[v][i]!=anc[w][i] && anc[v][i]!=-1) {
            v = anc[v][i], w = anc[w][i];
        }
    }
    return p[v];
}
void update(int u) {
    anc[u][0]=p[u];
    for (int i = 1; (1<<i)<=l[u]; ++i) {
        anc[u][i] = anc[anc[u][i-1]][i-1];
    }
}

int main() {
    scanf("%d", &N);
    top[0]=0; l[0]=0; p[0]=-1;
    // for (int i = 0; i < MAXN; ++i) 
    //     for (int j = 0; j < 20; ++j) 
    //         anc[i][j]=-1;
    for (int i = 1; i <= N; ++i) {
        char q; int v;
        scanf(" %c %d", &q, &v);
        v = top[v];
        if (q=='a') {
            p[i]=v; 
            top[i]=i;
            l[i]=1+l[v];
            update(i);
        } else if (q=='b') {
            top[i] = p[v];
            printf("%d\n", top[v]);
        } else {
            int w; scanf("%d", &w);
            top[i] = v;
            printf("%d\n", l[lca(v, top[w])]);
        }
    }
}

