
#include <cstdio>
#include <vector>
#include <algorithm>
#define MAX_W 20000
using namespace std;
typedef long long ll;
vector<int> idx[MAX_W+1], wts[MAX_W+1];
vector<ll> pre[MAX_W+1];
int N, Q;
inline int trans(int w) {return MAX_W-w+1;}
void insert(int q, int i) {
    for (int w=q; w<=MAX_W; w+=w&-w) {
        idx[w].push_back(i);
        wts[w].push_back(q);
    }
}
void precomp(int w) {
    for (int i = 0; i < wts[w].size(); ++i) {
        if (i) pre[w].push_back(pre[w].back()+trans(wts[w][i]));
        else pre[w].push_back(trans(wts[w][i]));
    }
}
int edge(int w, int i) {
    return -1+(upper_bound(idx[w].begin(), idx[w].end(), i)-idx[w].begin());
}
ll sum(int w, int i) {
    ll s=0;
    for (; w>0; w-=w&-w) {
        int bound=edge(w, i);
        if (bound>=0) s += pre[w][bound];
    }
    return s;
}
int main() {
    scanf("%d", &N);
    for (int i = 0, w; i < N; ++i) {
        scanf("%d", &w);
        insert(trans(w), i);
    }
    for (int i = 1; i <= MAX_W; ++i) precomp(i);
    scanf("%d", &Q);
    while (Q--) {
        int a, b, q;
        scanf("%d%d%d", &a, &b, &q);
        q = trans(q);
        printf("%lld\n", sum(q, b)-sum(q, a-1));
    }
}
