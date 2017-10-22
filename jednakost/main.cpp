#include <cstdio>
#include <cstring>
#include <vector>

#define INF 1000000000

using namespace std;

typedef pair<int, int> ii;

char A[1005], c;
int S, N;

ii dp[1005][5005]; // number of plus, number to take

inline int val(int i, int j) {
	int x = 0;
	for (int k = 0; k < j; ++k) x = x*10+(A[k+i]-'0');
	return x;
}

int main() {
	freopen("data.txt", "r", stdin);
	while ( (c=getchar()) != '=') A[N++]=c;
	while ( (c=getchar()) >= '0') S=10*S+(c-'0');
	for (int i = 0; i <= N; ++i)
		for (int s = 0; s <= S; ++s)
			dp[i][s] = ii(INF, 0);
	dp[N][0] = ii(0, 0);
	for (int i = N-1; i >= 0; --i) {
		if (A[i]=='0') {
			for (int s = 0; s <= S; ++s) 
				dp[i][s] = ii(dp[i+1][s].first, dp[i+1][s].second+1);
		} else {
			for (int j = 1; j <= 4 && i+j <= N; ++j) {
				int left = val(i, j);
				for (int s = 0; s+left <= S; ++s) 
					if (1+dp[i+j][s].first < dp[i][s+left].first) 
						dp[i][s+left] = ii(dp[i+j][s].first+1, j);
			}
		}
	}
	for (int x = 0, presum = 0; x < N; ) {
		int take = dp[x][S-presum].second;
		for (int i = 0; i < take; ++i)
			printf("%c", A[x+i]);
		presum += val(x, take);
		x += take;
		if (x==N) printf("=%d\n", S);
		else printf("+");
	}
}