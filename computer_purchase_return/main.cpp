/*input
2
5
10 6 1
5 7 1
6 10 2
1 5 1
11 11 2
16
*/
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;

int T, N, B, c[1005], v[1005], t[1005];
vector<ii> parts[10];
int dp[10][3005];
int main() {
    scanf("%d%d", &T, &N);
    for (int i = 0; i < N; ++i) {
        scanf("%d%d%d", c+i, v+i, t+i);
        parts[t[i]].emplace_back(c[i], v[i]);
    }
    scanf("%d", &B);
    memset(dp, -1, sizeof dp);
    for (int b = 0; b <= B; ++b) dp[0][b] = 0;
    for (int t=1; t <= T; ++t) 
        for (int b = 0; b <= B; ++b) 
            for (ii p : parts[t]) 
                if (b >= p.first)
                    dp[t][b] = max(dp[t][b], p.second + dp[t-1][b-p.first]);
    printf("%d\n", dp[T][B]);
}