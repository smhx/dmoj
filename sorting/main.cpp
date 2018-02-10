#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 200005, LOG = 20;
int dest[MAXN], rdest[MAXN], pos[MAXN], tmp[MAXN], tmpS[MAXN];
bool solve(int N, int S[], int M, const int X[], const int Y[], int P[], int Q[]) {
	for (int i = 0; i < N; ++i) tmp[i] = S[i];
	for (int i = 0; i < M; ++i) swap(tmp[X[i]], tmp[Y[i]]);
	for (int i = 0; i < N; ++i) dest[tmp[i]]=i;
	for (int i = 0; i < N; ++i) rdest[dest[i]]=i;
	for (int i = 0; i < N; ++i) pos[S[i]]=i;
	int k = 0;
	for (int i = 0; i < M; ++i) {
		int x = X[i], y = Y[i];
		int xval = S[x], yval = S[y];
		swap(pos[xval], pos[yval]);
		swap(S[x], S[y]);		
		while (dest[k]==k && k < N) ++k;
		if (k>=N) continue;
		int j = rdest[k]; // j is a value
		swap(S[pos[k]], S[pos[j]]);
		P[i] = pos[k], Q[i] = pos[j];
		swap(pos[k], pos[j]);
		rdest[dest[k]]=j; rdest[k]=k;
		dest[j]=dest[k]; dest[k]=k;
	}
	for (int i = 0; i < N; ++i) if (S[i]!=i) return false;
	return true;
}
int findSwapPairs(int N, int S[], int M, int X[], int Y[], int P[], int Q[]) {
	bool alreadySorted = true;
	for (int i = 0; i < N; ++i) if (S[i]!=i) alreadySorted = false;
	if (alreadySorted) return 0;

	int x = 0;
	for (int i = LOG; i >=0; --i) {
		if (x+(1<<i) <= M) {
			for (int j = 0; j < N; ++j) tmpS[j] = S[j];
			for (int j = 0; j < M; ++j) P[j] = Q[j] = 0;
			if (!solve(N, tmpS, x+(1<<i), X, Y, P, Q)) x += 1<<i;
		}
	}
	solve(N, S, ++x, X, Y, P, Q);
	return x;
}

/* testing
int testS[MAXN], testX[MAXN], testY[MAXN], testP[MAXN], testQ[MAXN];
int main() {
	freopen("data.txt", "r", stdin);
	int N, M; 

	scanf("%d%d", &N, &M);
	for (int i = 0; i < N; ++i) scanf("%d", testS+i);
	for (int i = 0; i < M; ++i) scanf("%d%d", testX+i, testY+i);

	int len = findSwapPairs(N, testS, M, testX, testY, testP, testQ);
	printf("len = %d\n", len);
	for (int i = 0; i < len; ++i) {
		printf("swapping (%d, %d)\n", testP[i], testQ[i]);
	}
}
*/
