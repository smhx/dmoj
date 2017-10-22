#include <cstdio>
#include <vector>
#include <cstring>
#define MAXN 1000005

#ifdef ONLINE_JUDGE
#define getchar() (*_pbuf ? *_pbuf++ : (_buf[fread_unlocked(_pbuf = _buf, 1, 1048576, stdin)] = 0, *_pbuf++))
char _buf[1048577], *_pbuf = _buf;
#endif

int readint() {
	int c, o = 0;
	while ((c = getchar()) < '0');
	do {
		o = o * 10 + (c - '0');
	} while ((c = getchar()) >= '0');
	return o;
}

using namespace std;

int N, M, p, q, visit[MAXN];
vector<int> adj[MAXN];
bool dfs(int x, int t) {
    vector<int> s;
    s.push_back(x);
    while (!s.empty()) {
        int u = s.back(); s.pop_back();
        visit[u] = 1;
        for (size_t i = 0; i < adj[u].size(); ++i) {
            if (adj[u][i]==t) return true;
            if (!visit[adj[u][i]]) s.push_back(adj[u][i]);
        }
    }
    return false;
}
int main() {
    freopen("data.txt", "r", stdin);
    N = readint(); M = readint();
    for (int i = 0, a, b; i < M; ++i) {
        a = readint(); b = readint();
        adj[b].push_back(a); // edge from b to a iff a is taller than b
    }
    // scanf("%d%d", &p, &q);
    p = readint(); q = readint();
    if (dfs(q, p)) printf("yes\n");
    else {
        memset(visit, 0, sizeof(int) * (N+1));
        if (dfs(p, q)) printf("no\n");
        else printf("unknown\n");
    }
}