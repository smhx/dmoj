#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>
#define MAXN 100005
#define INF 1000000
using namespace std;
typedef pair<int, int> ii;
int N, M, finish, levelcnt, lvl[MAXN], visited[MAXN], distend[MAXN],
    nxtzero[MAXN], p[MAXN], ord[MAXN], lstdig[MAXN];
vector<int> inlvl[MAXN];
vector<ii> adj[MAXN];

struct rel {
    int u, v, w;  // u is l, v is l-1, w is w(u, v)
    rel(int U, int V, int W) : u(U), v(V), w(W) {}
    rel() {}
    bool operator<(const rel& r) const {
        if (u == -1) return 0;
        if (r.u == -1) return 1;
        if (distend[u] == -1 && distend[r.u] != -1) return 0;
        if (distend[u] != -1 && distend[r.u] == -1) return 1;
        if (w != r.w) return w < r.w;
        if (ord[v] != ord[r.v]) return ord[v] < ord[r.v];
        if (distend[u] != -1) return distend[u] < distend[r.u];
        return 1;
    }
};

void getlevels() {
    printf("FUNCTION: getlevels\n");
    queue<int> q;
    q.push(0);
    lvl[0] = 0;
    visited[0] = 1;
    while (!q.empty()) {
        int u = q.front();
        printf("u = %d\n", u);
        q.pop();
        inlvl[lvl[u]].push_back(u);
        for (size_t i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i].second, w = adj[u][i].first;
            if (!visited[v]) {
                printf("    v = %d\n", v);

                lvl[v] = 1 + lvl[u];
                q.push(v);
                visited[v] = 1;
            }
        }
    }
    levelcnt = 0;
    for (int i = 0; i < N; ++i) levelcnt = max(levelcnt, lvl[i]);
    ++levelcnt;
}

void getends() {
    printf("FUNCTION: getends\n");
    queue<int> q;
    q.push(N - 1);
    memset(visited, 0, sizeof visited);
    memset(distend, -1, sizeof distend);
    distend[N - 1] = 0;
    while (!q.empty()) {
        int u = q.front();
        printf("u = %d\n", u);
        q.pop();
        visited[u] = 1;
        for (size_t i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i].second, w = adj[u][i].first;
            printf("  v=%d, w = %d\n", v, w);
            if (!visited[v] && w == 0) {
                printf("  real: v = %d\n", v);
                distend[v] = distend[u] + 1;
                nxtzero[v] = u;
                q.push(v);
            }
        }
    }
    nxtzero[N - 1] = N - 1;
}

void travel() {
    printf("FUNCTION travel\n");
    ord[0] = 0;
    for (int l = 1; l < levelcnt; ++l) {
        printf("l = %d\n", l);
        vector<rel> rels;
        for (size_t i = 0; i < inlvl[l].size(); ++i) {
            int u = inlvl[l][i];
            printf("  u = %d\n", u);
            ord[u] = -1;
            for (size_t j = 0; j < adj[u].size(); ++j) {
                int v = adj[u][j].second, w = adj[u][j].first;
                if (lvl[v] == l - 1) {
                    printf("    v = %d\n", v);
                    rels.push_back(rel(u, v, w));
                }
            }
        }
        sort(rels.begin(), rels.end());
        printf("after sorting\n");
        int k = 0, end = 0;
        // rels is empty!
        ord[rels[0].u] = 0;
        rel best = rel(-1, -1, -1);
        for (size_t i = 0; i < rels.size(); ++i) {
            int u = rels[i].u, v = rels[i].v, w = rels[i].w;
            printf("  u=%d, v=%d, w=%d\n", u, v, w);
            if (distend[u] != -1) {
                finish = u;
                printf("finish=%d\n", finish);
                p[finish] = v;
                lstdig[finish] = w;
                return;
            }
            if (ord[u] == -1) {
                if (!(!(rels[i] < best) && !(best < rels[i])))
                    best = rels[i], ++k;
                ord[u] = k;
                p[u] = v;
            }
        }
    }
}
int main() {
    freopen("data.txt", "r", stdin);
    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; ++i) {
        int a, b, len;
        scanf("%d%d%d", &a, &b, &len);
        adj[a].push_back(ii(len, b));
        adj[b].push_back(ii(len, a));
    }
    getlevels();
    printf("after getting levels\n");
    for (int u = 0; u < N; ++u) printf("lvl[%d]=%d\n", u, lvl[u]);
    getends();
    printf("after getting ends\n");
    for (int u = 0; u < N; ++u)
        printf("distend[%d]=%d, nxtzero[%d]=%d\n", u, distend[u], u,
               nxtzero[u]);
    travel();
    vector<int> path;
    for (int u = finish; u != 0; u = p[u]) {
        printf("pusing %d\n", u);
        path.push_back(u);
    }
    if (finish != 0) {
        printf("pusing 0\n");
        path.push_back(0);
    }
    reverse(path.begin(), path.end());
    for (int u = nxtzero[finish]; u != N - 1; u = nxtzero[u]) path.push_back(u);
    if (finish != N - 1) path.push_back(N - 1);
    if (finish)
        for (int u = finish; u != 0; u = p[u]) printf("%d", lstdig[u]);
    else
        printf("0");
    printf("\n");
    printf("%d\n", (int)path.size());
    for (size_t i = 0; i < path.size(); ++i) printf("%d ", path[i]);
    printf("\n");
}