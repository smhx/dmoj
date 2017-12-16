#include <cstdio>
using namespace std;
typedef long long ll;
const int MAXN = 22, SIZE = 2000000;
int N, H, hit = 0, adj[MAXN], idx[SIZE];
ll sum[SIZE], cnt = 0;
int main() {
	scanf("%d%d", &N, &H);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			char c; scanf(" %c", &c);
			if (c=='1') adj[i] |= 1<<j;
		}
	}
	for (int v = 0; v < N; ++v) {
		if (adj[0] & (1<<v)) {
			hit |= 1<<v;
			++cnt;
		}
	}
	idx[hit] = 1;
	sum[1] = cnt;
	for (int h = 2; h <= H; ++h) {
		cnt = 0;
		int tmphit = 0;
		for (int u = 0; u < N; ++u) {
			if ( (hit&(1<<u) )==0) {
				for (int v = 0; v < N; ++v) {
					if (adj[u] & (1<<v)) {
						cnt += 2LL;
					}
				}
			} else {
				for (int v = 0; v < N; ++v) {
					if (adj[u] & (1<<v)) {
						++cnt;
						tmphit ^= 1<<v;
					}
				}
			}
		}
		sum[h] = cnt+sum[h-1];
		if (idx[tmphit]) {
			int oldh = idx[tmphit];
			int mod = h-oldh;
			ll presum = sum[h];
			int ncycle = (H - h) / mod;
			ll cyclesum = sum[h] - sum[oldh];
			int leftover = (H-oldh) % mod;
			ll leftoversum = sum[oldh + leftover] - sum[oldh];
			printf("%lld\n", presum + 1LL*ncycle * cyclesum + leftoversum);
			return 0;
		} 
		idx[tmphit] = h;
		hit = tmphit;
	}
	printf("%lld\n", sum[H]);	
}