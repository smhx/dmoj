#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 100005;

int N, M, B[MAXN], C[MAXN], L[MAXN], root;

ll mx = 0;

vector<int> ch[MAXN];

int cnt(const vector<int>& v) {
    int num = 0, sum = 0;
    while (1) {
        if (num >= v.size() || sum + v[num] > M) break;
        sum += v[num];
        ++num;
    }
    
    return num;
}

vector<int> dfs(int u) {
    vector<int> a;
    a.push_back(C[u]);
    for (int v : ch[u]) {
        vector<int> b = dfs(v); 
        vector<int> tmp;
        merge(a.begin(), a.end(), b.begin(), b.end(), back_inserter(tmp));
        a = tmp;
    }
    
    mx = max(mx, 1LL * L[u] * cnt(a));
   
    return a;
}

int main() {
    // freopen("data.txt", "r", stdin);
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; ++i ) {
        scanf("%d%d%d", B+i, C+i, L+i);
        if (B[i]==0) root = i;
        else ch[B[i]].push_back(i);
    }

    dfs(root);
    printf("%lld\n", mx);
}