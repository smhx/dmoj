#include <cstdio>
#include <vector>
#define MAXN 500005
using namespace std;

typedef pair<int, int> ii;

int N, K;
vector<ii> adj[MAXN];

int main() {
    scanf("%d%d", &N, &K);
    for (int i = 0, w, a, b; i < K; ++i) {
        scanf("%d%d%d", &a, &b, &w);
        adj[a].push_back(ii(w, b));
        adj[b].push_back(ii(w, a));
    }
}