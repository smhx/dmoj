#include <cstdio>

int A[1000];
int m[1000];

int main () {
	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &A[i]);
	}
	int max = 0;
	for (int i = 0; i < N; i++) {
		bool found = false;
		for (int j = 0; j <= i; j++) {
			if (A[j] < A[i]) {
				if (A[i]+m[j] > m[i]) {
					m[i] = A[i]+m[j];
					found = true;
				}
			}
		}
		if (!found) {
			m[i] = A[i];
		}
		if (m[i] > max) max = m[i];
 	}
 	printf("%d\n", max);
 	return 0;
}