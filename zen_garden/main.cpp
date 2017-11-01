/*input
4
5 10 15 20
2
1 30
3 4
*/
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 100005;
int N, M, med[MAXN], a, d, harmony = 0;
int main() {
    scanf("%d", &N);
    
    for (int i = 1; i <= N; ++i) {
        scanf("%d", med+i);
        harmony += med[i];
    }

    scanf("%d", &M);
    
    while (M--) {
        scanf("%d %d", &a, &d);
        harmony -= min(min(med[a], med[a+1]), d);
    }
    printf("%d\n", harmony);
}