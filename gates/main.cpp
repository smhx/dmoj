#include <cstdio>
#include <set>
using namespace std;
int G, P;
set<int> open;
int main() {
    // freopen("s3/s3.9.in", "r", stdin);
    scanf("%d%d", &G, &P);
    for (int i = 1; i <= G; ++i) open.insert(i);
    for (int i = 1; i <= P; ++i) {
        int x; scanf("%d", &x);
        if (open.empty() ) break;
        set<int>::iterator itr = open.upper_bound(x);
        if (itr==open.begin()) break;
        open.erase(--itr);
    }
    printf("%d\n", G-(int)open.size());
}
