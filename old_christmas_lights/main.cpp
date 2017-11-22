#include <cstdio>
#include <deque>
using namespace std;
typedef pair<int, int> ii;
const int MAXN = 100005, LOG = 19;
int N, K, Q, A[MAXN], R[MAXN], L[MAXN], f[MAXN][LOG], g[MAXN];

int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d%d", &N, &K);
	for (int i = 1; i <= N; ++i) scanf("%d", A+i);

	deque<ii> minq, maxq; 
	for (int l = 1, r = 1; r <= N; ++r) {
		while (!minq.empty() && minq.back().first > A[r]) minq.pop_back();
		while (!maxq.empty() && maxq.back().first < A[r]) maxq.pop_back();
		minq.emplace_back(A[r], r); maxq.emplace_back(A[r], r);
		while (maxq.front().first - minq.front().first > K) {
			if (maxq.front().second==l) maxq.pop_front();
			if (minq.front().second==l) minq.pop_front();
			R[l] = r-l; ++l;
		}
		L[r] = r-l+1; g[r] = l;
	}
	for (int i = 1; i <= N; ++i) f[i][0] = i;
	for (int k = 1; k < LOG; ++k) {
		for (int i = 1; i <= N; ++i) {
			if (i + (1<<k) <= N) {
				if (R[ f[i][k-1] ]  >= R[ f[i+(1<<(k-1))][k-1]] ) f[i][k] = f[i][k-1];
				else f[i][k] = f[i+(1<<(k-1))][k-1];
			}
		}
	}
	scanf("%d", &Q);
	while (Q--) {
		int a, b; scanf("%d%d", &a, &b);
		int i = g[b], k=0; 
		if (i <= a) {printf("%d %d\n", a, b); continue; }
		for (; a + (1<<(k+1)) <= i; ++k);
		int j, j1 = f[a][k], j2 = f[i-(1<<k)][k];
		if (R[j1] > R[j2] ) j = j1;
		else if (R[j1]  == R[j2] ) j = min(j1, j2);
		else j = j2;

		if (b-i+1 > R[j]) printf("%d %d\n", i, b);
		else printf("%d %d\n", j, R[j]+j-1);
	}
}