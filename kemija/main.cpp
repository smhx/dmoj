#include <cstdio>
#include <vector>
using namespace std;

	
int main () {
	int N=0, totalWeight=0;
	scanf("%d", &N);

	vector<int> D(N);
	vector<int> A(N);
	vector<int> B(N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &B[i]);
		totalWeight += B[i];
	}

	for (int i = 0; i < N; i++) {
		D[i] = B[(i+1) % N]-B[i];
	}
	int sum = 0;
	if (N%3!=0) {
		int weight = 0;
		for (int i = 0; i < N; i++) {
			A[(3*i) % N] = sum;
			sum += D[(3*i) % N];
		}
		for (int i = 0; i < N; i++) {
			weight += A[i];
		}
		int x = (totalWeight-3*weight)/(3*N);
		for (int i = 0; i < N; i++) {
			A[i] += x;
		}
	} else {
		int sum[3] = {0, 0, 0};
		
		int min[3] = {1000000001, 1000000001, 1000000001};
		for (int i = 0; i < N; i++) {
			A[i] = sum[i%3];
			sum[i%3] += D[i];
			if (A[i] < min[i%3])
				min[i%3] = A[i];
		}
		for (int i = 0; i < 3; i++) {
			if (i==2) {
				int weight = 0;
				for (int i = 0; i < N; i++) {
					weight += A[i];
				}		
				int x = (totalWeight-3*weight)/N;
				for (int j = i; j < N; j+=3) {
					A[j] += x;
				}
				continue;
			}
			
			for (int j = i; j < N; j+=3) {
				A[j] += 1-min[i];
			}
		}
	}
	for (int i = 1; i <= N; i++) {
		printf("%d\n", A[i%N]);
	}
	
	return 0;
}