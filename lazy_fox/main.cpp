#include <algorithm>
#include <cstdio>
#include <vector>
#define MAXN 2005
#define INF 1000000000
#define getchar() (*_pbuf ? *_pbuf++ : (_buf[fread(_pbuf = _buf, 1, 1024, stdin)] = 0, *_pbuf++))
char _buf[1025], *_pbuf = _buf;

int readint() {
	int c, o = 0, sign=1;
	while (1) {
        c = getchar(); 
        if (c=='-' || c>='0') break;
    }
    if (c=='-') {
        sign=-1;
        c = getchar();
    }
	do {
		o = (o<<3)+(o<<1) + (c - '0');
	} while ((c = getchar()) >= '0');
	return o*sign;
}

using namespace std;
typedef pair<int, int> ii;
int N, d[MAXN][MAXN], X[MAXN], Y[MAXN], dp[MAXN][MAXN];
int b[MAXN], sb[MAXN], bd[MAXN];

vector< pair<int,ii> > order;

int main() {
    N = readint();
    for (int i = 1; i <= N; ++i) {
        X[i] = readint(); Y[i] = readint();
    }
    for (int i = 0; i < N; ++i)
        for (int j = i+1; j <= N; ++j) 
            d[i][j] = (X[i] - X[j]) * (X[i] - X[j]) + (Y[i] - Y[j]) * (Y[i] - Y[j]);
        
    for (int i = 0; i < N; ++i)
        for (int j = i+1; j <= N; ++j)
            order.push_back({d[i][j], ii(i, j)});

    sort(order.begin(), order.end());
    for (int i = 0; i <= N; ++i) bd[i] = INF;

    for (size_t i = 0; i < order.size(); ++i) {
        int p = order[i].second.first, u = order[i].second.second;
        int dist = d[p][u];
        for (int k = 0; k < 2; ++k) {
            if (k) swap(u, p);
            if (!u) break;
            dp[p][u] = dist > bd[u] ? dp[p][u] = 1 + b[u] : 1 + sb[u];
            if (dp[p][u] > b[p]) {
                if (bd[p] < dist) sb[p] = b[p];
                b[p] = dp[p][u];
                bd[p] = dist;
            } else if (dp[p][u] == b[p] && bd[p] > dist)
                bd[p] = dist;
            else if (dp[p][u] < b[p] && bd[p] < dist && dp[p][u] > sb[p]) 
                sb[p] = dp[p][u];
        }
    }
    int ans = 0;
    for (int u = 1; u <= N; ++u) ans = max(ans, dp[0][u]);
    printf("%d\n", ans);
}