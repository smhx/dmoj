#include <cstdio>
#include <vector>
using namespace std;
int N, M, ds[1000005];
vector<int> edges;

int find(int x) {
    return x==ds[x] ? x : (ds[x]=find(ds[x]));
}

bool merge(int x, int y) {
    int xr = find(x), yr = find(y);
    if (xr!=yr) {
        ds[yr]=xr;
        return true;
    }
    return false;
}

int main() {
	freopen("data.txt", "r", stdin);
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= M; ++i) ds[i] = i;
    for (int e = 1; e <= M && edges.size() < N-1; ++e) {
        int u, v; scanf("%d%d", &u, &v);
        if (merge(u, v)) edges.push_back(e);
    }
    if (edges.size()==N-1) 
        for (int e : edges) printf("%d\n", e);
    else printf("Disconnected Graph\n");
    
}
