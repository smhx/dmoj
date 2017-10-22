#include <cstdio>
#include <vector>
#include <cstring>
#define MAXN 100005
using namespace std;
int N, q[MAXN], p[MAXN], m[MAXN][2], M[MAXN][2];
char s[3];
vector<int> roots, children[MAXN];

inline int score() {
    if (strcmp(s, "WA")==0) return 0;    
    if (strcmp(s, "AC")==0) return 1;    
    return 2;
}

void solve(int u) {
    for (size_t i = 0; i < children[u].size(); ++i) solve(children[u][i]);
    for (int t = 0; t < 2; ++t) {
        for (size_t i = 0; i < children[u].size(); ++i) {
            int v = children[u][i];
            if (q[v] != 2) {
                m[u][t] += (t!=q[v]) + m[v][t==q[v]];
                M[u][t] += (t!=q[v]) + M[v][t==q[v]];
            } else {
                
                m[u][t] += min(m[v][1], 1+m[v][0]);
                M[u][t] += max(M[v][1], 1+M[v][0]);
            }
        }
    }
}

int main() {
    freopen("data.txt", "r", stdin);
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) {
        char cmd; scanf(" %c", &cmd);
        if(cmd=='C'){
            scanf(" %s", s);
            q[i] = score();
            roots.push_back(i);
        } else {
            int v; scanf("%d %s", &v, s);
            q[i] = score();
            p[i] = v;
            children[v].push_back(i);
        }
    }
  
    int lo=0, hi=0;
    for (size_t i = 0; i < roots.size(); ++i) {
        int r = roots[i];
        solve(r);
        if (q[r] != 2) {
            lo += m[r][q[r]] + !q[r];
            hi += M[r][q[r]] + !q[r];
        } else {
            lo += min(m[r][0]+1, m[r][1]);
            hi += max(M[r][0]+1, M[r][1]);
        }
    }
   
    printf("%d %d\n", lo, hi);

    
}