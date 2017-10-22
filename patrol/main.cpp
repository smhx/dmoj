#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#define MAXN 100005
#define INF 1000000000
using namespace std;
typedef long long ll;

int N, K, diameter=0, dia[MAXN], p[MAXN], h[MAXN], f[2][MAXN];
vector<int> adj[MAXN];


int sum1(int u, int p, int* A) {
    int ans = -INF;
    for (int v : adj[u])
        if (v != p)
            ans = max(ans, A[v]);
    return ans;
}

int sum2(int u, int p, int* A, int* B) {

    int best = 0, sbest = 0, ans = -INF;
    B[0] = -INF;

    for (int v : adj[u]) {
        if (v!=p) {
            if (B[v] >= B[best]) {
                sbest = best;
                best = v;
            } else if (B[v] >= B[sbest]) {
                sbest = v;
            }
        }
    }

    if (best==0 || sbest==0) return ans;

    if (A==B) return A[best]+A[sbest];
    
    for (int v : adj[u]) {
        if (v!=p) {
            if (v!=best) ans = max(ans, A[v]+B[best]);
            else ans = max(ans, A[v]+B[sbest]);
        }
    }
    return ans;
}

int sum3(int u, int p, int* A, int* B) {
    int best=0, sbest=0, tbest=0;
    B[0] = -1;
    for (int v : adj[u]) {
        if (v!=p) {
            if (B[v] >= B[best]) {
                tbest = sbest;
                sbest = best;
                best = v;
            } else if (B[v] >= B[sbest]) {
                tbest = sbest;
                sbest = v;
            } else if (B[v] >= B[tbest]) {
                tbest = v;
            }
        }
    }

    if (!best || !sbest || !tbest) return -INF;
    
    if (A==B) return A[best]+A[sbest]+A[tbest];

    int ans = -INF;

    for (int v : adj[u]) {
        if(v!=p) {
            if (v==best) ans = max(ans, A[v]+ B[sbest]+B[tbest]);
            else if (v==sbest) ans = max(ans, A[v]+B[best]+B[tbest]);
            else  ans = max(ans, A[v]+B[best]+B[sbest]);
        }
    }
    return ans;
}


int sum4(int u, int p, int* A) {
    int best=0, sbest=0, tbest=0, fbest=0;
    A[0] = -INF;
    for (int v : adj[u]) {
        if (v!=p) {
            if (A[v] >= A[best]) {
                fbest=tbest;
                tbest = sbest;
                sbest = best;
                best = v;
            } else if (A[v] >= A[sbest]) {
                fbest=tbest;
                tbest = sbest;
                sbest = v;
            } else if (A[v] >= A[tbest]) {
                fbest=tbest;
                tbest = v;
            } else if (A[v] >= A[fbest]) {
                fbest=v;
            }
        }
    }
    if (!best || !sbest || !tbest || !fbest) return -INF;
    return A[best]+A[sbest]+A[tbest]+A[fbest];
}

void dfs1(int u, int p) {
    h[u] = 0;
    for (int v : adj[u]) {
        if (v!=p) {
            dfs1(v, u);
            if (h[u]+1+h[v] > dia[u]) {
                dia[u] = h[u]+1+h[v];
                if (dia[u] > diameter) diameter = dia[u];
            }
            if (h[v]+1 > h[u]) h[u] = h[v]+1;
        }
    } 
}

void dfs2(int u, int p) {
    for (int v : adj[u]) 
        if (v != p) dfs2(v, u);

    dia[u] = max(dia[u], sum1(u, p, dia));

    // connected 

    f[1][u] = 0; // begin

    f[1][u] = max(f[1][u], sum1(u, p, dia)); // 0 connections

    f[1][u] = max(f[1][u], 1+sum1(u, p, f[1])); // 1 connection in 1 subtree
    f[1][u] = max(f[1][u], 1+sum2(u, p, h, dia)); // 1 connection in 2 subtrees

    f[1][u] = max(f[1][u], dia[u]); // 2 connections in 2 subtrees

    f[1][u] = max(f[1][u], 3+sum3(u, p, h, h)); // 3 connections in 3 subtrees

    // disconnected

    f[0][u] = 0; // begin

    f[0][u] = max(f[0][u], sum1(u, p, f[0])); // 0 connections in 1 subtree
    f[0][u] = max(f[0][u], sum2(u, p, dia, dia) ); // 0 connections 2 subtrees

    f[0][u] = max(f[0][u], 1+sum1(u, p, f[1] )); // 1 connection 1 subtree
    f[0][u] = max(f[0][u], 1+sum2(u, p, h, dia)); // 1 connection 2 subtrees 

    f[0][u] = max(f[0][u], 2+sum2(u, p, h, f[1])); // 2 connections 2 subtrees
    f[0][u] = max(f[0][u], 2+sum3(u, p, dia, h)); // 2 connections 3 subtrees

    f[0][u] = max(f[0][u], 3+sum3(u, p, h, h)); // 3 connections 3 subtrees

    f[0][u] = max(f[0][u], 4+sum4(u, p, h)); // 4 connections 4 subtrees
}


int main() {
    // freopen("data.txt", "r", stdin);
    scanf("%d%d", &N, &K);
    for (int i = 0, A, B; i < N-1; ++i) {
        scanf("%d%d", &A, &B);
        adj[A].push_back(B);
        adj[B].push_back(A);
    }

    dfs1(1, 0);

    if (K==1) return !printf("%d\n", 2 * N - 1 - diameter );

    dfs2(1, 0);
    // for (int i = 1; i <= N; ++i) printf("node[%d]: dia = %d, connected = %d, dis = %d\n", i, dia[i], f[1][i], f[0][i]);
    
    printf("%d\n", 2*N-f[0][1]);

}

