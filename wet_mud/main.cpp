#include <cstdio>
#include <algorithm>
#define MAXN 100005
using namespace std;
typedef pair<int,int> ii;
int N, M, J, jump[MAXN];

ii patch[MAXN];

int main() {
    scanf("%d%d%d", &N, &M, &J);
    

    for (int i = 0; i < M; ++i) 
        scanf("%d%d", &patch[i].second, &patch[i].first);
    sort(patch, patch+M);
    for (int i = 0; i <= N+1; ++i) jump[i] = (i+J <= N) ? i : N+1;
    
    int pos = 0;
    
    if (jump[0] > N) {
        printf("0\n");
        return 0;
    }

    for (int i = 0; i < M; ++i) {
        int x = patch[i].second;
        if (x <= pos) continue;
        for (int j = x-J; j < x; ++j) 
            if (jump[j] < x) jump[j] = x;
        while (pos != jump[pos]) {
            pos = jump[pos];
            if (pos > N) {
                printf("%d\n", patch[i].first);
                return 0;
            }
        }
        
        
    }
    printf("-1\n");
    return 0;
}



