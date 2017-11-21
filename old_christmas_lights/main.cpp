#include <cstdio>
#include <algorithm>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 100005, LOG=20;
int N, K, Q, A[MAXN], f[MAXN], g[MAXN], minst[MAXN][LOG], maxst[MAXN][LOG], lenst[MAXN][LOG];

int main() {
	scanf("%d%d", &N, &K);

	memset(minst, 0x3f3f3f3f, sizeof minst);

	for (int i = 1; i <= N; ++i) {
		scanf("%d", A+i);
		minst[i][0] = maxst[i][0] = A[i];
	}

	for (int k = 1; k < LOG; ++k) {
		for (int i = 1; i <= N; ++i) {
			if (i + (1<<k) - 1 <= N) {
				minst[i][k] = min(minst[i][k-1], minst[i + (1 << (k-1)) ][k-1]);
				maxst[i][k] = max(maxst[i][k-1], maxst[i+(1<<(k-1))][k-1]);
			}
		}
	}

	for (int i = 1; i <= N; ++i) {
		int m=A[i], M =A[i];
		f[i] = i;
		for (int k = LOG-1; k >= 0; --k) {
			if (f[i] + (1<<k) <= N) {
				int newm = min(m, minst[f[i]+1][k]);
				int newM = max(M, maxst[f[i]+1][k]);
				if (newM-newm <= K) {
					f[i] += 1<<k;
					m = newm, M = newM;
				}
			}
		}
	}

	for (int i = 1; i <= N; ++i) {
		int m = A[i], M = A[i];
		g[i] = i;
		for (int k = LOG-1; k >= 0; --k) {
			if (g[i] - (1<<k) > 0) {
				int newm = min(m, minst[g[i]-(1<<k )][k]);
				int newM = max(M, maxst[g[i]-(1<<k)][k]);
				if (newM-newm <= K) {
					g[i] -= 1<<k;
					m = newm, M = newM;
				}
			}
		}
	}

	for (int i = 1; i <= N; ++i) lenst[i][0] = i;

	for (int k = 1; k < LOG; ++k) {
		for (int i = 1; i <= N; ++i) {
			if (i + (1<<k) - 1 <= N) {
				int a = lenst[i][k-1], b = lenst[i+(1<<(k-1))][k-1];
				if (f[a] - a > f[b] - b) lenst[i][k] = a;
				else if (f[a]-a < f[b]-b) lenst[i][k] = b;
				else lenst[i][k] = min(a, b);
			}
		}
	}
	scanf("%d", &Q);
	while (Q--) {
		int a,b; scanf("%d%d", &a, &b);
		int i = g[b], k=0; 
		if (i <= a) {printf("%d %d\n", a, b); continue; }
		for (; a + (1<<(k+1)) <= i; ++k);
		int j, j1 = lenst[a][k], j2 = lenst[i-(1<<k)][k];
		if (f[j1] - j1 > f[j2] - j2) j = j1;
		else if (f[j1] - j1 == f[j2] - j2) j = min(j1, j2);
		else j = j2;

		if (b-i+1 > f[j]-j+1) printf("%d %d\n", i, b);
		else printf("%d %d\n", j, f[j]);
	}
}