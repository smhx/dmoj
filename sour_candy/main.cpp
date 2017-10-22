#include <cstdio>
#include <unordered_map>
#include <cstring>
#define MAXN 100005
using namespace std;
int N, s[MAXN], t[MAXN], map[MAXN], bit[MAXN];
unordered_map<int, int> r;

int sum(int x) {
    int ans = 0;
    for (;x;x-=x&-x) ans+=bit[x];
    return ans;
}
void update(int x) {for (;x<=N;x+=x&-x) ++bit[x];}
int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) scanf("%d", s+i);
    for (int i = 1; i <= N; ++i) scanf("%d", t+i);
    for (int i = 1; i <= N; ++i) r[t[i]] = i;
    for (int i = 1; i <= N; ++i) s[i] = r[s[i]];
    for (int i = 1; i <= N; ++i) map[s[i]] = i;
    int moves = N, left=0;
    for (int i = 0, k; i < N; i=k) {
        for (k=i+1; k < N && map[k] < map[k+1]; ++k);
        if (i + N - k < moves) moves = i + N - k, left = i;
    }
    printf("%d\n", moves);
    for (int i = left; i >= 1; --i) {
        printf("F %d\n", map[i]+left-i-sum(map[i]));
        update(map[i]);
    }
    memset(bit, 0, sizeof(int) * (N+1) );
    for (int i = 1, r = left; i <= N; ++i) {
        if (s[i] <= left) --r;
        else map[s[i]] += r;
    }
    for (int i = N-(moves-left)+1; i <= N; ++i) {
        printf("B %d\n", map[i]- sum(map[i]));
        update(map[i]);
    }

}