#include <cstdio>
const int MAXN = 200005, INF = 1000000000;
int N, nppl=0, nq=0, A[MAXN], B[MAXN], q[MAXN];
int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d", &N);
	while (N--){
		char cmd; scanf(" %c", &cmd);
		if (cmd=='D') {
			++nppl;
			scanf("%d%d", A+nppl, B+nppl);
		} else {
			++nq;
			scanf("%d", q+nq);
		}
	}
	for (int i = 1; i <= nq; ++i) {
		int bdiff = INF, adiff = INF;
		int k;
		for (int j = 1; j <= nppl; ++j) {
			if (q[i]!=j && B[j] >= B[q[i]] && A[j] >= A[q[i]]) {
				if (A[j] - A[q[i]] < adiff) {
					bdiff = B[j]-B[q[i]];
					adiff = A[j] - A[q[i]];
					k = j;
				} else if (A[j] - A[q[i]] == adiff && B[j]-B[q[i]] < bdiff) {
					bdiff = B[j] - B[q[i]];
					k = j;
				}	
			}	
		}
		printf("%d\n", k);
	}
}