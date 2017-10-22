#include <cstdio>
#include <set>
#define MAXN 100005
#define MAXA 103
using namespace std;
typedef pair<int, int> ii;
int N, S, Q, d[MAXN];
set<int> candy[MAXN];
set<ii> shops[MAXA];
char cmd;

int main() {
    // freopen("data.txt", "r", stdin);
    scanf("%d%d", &N, &S);
    for (int i = 1; i <= N; ++i) scanf("%d", d+i);
    for (int i = 0, s, a; i < S; ++i) {
        scanf("%d%d", &s, &a);
        candy[s].insert(a);
        shops[a].insert(ii(d[s], s));
    }

    scanf("%d", &Q);
    while (Q--) {
        scanf(" %c", &cmd);
        if (cmd=='Q') {
            int k; scanf("%d", &k);
            if (shops[k].empty()) printf("-1\n");
            else printf("%d\n", shops[k].begin()->second );
        } else {
            int x, k; scanf("%d%d", &x, &k);
            if (cmd=='A') {
                candy[x].insert(k);
                shops[k].insert(ii(d[x], x));
            } else if (cmd=='S') {
                candy[x].erase(k);
                shops[k].erase(ii(d[x], x));
            } else if (cmd=='E') {
                for (auto a : candy[x]) shops[a].erase(ii(d[x], x));
                candy[x].clear();
                d[x] = k;
            }
        }
    }
}
