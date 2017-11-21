/*input
5
0
1
2
3
4
*/
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
int n, nz;
vi ng, ps;
int main() {
    scanf("%d", &n);
    for (int i = 0, r; i < n; ++i) {
        scanf("%d", &r); 
        if (r>0) ps.push_back(r);
        else if (r<0) ng.push_back(r);
        else ++nz;
    }
    
    ll p = 1LL;
    for (int x : ps) p *= 1LL * x;
    for (int i = 0; i < ng.size()-1; ++i) p *= ng[i];
    if (p<0) p*=ng.back();

    
    // if (ng.empty() && ps.empty()) return !printf("0\n"); 
    // if (ng.size()==1 && n==1) return !printf("%d\n", ng[0]); 
    // if (ng.size()==1 && ps.empty()) return printf("0\n");
    // for (int x : ps) p *= 1LL * x;
    // if (ng.empty()) return !printf("%lld\n", p);
    // sort(begin(ng), end(ng)); 

    // for (int i = 0; i < ng.size()-1; ++i) p *= ng[i];
    // if (p<0) p*=ng.back();
    // printf("%lld\n", p);
}