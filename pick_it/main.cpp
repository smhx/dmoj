#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN = 205;

int n, a[MAXN], dp[MAXN][MAXN];

int main() {
	scanf("%d", &n);
	while (n) {
		memset(dp, 0, sizeof dp);

		for (int i = 1; i <= n; ++i) scanf("%d", a+i);
		
		for (int l = 2; l < n; ++l) 
			for (int i = 1; i+l <= n; ++i) 
				for (int k = i+1; k < i+l; ++k) 
					dp[i][i+l] = max(dp[i][i+l], dp[i][k]+dp[k][i+l]+a[i]+a[k]+a[i+l]);
				
		printf("%d\n", dp[1][n]);
		scanf("%d", &n);
	}
}