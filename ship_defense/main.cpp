/*input
100 2 2
50 0
0 10
0 10 11
5 1 50
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int D, E, A[10], S[10], T[1005], L[1005];
long double H, X[1005], dam[5005];
int main() {
	memset(X, 0, sizeof X);
	memset(dam, 0, sizeof dam);
	memset(A, 0, sizeof A);
	memset(S, 0, sizeof S);
	memset(T, 0, sizeof T);
	memset(L, 0, sizeof L);


	cin >> H >> D >> E;
	for (int i = 1; i <= D; ++i) cin >> A[i] >> S[i];
	for (int i = 1; i <= E; ++i) {
		cin >> T[i] >> L[i] >> X[i];
		for (int j = 0; j < L[i]; ++j) {
			dam[T[i]+j] += X[i];
		}
	}
	for (int t = 0; t < 5005; ++t) {
		long double mind = 100000000.0;
		for (int d = 1; d <= D; ++d) {
			mind = min(mind, max((long double)0.0, dam[t] - S[d]) * (100-A[d]) * 0.01);
		}
		H -= mind;
	}
	if (H <= 0) {
		printf("DO A BARREL ROLL!\n");
	} else {
		cout << fixed << setprecision(2) << H << endl;
	}
}