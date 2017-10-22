#include <cstdio>
#include <algorithm>
#define MAXN 150005
#define INF 1000000000

int N, sum[3][MAXN], ans = INF;

void perm(int p, int& a, int& b, int& c) {
    a = p>>1;
    b = (a+1+ (p&1) )%3;
    c = (a+2- (p&1) )%3;
}

int main() {
    // freopen("data.txt", "r", stdin);
    scanf("%d", &N);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < N; ++j) {
            scanf("%d", sum[i]+j);
            if (j) sum[i][j] += sum[i][j-1];
        }
    }

    for (int p = 0; p < 6; ++p) {
        int a, b, c;
        perm(p,a, b, c);    
        int mem = INF; 
        for (int i = N-2; i > 0; --i) {
            int s =  sum[b][i]-sum[c][i];
            if (mem != INF && s > mem) 
                s = mem;
            ans = std::min(ans, sum[a][i-1]+sum[c][N-1]-sum[b][i-1] + s);
            mem = s;
        }

    }

    printf("%d\n", ans);

}