#include <algorithm>
#include <cstdio>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>
#define mp make_pair
#define MAXN 100005
#define INF 1000000
using namespace std;

int N, M;
int place[MAXN], visited[MAXN], nxtzero[MAXN], numzero[MAXN], lstdig[MAXN],
    onqueue[MAXN], bfsp[MAXN];
// you have a node u. You need the jjj

vector<pair<int, int> > ord[MAXN];  // ord[l][i] holds the pair (u, order).
vector<pair<int, int> > adj[MAXN];
vector<int> path;
void zero() {
    for (int i = 0; i < N; ++i) nxtzero[i] = -1;
    queue<int> q;
    q.push(N - 1);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        visited[u] = 1;
        for (int i = 0; i < (int)adj[u].size(); ++i) {
            int v = adj[u][i].first, w = adj[u][i].second;
            if (w == 0 && !visited[v]) {
                nxtzero[v] = u;
                numzero[v] = 1 + numzero[u];
                q.push(v);
            }
        }
    }
    nxtzero[N - 1] = N - 1;
}

int cmp(int u, int v, int w) {
    pair<int, int> p = make_pair(u, v);
    if (nxtzero[v] != -1) {
        while (lstdig[v] == 0 && v != 0) v = bfsp[v];
        while (w == 0 && u != 0) w = lstdig[u], u = bfsp[u];
    }
    if (place[u] + 1 != place[v])
        return (place[u] + 1 < place[v]) ? 1 : -1;
    else if (w != lstdig[v])
        return (w < lstdig[v]) ? 1 : -1;
    return cmp(bfsp[u], bfsp[v], lstdig[u]);
}

void travel() {
    for (int i = 0; i < N; ++i) visited[i] = 0, lstdig[i] = INF, place[i] = INF;
    queue<int> q;
    q.push(0);
    place[0] = 0;
    lstdig[0] = 0;
    int curlevel = 0;
    ord[0].push_back(mp(0, 0));
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        visited[u] = 1;
        printf("Searching %d\n", u);
        if (nxtzero[u] == -1) {
            for (int i = 0; i < (int)adj[u].size(); ++i) {
                int v = adj[u][i].first, w = adj[u][i].second;
                if (visited[v]) continue;
                printf("looking at %d\n", v);
                if (!onqueue[v]) q.push(v), onqueue[v] = 1;
                if (cmp(u, v, w) == 1) {
                    lstdig[v] = w;
                    bfsp[v] = u;
                    place[v] = 1 + place[u];
                    printf("cmp is 1\n");
                } else {
                    printf("cmp is 0 or -1\n");
                }
            }
        } else {
            int v = nxtzero[u], rel = cmp(u, v, 0);
            printf("u is zero reachable. looking at v=%d, rel is %d\n", v, rel);
            if (rel == 1 || (rel == 0 && numzero[u] + 1 < numzero[v])) {
                lstdig[v] = 0, bfsp[v] = u, numzero[v] = numzero[u] + 1;
                q.push(v);
            }
        }
    }
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; ++i) {
        int a, b, len;
        scanf("%d%d%d", &a, &b, &len);
        adj[a].push_back(mp(b, len));
        adj[b].push_back(mp(a, len));
    }
    zero();
    travel();
    for (int i = 0; i < N; ++i) {
        printf("lstdig[%d]=%d, place[%d]=%d, nxtzero[%d]=%d\n", i, lstdig[i], i,
               place[i], i, nxtzero[i]);
    }
    int x = N - 1, start = 0, found = 0;
    for (int i = 0;; ++i) {
        if (x == 0) break;
        if (lstdig[x] != 0 && !found) start = i, found = 1;
        path.push_back(x);
        x = bfsp[x];
    }
    if (!found)
        printf("0");
    else {
        for (int i = start; i < (int)path.size(); ++i)
            printf("%d", lstdig[path[i]]);
    }
    printf("\n%d\n0 ", (int)path.size() + 1);
    for (int i = (int)path.size() - 1; i >= 0; --i) {
        printf("%d ", path[i]);
    }
    printf("\n");
}
