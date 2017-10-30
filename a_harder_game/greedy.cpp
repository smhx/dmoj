#include <cstdio>
#include <algorithm>
#define MAXN 1000006
int N, A[MAXN];
using namespace std;
int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d", &N);

	for (int i = 1; i <= N; ++i) {
		scanf("%d", A+i);
	}

	int lo = 1, hi = N;

	int me = 0;
	for (int move = 1; move <= N; ++move) {
		if (move==N && move&1) me += A[lo];
		else {
			if (max(A[lo+1], A[hi]-A[lo]) < max(A[hi-1],A[lo]) - A[hi]) {
				// take lo
				if (move&1) me += A[lo];
				lo++;
			} else {
				if (move&1) me += A[hi];
				hi--;
			}
			
		}
	}
	printf("%d\n", me);
}