#include <cstdio>
#include <vector>
#define MAX 1048576
#define INF 1000000000
using namespace std;
int m, n, a, b, c, start=0;
char ch;
vector<int> pre[MAX];
bool visit[MAX];

inline int on(int x, int p) {
    return (x & (1<<p)) ? 1 : 0;
}

int nxt(int x) {
    int y = x;
    for (int R = 0; R < m; ++R) {
        for (int C = 0; C < n; ++C) {
            int adja = 0;
            for (int i = -1; i <= 1; ++i) 
                for (int j = -1; j <= 1; ++j) 
                    if ( (i || j) && R+i >= 0 && R+i < m && C+j >= 0 && C+j < n) 
                        adja += on(x, n*(R+i)+(C+j) );
            
            if (  x&(1<<(n*R+C)) ) {
                if (adja < a || adja > b) y -= 1<<(n*R+C); 
            } else {
                if (adja > c) 
                    y += 1<<(n*R+C);
            }
        }
    }
    return y;
}

int dfs(int u) {
    if (visit[u]) return INF;
    visit[u] = 1;
    if (pre[u].empty()) return 0;
    int m = INF;
    for (int v : pre[u]) m = std::min(m, 1+dfs(v));
    return m;
}

int main() {
    // freopen("data.txt", "r", stdin);
    scanf("%d%d%d%d%d", &m, &n, &a, &b, &c); 
    for (int i = 0; i < m*n; ++i) {
        scanf(" %c", &ch);
        if (ch=='*') start |= (1<<i);
    }
    // There can be a cycle?
    for (int x = 0; x < 1 << (m*n); ++x) pre[nxt(x)].push_back(x);
    printf("%d\n", dfs(start));
}