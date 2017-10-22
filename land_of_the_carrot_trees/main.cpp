#include <cstdio>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cstring>
#include <unordered_set>
#define MAXN 100005
#define GSZ 1000
#define NG 105
using namespace std;

struct command {char c; int x, y, z;};

vector<command> group[NG];

int N, Q, ingroup[MAXN], xorval[MAXN], gpar[MAXN], gvisit[MAXN];

unordered_map<int, int> gadj[MAXN];
unordered_map<int, int> adj[MAXN];

void dfs1(int u, int xr, int p, int gp) {
    gvisit[u] = 1;
    xorval[u] = xr;
    gpar[u]=gp;
    if (ingroup[u]) {
        xr = 0;
        gp = u;
    }
    for (auto pair : adj[u]) {
        int v = pair.first, w = pair.second;
        if (v==p) continue;
        dfs1(v, xr^w, u, gp);
    }
}

bool dfs2(int u, int p, int dest, int& w) {
    if (u==dest) return true;
    for (auto pair : gadj[u]) {
        int v = pair.first; 
        if (v==p) continue;
        if (dfs2(v, u, dest, w)) {
            w ^= pair.second;
            return true;
        }
    }
    return false;
}

int main() {
    scanf("%d%d", &N, &Q);
    for (int i = 0, a, b, c; i < N-1; ++i) {
        scanf("%d%d%d", &a, &b, &c);
        adj[a][b] = c;
        adj[b][a] = c;
    }
    for (int i = 0; i < Q; ++i) {
        char c; int x, y, z=0;
        scanf(" %c%d%d", &c, &x, &y);
        if (c=='A') scanf("%d", &z);
        group[i/GSZ].push_back({c, x, y, z});
    }

    for (int g = 0; !group[g].empty(); ++g) {
        for (int i = 1; i <= N; ++i) gadj[i].clear();
        memset(ingroup, 0, sizeof ingroup);
        memset(xorval, 0, sizeof xorval);
        memset(gpar, -1, sizeof gpar);
        memset(gvisit, 0, sizeof gvisit);
        for (auto c : group[g]) 
            ingroup[c.x]=ingroup[c.y]=1;

        for (int u = 1; u <= N; ++u) 
            if (ingroup[u] && !gvisit[u]) 
                dfs1(u, 0, -1, -1);

        for (int u = 1; u <= N; ++u) {
            if (gpar[u]!=-1 && ingroup[u]) {
                gadj[u][gpar[u]] = xorval[u];
                gadj[gpar[u]][u] = xorval[u];
            }
        }

        for (auto c : group[g]) {
            if (c.c=='A') {
                gadj[c.x][c.y]=c.z;
                gadj[c.y][c.x] = c.z;

                adj[c.x][c.y] = c.z;
                adj[c.y][c.x] = c.z;

            } else if (c.c=='R') {
                gadj[c.x].erase(c.y);
                gadj[c.y].erase(c.x);

                adj[c.x].erase(c.y);
                adj[c.y].erase(c.x);
            } else {
                int w=0;
                if (dfs2(c.x, -1, c.y, w)) printf("%d\n", w);
                else printf("-1\n");
            }
        }
    }
}