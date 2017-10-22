#include <cstdio>
#include <vector>
#include <algorithm>
#define INF 1000000000
#define MAXN 1005
using namespace std;

int M, ds[MAXN], tmpN[10], tmpW[10];

struct edge {
    int w;
    vector<int> pens;
    edge() : w(INF), pens(vector<int>()) {}
    edge(int _w, vector<int> p) : w(_w), pens(p) {} 
    bool operator<(const edge& e) const {return w < e.w;}
} tmpe[MAXN][MAXN]; 

vector<edge> e;

int find(int x) {return ds[x]==x ? x : ( ds[x] = find(ds[x]) );}

int main() {
    // freopen("data.txt", "r", stdin);
    scanf("%d", &M);
    for (int p = 1; p <= M; ++p) {
        int sz;
        scanf("%d", &sz);
        for (int i = 0; i < sz; ++i) scanf("%d", tmpN+i);
        for (int i = 0; i < sz; ++i) scanf("%d", tmpW+i);
        
        for (int i = 0; i < sz; ++i){
            int n1 = min(tmpN[i], tmpN[(i+1)%sz]);
            int n2 = max(tmpN[i], tmpN[(i+1)%sz]);
            tmpe[n1][n2].pens.push_back(p);
            tmpe[n1][n2].w = tmpW[i];
        }
    }

    for (int i = 1; i <= M; ++i) ds[i] = i;

    for (int i = 0; i < MAXN; ++i) {
        for (int j = i+1; j < MAXN; ++j) {
            if (tmpe[i][j].w != INF) {
                if (tmpe[i][j].pens.size()==1) tmpe[i][j].pens.push_back(0);
                e.push_back( tmpe[i][j] );
            }
        }
    }

    sort(e.begin(), e.end());

    int cost1 = 0, tree1 = 0;
    for (int i = 0; i < (int) e.size() && tree1 < M; ++i) {
        int x = e[i].pens[0], y = e[i].pens[1];
        int xr = find(x), yr = find(y);
        if (xr != yr) {
            // printf("merging pens %d and %d with weight %d\n", x, y, e[i].w);
            cost1 += e[i].w;
            ds[yr] = xr;
            ++tree1;
        }
    }
    // printf("cost1 = %d\n", cost1);
    for (int i = 0; i <= M; ++i) ds[i] = i;
    
    int cost2 = 0, tree2 = 0;
    for (int i = 0; i < (int) e.size() && tree2 < M-1; ++i) {
        
        int x = e[i].pens[0], y = e[i].pens[1];
        if (x==0 || y==0) continue;
        int xr = find(x), yr = find(y);
        if (xr != yr) {
            cost2 += e[i].w;
            ds[yr] = xr;
            ++tree2;
        }
    }
    if (tree2 != M-1) cost2 = INF; 
    printf("%d\n", min(cost1, cost2));
}