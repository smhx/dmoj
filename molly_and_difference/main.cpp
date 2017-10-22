#include <cstdio>
#include <algorithm>

using namespace std;

int A[1000000];

int main() {
	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &A[i]);
	}

	sort(A, A+N);

	int min = 1 << 30;

	for (int i = 0; i < N-1; i++) {
		if (A[i+1]-A[i] < min) min = A[i+1]-A[i];
	}

	printf("%d\n", min);
	return 0;
}