#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 105;

int N, dp[MAXN][MAXN], A[MAXN], oddsum[MAXN]; 


int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		scanf("%d", A+i);
		A[i] = A[i]&1;
		if (i) oddsum[i] = A[i] + oddsum[i-1];
		else oddsum[i] = A[i];
	}

	for (int sz = N-1; sz; --sz) {
		for (int l = 0; l < N; ++l) {
			int totOdd;
			if (l + sz -1 < N) {
				if (l) totOdd = oddsum[l+sz-1]-oddsum[l-1];
				else totOdd = oddsum[l+sz-1];
				totOdd = oddsum[N-1]-totOdd;
			} else {
				int L = (l+sz-1)%N;
				totOdd = oddsum[L]+oddsum[N-1]-oddsum[l-1];
				totOdd = oddsum[N-1]-totOdd;
			}

			int takeL, takeR;
			if (l) {
				takeL = totOdd - dp[l-1][sz+1];
			} else {
				takeL = totOdd -dp[N-1][sz+1];
			}
			takeR = totOdd - dp[l][sz+1];			
			dp[l][sz] = max(takeL, takeR);
		}
	}
	int cnt=0;
	for (int i = 0; i < N; ++i) 
		if (dp[i][1] < oddsum[N-1]/2 + oddsum[N-1]%2) ++cnt;
	
	printf("%d\n", cnt);
}