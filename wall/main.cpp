#include <unordered_map>
#include <algorithm>
#define MAXK 500005

using namespace std;

unordered_map<int, int> map;
int pnts[MAXK<<1], tmp[MAXK<<1];

struct node {
    int l, r, lo, hi;
    bool lzylo, lzyhi;
    node() : l(0), r(0), lo(0), hi(0), lzylo(0), lzyhi(0) {}
} node[MAXK<<3];

void build(int u, int l, int r) {
    node[u].l = l, node[u].r = r;
    if (l!=r) {
        int m = (l+r)>>1;
        build(u<<1, l, m);
        build(u<<1|1, m+1, r);
    }
}

inline void lopush(int u, int w) {
    if (node[u].lo <= node[w].lo) return;
    node[w].lo = node[u].lo;
    if (node[w].hi < node[w].lo) {
        node[w].hi = node[w].lo;
        if (node[w].l != node[w].r) node[w].lzyhi = true;
    }
    if (node[w].l != node[w].r) node[w].lzylo = true;
}

inline void hipush(int u, int w) {
    if (node[u].hi >= node[w].hi) return;
    node[w].hi = node[u].hi;
    if (node[w].lo > node[w].hi) {
        node[w].lo = node[w].hi;
        if (node[w].l != node[w].r) node[w].lzylo = true;
    }
    if (node[w].l != node[w].r) node[w].lzyhi = true;
}

inline void lzypush(int u) {
    if (node[u].lzylo) {
        lopush(u, u<<1);
        lopush(u, u<<1|1);
    }
    if (node[u].lzyhi) {
        hipush(u, u<<1);
        hipush(u, u<<1|1);
    }
}

// op is 1 for set low, 2 for set high
void update(int u, int l, int r, int h, int op) {
    if (node[u].l > r || node[u].r < l) return;
    lzypush(u);

    if ( (op==1 && node[u].lo >= h) || (op==2 && node[u].hi <= h) ) return;

    if (l <= node[u].l && node[u].r <= r) {
        if (op==1) {
            node[u].lo = h;
            if (node[u].hi < node[u].lo) {
                node[u].hi = node[u].lo;
                if (node[u].l != node[u].r)
                    node[u].lzyhi = true;            
            }
            if (node[u].l != node[u].r)
                node[u].lzylo = true;
        } else {
            node[u].hi = h;
            if (node[u].lo > node[u].hi) {
                node[u].lo = node[u].hi;
                if (node[u].l != node[u].r)
                    node[u].lzylo = true;    
            }
            if (node[u].l != node[u].r)
                node[u].lzyhi = true;
        }
    } else {
        update(u<<1, l, r, h, op);
        update(u<<1|1, l, r, h, op);
        node[u].lo = min(node[u<<1|1].lo, node[u<<1].lo);
        node[u].hi = max(node[u<<1|1].hi, node[u<<1].hi);
    }

}

int query(int u, int x) {
    lzypush(u);
    if (node[u].l==node[u].r) return node[u].lo;
    int m = (node[u].l+node[u].r) >> 1;
    if (x <= m) return query(u<<1, x);
    else return query(u<<1|1, x);
}

void buildWall(int n, int k, int op[], int left[], int right[], int height[], int finalHeight[]) {

    for (int i = 0; i < k; ++i) tmp[i] = left[i], tmp[i+k] = right[i]+1;

    sort(tmp, tmp + 2 * k);

    int M = 1;
    pnts[1] = tmp[0];
    map[pnts[1]] = 1;
    for (int i = 1; i < 2*k; ++i) {
        if (tmp[i] != tmp[i-1]) {
            pnts[++M] = tmp[i];
            map[pnts[M]] = M;
        }
    }
    build(1, 1, M);
    for (int i = 0; i < k; ++i) update(1, map[left[i]], map[right[i]+1]-1, height[i], op[i]);

    for (int x = 0; x < pnts[1]; ++x) finalHeight[x] = 0;

    for (int i = 1; i <= M; ++i) {
        int h = query(1, i);
        for (int j = pnts[i]; j < pnts[i+1]; ++j) finalHeight[j] = h;
    }  

    for (int x = pnts[M]; x < n; ++x) finalHeight[x] = 0;

}

// int main() {
//     freopen("data.txt", "r", stdin);
//     int N, K;
//     int left[100], right[100], height[100], op[100], finalHeight[100];
//     scanf("%d%d", &N, &K);
//     for (int i = 0; i < K; ++i) scanf("%d%d%d%d", op+i, left+i, right+i, height+i);
//     buildWall(N, K, op, left, right, height, finalHeight);

//     printf("finalHeight:\n");
//     for (int i = 0; i < N; ++i) {
//         printf("%d ", finalHeight[i]);
//     }
//     printf("\n");
// }