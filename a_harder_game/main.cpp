#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <vector>
#define MAXN 1003
int N, A[MAXN], dp[MAXN][MAXN], S[MAXN];
using namespace std;
int main() {
	// freopen("data.txt", "r", stdin);
	// scanf("%d", &N);

	N = 4;

	srand(time(NULL));


	int T = 100;

	
	while (T--) {
		printf("T = %d\n", T);
		for (int i = 1; i <= N; ++i) {
			// scanf("%d", A+i);
			A[i] = rand() % 10 + 1;
			S[i] = A[i]+S[i-1];
		}

		int lo = 1, hi = N;

		int me = 0;
		for (int move = 1; move <= N; ++move) {
			if (move==N && move&1) me += A[lo];
			else {
				// vector<int> l, r;
				// l.push_back(lo); r.push_back(hi);
				// int lasum = A[lo], rasum = A[hi];
				// printf("lo=%d, hi=%d\n", lo, hi);
				// for (int j = lo+1, sign = -1; A[j]>A[j-1] && j <= hi; j++) {
					// printf("  lj=%d\n", j);
					// lasum += sign*A[j];
					// sign *= -1;
				// }
				// for (int j = hi-1, sign = -1; A[j] > A[j+1] && j >= lo; j--) {
					// printf("  hj=%d\n", j);
					// rasum += sign*A[j];
					// sign*=-1;
				// }
				// printf("lo=%d, hi=%d, lasum=%d, rasum=%d\n", lo, hi, lasum, rasum);
				if ( 1) {
					if (move&1) me += A[lo];
					lo++;

				} else {
					if (move&1) me += A[hi];
					hi--;
				}
			}
		}

		for (int l = 1; l <= N; ++l) {
			for (int i = 1; i+l-1 <= N; ++i) {
				int j = i+l-1;
				dp[i][j] = S[j]-S[i-1]-std::min(dp[i+1][j], dp[i][j-1]);
			}
		}

		if (dp[1][N] != me) {
			printf("WRONG!! correct is %d, greedy is %d, Here's A\n", dp[1][N], me);
			for (int i = 1; i <= N; ++i) printf("%d ", A[i]);
			printf("\n");
			return 0;
		}
	}
	

	// printf("%d\n", me);
}

/*

	Each coin is a "door" to the next or previous depending whether it was taken as a left or as a right

	Unless this coin is part of a sub with r <= l+1
	
	Let's sort it. What does this mean? Assign each coin a sorted index, with equals being equal.

	Each coin is better than j >= 0 next coins. So

*/