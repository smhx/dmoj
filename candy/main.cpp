#include <cstdio>
#include <algorithm>

#define MAXN 205
#define MAXT 10000001

typedef std::pair<int, int> ii;

int N, T, cnt[MAXT], type[MAXT], lft[MAXT], rt[MAXT];
bool dp[MAXT];

ii candy[MAXN];

int main() {
	// freopen("data.txt", "r", stdin);
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) {
		scanf("%d%d", &candy[i].second, &candy[i].first);
		T += candy[i].first * candy[i].second;
	}
	sort(candy+1, candy+N+1);
	dp[0] = true;
	for (int i = 0; i <= T>>1; ++i) {
		lft[i]=i==1 ? 1 : i-1;
		rt[i]=i+1;
	}

	int lo = 1; // The lowest one where dp[lo] is false

	for (int i = 1; i <= N; ++i) {
		for (int s = lo; s <= T>>1; s=rt[s]) {
			int c = candy[i].first, k = candy[i].second;
			if ( dp[s-c] && (type[s-c]!=i || cnt[s-c] < k) ) {
				dp[s] = true;
				type[s] = i;
				if (type[s-c]!=i) cnt[s]=1;
				else cnt[s]= cnt[s-c]+1;

				rt[lft[s]]=rt[s];
				lft[rt[s]]=lft[s];

				if (s==lo) lo = rt[s];
			}
		}
	}

	
	for (int s = T >> 1; s>=0; --s) {
		if (dp[s]) {
			printf("%d\n", T-2*s);
			return 0;
		}
	}
}