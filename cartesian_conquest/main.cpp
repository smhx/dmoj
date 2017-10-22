#include <cstdio>
#include <algorithm>
#include <unordered_map>
using namespace std;
#define INF 1000000000
#define mp make_pair

typedef pair<int, int> ii;
struct ii_hash {
    size_t operator() (const ii& x) const {
        return hash<long long>() ( ( (long long)x.first )^( (long long)x.second ) << 32 );
    }
};

unordered_map<ii, ii, ii_hash> mem;
inline bool contains(unordered_map<ii, ii, ii_hash>& m, int x, int y) {return m.find(mp(x,y))!=m.end();} 

inline ii optimal(ii a, ii b) {
    return mp(min(a.first, b.first), max(a.second, b.second) );
}

ii sol(int x, int y) {
    if (x > y) swap(x, y);
    ii ans = mp(INF, -INF);
    if(x%2==1 && y%2==1) return ans;
    if (x==0) return mp(0, 0);
    if (contains(mem, x, y)) return mem[mp(x,y)];
    if (y <= 2*x) {
        if (x%2==0) ans = optimal(ans, sol(x, y-(x/2) ));
        if (y%2==0) ans = optimal(ans, sol(x-(y/2), y));
        return mem[mp(x,y)]=mp(ans.first+1, ans.second+1);
    } else {
        int n = y/(2*x);
        ii tmp = sol(x, y-n*2*x);
        ans = optimal(ans, mp(tmp.first+n, tmp.second+n));
        if (x%2==0) {
            int n = 2*y/x-3; 
            tmp = sol(x,y-n*x/2);
            ans = optimal(ans, mp(tmp.first+n/4+n%4, tmp.second+n));
        }
        return mem[mp(x,y)]=ans;
    }
}

int main(){
    int x,y;
    scanf("%d%d",&x,&y);
    ii ans = sol(x,y);
    printf("%d %d\n", ans.first, ans.second);
}