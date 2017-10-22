#include <cstdio>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <cstring>
#define MAXN 500005
#define MOD 1000000007

using namespace std;
typedef long long ll;
typedef vector<ll> vll;
unordered_map<ll, int> map;

int N, M;
ll l[MAXN], r[MAXN], h[MAXN], area=0;
vll tpnts, pnts;

ll t[8*MAXN], lazy[8*MAXN];

ll query(int u, int tl, int tr, int l, int r) {
    if (tl > r || tr < l) return -MOD;
    if (lazy[u] != -1) {
        t[u<<1] = t[u<<1|1] = lazy[u<<1] = lazy[u<<1|1] = lazy[u];
        lazy[u] = -1;
    }
    if (l <= tl && tr <= r) return t[u];
    int m = (tl+tr) >> 1;
    return max(query(u<<1, tl, m, l, r), query(u<<1|1, m+1, tr, l, r) );
}

void update(int u, int tl, int tr, int l, int r, int v) {
    if (tl > r || tr < l) return;
    if (lazy[u] != -1) {
        t[u<<1] = t[u<<1|1] = lazy[u<<1] = lazy[u<<1|1] = lazy[u];
        lazy[u] = -1;
    }
    if (l <= tl && tr <= r) {
        lazy[u] = t[u] = v;
        return;
    }
    int m = (tl+tr) >> 1;
    update(u<<1, tl, m, l, r, v);
    update(u<<1|1, m+1, tr, l, r, v);    
    t[u] = max(t[u<<1], t[u<<1|1]);
}

int main() {
    // freopen("data.txt", "r", stdin);
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%lld %lld %lld", l+i, r+i, h+i);
        r[i] += l[i];
        tpnts.push_back(l[i]);
        tpnts.push_back(r[i]);
    }
    sort(tpnts.begin(), tpnts.end());
    pnts.push_back(tpnts[0]);

    for (size_t i = 1; i < tpnts.size(); ++i) 
        if (tpnts[i] != tpnts[i-1]) pnts.push_back(tpnts[i]);

    M = (int)pnts.size();
    // printf("pnts: ");
    // for (int i = 0; i < M; ++i) printf("%lld ", pnts[i]);
    // printf("\n");
    for (int i = 0; i < M; ++i) map[pnts[i]] = i;

    memset(lazy, -1, sizeof lazy);

    for (int i = 0; i < N; ++i) {
        int H = query(1, 0, M-1, map[l[i]], map[r[i]]-1);
        // printf("H is %d from query with l = %d, r = %d\n", H, map[l[i]], map[r[i]] - 1);
        update(1, 0, M-1, map[l[i]], map[r[i]]-1, H+h[i]);
        // printf("After updating %d %d to %d, t is now:\n", map[l[i]], map[r[i]]-1, H+h[i]);
        // for (int i = 1; i <= 2 * M+1; ++i ) printf("t[%d] = %d, lazy[%d]=%d\n", i, t[i], i, lazy[i]);
    }

    // for (int u = 1; u <= M; ++u) {
    //     if (lazy[u] != -1) {
    //         t[u<<1] = t[u<<1|1] = lazy[u<<1] = lazy[u<<1|1] = lazy[u];
    //         lazy[u] = -1;
    //     }
    // }
    for (int i = 0; i < pnts.size()-1; ++i) {
        // printf("querying at point %d: %d\n", i, query(1, 0, M-1, i, i));
        area +=  ( (pnts[i+1]-pnts[i]) * query(1, 0, M-1, i, i) ) % MOD;
        area %= MOD;
        // printf("\n\n");
        // for (int i = 1; i <= 2 * M+1; ++i ) printf("t[%d] = %d, lazy[%d]=%d\n", i, t[i], i, lazy[i]);
    }
    for (int i = 0; i < N; ++i) {
        area -= ( (r[i]-l[i]) * h[i] )%MOD;
        area %= MOD;
    }

    if (area < 0) area += MOD;

    printf("%lld\n", area);
    
}