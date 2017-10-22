#include <cstdio>
#include <stack>
#include <algorithm>
#define MAXN 1000005
using namespace std;
typedef pair<int, int> ii;

int N, Q, A[MAXN], bit[MAXN], ans[MAXN];
struct query {
    int l, r, id;
    bool operator< (const query& q) const {
        return l != q.l ? l > q.l : r > q.r;
    }
} queries[MAXN];

void update(int x, int v) {
    for (; x <= N; x += x&-x) bit[x] += v;
}

int sum(int x) {
    int ret = 0;
    for (; x; x-=x&-x) ret += bit[x];
    return ret;
}

int main() {
    // freopen("data.txt", "r", stdin);    
    scanf("%d%d", &N, &Q);
    for (int i = 1; i <= N; ++i) scanf("%d", A+i);
    for (int i = 0; i < Q; ++i) {
        scanf("%d%d", &queries[i].l, &queries[i].r);
        queries[i].id = i;
    }
    sort(queries, queries+Q);
    stack<int> s;
    for (int i = 0, x = N; i < Q; ++i) {
        while (x >= queries[i].l) {
            while (!s.empty() && A[s.top()] < A[x]) {
                update(s.top(), -1);
                s.pop();
            }
            s.push(x);
            update(x, 1);
            --x;
        }
        ans[queries[i].id] = sum(queries[i].r);
    }
    for (int i = 0; i < Q; ++i) printf("%d\n", ans[i]);

}