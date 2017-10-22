#include <cstring>
#include <vector>
#define MAXN 400005

// #define getchar() (*_pbuf ? *_pbuf++ : (_buf[fread_unlocked(_pbuf = _buf, 1, 1048576, stdin)] = 0, *_pbuf++))
char _buf[1048577], *_pbuf = _buf;

int readint() {
        int c, o = 0;
        while ((c = getchar()) < '0');
        do {
                o = o * 10 + (c - '0');
        } while ((c = getchar()) >= '0');
        return o;
}

using namespace std;
typedef long long ll;

int N, p[MAXN], endcnt[MAXN], h[MAXN];
vector<int> adj[MAXN];

void dfs1(int u, int& f) {
    if (h[u] > f) f = h[u];

    for (int v : adj[u]) {
        if (h[v] == -1 && v != p[u]) {
            p[v] = u;
            h[v] = 1 + h[u];
            dfs1(v, f);
        }
    }
}

void dfs2(int u, int far, int& w) {
    for (int v : adj[u]) {
        if (v != p[u]) {
            dfs2(v, far, w);
            endcnt[u] += endcnt[v];
        }
    }
    if (h[u] == far) ++endcnt[u];
    if (endcnt[u] > endcnt[w]) w = u;
}

ll within(int w, int pw) {
    ll totalSum = 0, toret = 0;
    for (int u : adj[w])
        if (u != pw) totalSum += endcnt[u];
    for (int u : adj[w])
        if (u != pw) toret += (ll)endcnt[u] * ll(totalSum - endcnt[u]);
    return toret >> 1;
}

int main() {
    N = readint();
    for (int i = 0, a, b; i < N - 1; ++i) {
        a = readint(); b = readint();
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int d1 = 0, d2 = 0, pw = 0, cnt1 = 0, cnt2 = 0, hw = 0, w = 0;
    ll cnt = 0;

    memset(h, -1, sizeof(int) * (N + 1));

    h[1] = 0;
    dfs1(1, d1);

    for (int u = 1; u <= N; ++u)
        if (h[u] == d1) ++cnt1;

    dfs2(1, d1, w);

    hw = h[w], pw = p[w];

    memset(h, -1, sizeof(int) * (N + 1));
    memset(p, 0, sizeof(int) * (N + 1));

    h[w] = -2, h[pw] = 0;
    dfs1(pw, d2);

    for (int u = 1; u <= N; ++u)
        if (h[u] == d2) ++cnt2;

    d2 += 1 + d1 - hw;

    if (d2 > 2 * (d1 - hw))
        cnt = ll(cnt1) * ll(cnt2);
    else if (d2 == 2 * (d1 - hw))
        cnt = within(w, pw) + ll(cnt1) * ll(cnt2);
    else
        cnt = within(w, pw), d2 = 2 * (d1 - hw);

    printf("%d %lld\n", d2 + 1, cnt);
}
