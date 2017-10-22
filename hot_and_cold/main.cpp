#include <cstdio>
#include <vector>
#include <algorithm>
#define scan(x) do{while((x=getchar())<'0');for(x-='0';'0'<=(_=getchar());x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define MAXN 100005
#define LOG 18
using namespace std;
typedef long long ll;
int N, S, h[MAXN], p[MAXN][LOG];
ll a[MAXN], b[MAXN], A[MAXN], B[MAXN];
vector<int> adj[MAXN];

void dfs() {
    vector<int> s;
    h[1] = 0;
    s.push_back(1);
    while (!s.empty()) {
        int u = s.back(); s.pop_back();
        for (size_t i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i];
            if (v != p[u][0]) {
                h[v] = 1 + h[u];
                p[v][0] = u;
                s.push_back(v);
            }
        }
    }
}

int anc(int u, int i) {
    for (int j = LOG-1; j >= 0; --j) if ((i>>j)&1) u = p[u][j];
    return u;
}

int lca(int u, int v, int& du, int& dv) {
    du=dv=0;
    if (h[u] < h[v]) dv = h[v]-h[u], v = anc(v, h[v]-h[u]);
    else if (h[v] < h[u]) du = h[u]-h[v], u = anc(u, h[u]-h[v]);
    if (u==v) return u;
    int d = 0;
    for (int i = LOG-1; i >= 0; --i) 
        if (p[u][i] && p[u][i] != p[v][i]) 
            u = p[u][i], v = p[v][i], d |= 1<<i;
    du += d+1, dv += d+1;
    return p[u][0];
}

void sum(int u) {
    A[u]=a[u], B[u] = b[u];
    for (size_t i = 0; i < adj[u].size(); ++i) {
        int v = adj[u][i];
        if (v != p[u][0]) {
            sum(v);
            A[u] += A[v], B[u] += B[v];
        }
    }
}


int main() {
    scan(N); scan(S);
    for (int i = 1; i < N; ++i) {
        int x, y; scan(x); scan(y);
        adj[x].push_back(y); adj[y].push_back(x);
    }
    dfs();
    for (int i = 1; 1<<i <= N; ++i) 
        for (int j = 1; j <= N; ++j)
            if (p[j][i-1]) p[j][i] = p[p[j][i-1]][i-1];
    while (S--) {
        int u, v, t, uw, vw, uq, tq, tmp; 
        scan(u); scan(v); scan(t);
        // scanf("%d%d%d", &u, &v, &t);
        int w = lca(u, v, uw, vw);
        int q = lca(u, t, uq, tq);
        if (q==w && h[w] < h[lca(v, t, tmp, tmp)]) {
            swap(u, v); swap(uw, vw);
            q = lca(u, t, uq, tq);
        }
        if (h[q] < h[w]) {
            q = w, uq = uw;
            int x, y;
            lca(q, t, x, y);
            tq = x+y;
        }
        ++a[u]; b[u] += uq+tq-h[u];
        a[p[q][0]]-=2; b[p[q][0]] += 1+h[p[q][0]]-uq+h[u];
        ++a[p[w][0]]; b[p[w][0]] -= h[p[q][0]]+tq+1;
        ++a[v]; b[v] += -h[v]+vw+uw-uq+tq;
        --a[w]; b[w] -= -h[v]+vw+uw-uq+tq;
    }
    sum(1);
    for (int i = 1; i <= N; ++i) printf("%lld ", A[i] * h[i] + B[i]);
    printf("\n");
}