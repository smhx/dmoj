#include <bits/stdc++.h>
using namespace std;

const int MAX = 3e5+5, INF = 1e7;

int f[2][2] = {{1,1},{1,0}};

int N, M, ch[MAX][2], curstate[MAX], dp[MAX][4];

// int dp(int u, int st) {
// 	if (u <= N) {
// 		if (st == 1) return 0;
// 		return -INF;
// 	} 

// }

int main() {
	scanf("%d%d", &N, &M);
	for (int i = N+1; i <= N+M; ++i) scanf("%d%d", &ch[i][0], &ch[i][1]);
	// Find the current state of each node
	for (int i = 1; i <= N; ++i) curstate[i] = 1;
	for (int i = N+1; i <= N+M; ++i) {
		curstate[i] = 2*f[curstate[ch[i][0]]&2][curstate[ch[i][1]]&2] | f[curstate[ch[i][0]]&1][curstate[ch[i][0]]&1];
	}

	for (int i = 1; i <= N; ++i) dp[i][0] = dp[i][2] = dp[i][3] = -INF;
	for (int i = N+1; i <= N+M; ++i) {
		dp[i][0] = 1 + dp[ch[i][0]][3] + dp[ch[i][1]][3];
		dp[i][3] = 1;
	}
}