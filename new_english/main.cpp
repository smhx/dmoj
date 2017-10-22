#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#define MAXN 100005
#define ALPHA 26
using namespace std;

int N, M, cnt[ALPHA], last[ALPHA], mark[ALPHA];
char word[MAXN];
struct demand {
    int idx, x;
    char c;
    bool operator<(const demand& d) const {
        return (idx != d.idx) ? idx < d.idx : x > d.x;
    }
} demands[MAXN];

int main() {
    // freopen("data.txt", "r", stdin);
    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; ++i) {
        scanf(" %c %d %d", &demands[i].c, &demands[i].x, &demands[i].idx);
    }

    sort(demands, demands+M);
    memset(word, 0, sizeof word);
    memset(last, 0, sizeof last);
    memset(cnt, 0, sizeof cnt);

    int j = 1;
    for (int i = 0; i < M; ++i) {
        char c = demands[i].c;
        int idx = demands[i].idx;        
        int x = demands[i].x;

        bool jump =  false;
        int need = x-cnt[c-'a'];
        // printf("c = %c, idx = %d, x = %d, j = %d, need = %d\n", c, idx, x,j,need);
        
        if (need < 0) {
            
            // printf("need = %d, -1\n", need);
            printf("-1\n");
            return 0;
        }
        int k = j;
        if (j <= last[c-'a']) k = last[c-'a']+1, jump = true;

        // printf("c = %c, idx = %d, x = %d, k = %d, j = %d\n", c, idx, x, k, j);
        
        while (need--) {
            while (word[k]) ++k;
            // printf("    k = %d\n", k);
            if (k > idx) {
                // printf("k = %d, idx = %d, -1\n", k, idx);
                printf("-1\n");
                return 0;
            }
            word[k] = c;
            ++k;
        }
        cnt[c-'a'] = x;
        // printf("cnt[%d] = %d\n", c-'a', cnt[c-'a']);
        
        last[c-'a'] = idx;
        if (!jump) for (j = k; word[j]; ++j);
    }

    char filler = 0;
    for (int i = 0; i < M; ++i) 
        if (j <= demands[i].idx) mark[demands[i].c-'a'] = 1;
    
    for (int i = 0; i < ALPHA && !filler; ++i) if (!mark[i]) filler = i+'a';
    
    for (; j <= N; ++j) {
        if (!filler) {
            printf("-1\n");
            return 0;
        }
        if (!word[j]) word[j] = filler;
    }
    for (int i = 1; i <= N; ++i) {
        printf("%c", word[i]);
    }
    printf("\n");
}