#include <cstdio>
#include <vector>
#include <algorithm>
#define MAXN 300001
using namespace std;
int N;
int size[MAXN], top[MAXN], p[MAXN], anc[MAXN][20], l[MAXN];
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
void display(int i) {
    for (int j = 0; j <= i; ++j) {
        printf("p[%d]=%d, top[%d]=%d, size[%d]=%d\n", j, p[j], j, top[j], j, size[j]);
    }
}
int main() {
    scanf("%d", &N);
    size[0]=0; l[0]=0;
    for (int i = 0; i < MAXN; ++i) 
        for (int j = 0; j < 20; ++j) 
            anc[i][j]=-1;
    for (int i = 1; i <= N; ++i) {
        char q; int v;
        scanf(" %c %d", &q, &v);
        if (q=='a'){
            p[i]=v; top[i]=i; size[i]=1+size[v]; l[i]=1+l[v];
            update(i);
            // display(i);
        } else if (q=='b') {
            p[i]=p[v]; top[i]=top[p[v]]; size[i]=size[p[v]]; l[i] = l[v];
            update(i);
            printf("%d\n", top[v]);
            // display(i);
        } else {
            int w; scanf("%d", &w);
            p[i]=p[v]; size[i]=size[v]; top[i]=top[v]; l[i] = l[v];
            update(i);
            printf("%d\n", size[lca(v, w)]);
            // display(i);
        }
    }
    display(N);
}

