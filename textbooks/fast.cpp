#include <cstdio>
#include <algorithm>
#include <vector>
#include <unordered_map>
#define MAXN 500005
#define MOD 1000000007
using namespace std;
typedef long long ll;

unordered_map<int, int> map;

int N, M, H, area = 0, l[MAXN], r[MAXN], h[MAXN], lzy[2*MAXN], t[4*MAXN];
vector<int> tpnts, pnts;

inline void apply(int u, int v) {
    t[u] = v;
    if (u < M) lzy[u] = v;
}

void build(int u) {
    for (; u > 1; u >>= 1) if (lzy[u>>1]==-1) t[u>>1] = max(t[u], t[u^1]);
}

void push(int p) {
    for (int s = H; s > 0; --s) {
        int i = p >> s;
        if (lzy[i] != -1) {
            apply(i<<1, lzy[i]);
            apply(i<<1|1, lzy[i]);
            lzy[i] = -1;
        }
    }
}
  

int query(int l, int r) {
    l += M, r += M;
    push(l); push(r-1);
    int ans = -MOD;
    for (; l < r; l >>= 1, r >>= 1) {
        if (l&1) ans = max(ans, t[l++]);
        if (r&1) ans = max(ans, t[--r]);
    }
    return ans;
}

void update(int l, int r, int v) {
    l += M, r += M;
    int a = l, b = r;
    for (; l < r; l >>= 1, r >>= 1) {
        if (l&1) apply(l++, v);
        if (r&1) apply(--r, v);
    }
    build(a);
    build(b-1);
}

void clean() {
    for (int i = 0; i < M; ++i) {
        if (lzy[i] != -1) {
            apply(i<<1, lzy[i]);
            apply(i<<1|1, lzy[i]);
            lzy[i] = -1;
        }
    }
}


int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%d %d %d", l+i, r+i, h+i);
        r[i] += l[i];
        tpnts.push_back(l[i]);
        tpnts.push_back(r[i]);
    }
    sort(tpnts.begin(), tpnts.end());
    pnts.push_back(tpnts[0]);
    for (size_t i = 1; i < tpnts.size(); ++i) 
        if (tpnts[i] != tpnts[i-1]) pnts.push_back(tpnts[i]);
    M = (int) pnts.size();
    for (int i = 0; i < M; ++i) map[pnts[i]] = i, lzy[i] = -1;
    H = sizeof(int) * 8 - __builtin_clz(M);
    for (int i = 0; i < N; ++i) 
        update(map[l[i]], map[r[i]], query(map[l[i]], map[r[i]]) + h[i] );
    clean();
    for (size_t i = 0; i < pnts.size() - 1; ++i) 
        area = (area + (  ll(pnts[i+1] - pnts[i]) * ll(t[i+M])  )%MOD)%MOD;
    for (int i = 0; i < N; ++i) 
        area = (area - (ll(h[i])*ll(r[i]-l[i]))%MOD)%MOD;
    if (area < 0) area += MOD;
    printf("%d\n", area);
}