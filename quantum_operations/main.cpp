#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

// (max, min)
void getMinMax(vector<int>& small, vector<int>& big) {
	while (small.size() > 1 && big.size() > 1) {
		int min1 = small.back();
		small.pop_back();
		int min2 = small.back();
		small.pop_back();

		int max1 = big.back();
		big.pop_back();
		int max2 = big.back();
		big.pop_back();

		int a = min(min1*min2, min(min1*max2, min(max1*min2, max1*max2)));
		int b = max(min1*min2, max(min1*max2, max(max1*min2, max1*max2)));

		small.push_back(a);
		big.push_back(b);
	}
	printf("%d\n%d\n", big[0], small[0]);
}

int main () {
	const int MAX = 1<<25;
	const int MIN = -1* (1<<25);
	int N;
	scanf("%d", &N);

	vector<int> maxElement(N, MIN);
	vector<int> minElement(N, MAX);

	vector<int> maxRowSum(N, MIN);
	vector<int> minRowSum(N, MAX);

	vector<int> maxColSum(N, MIN);
	vector<int> minColSum(N, MAX);

	for (int i = 0; i < N; i++) {
		int r, c;
		scanf("%d %d", &r, &c);
		vector<int> colSums(c);
		for (int j = 0; j < r; j++) {
			int rowSum = 0;
			for (int k = 0; k < c; k++) {
				int n;
				scanf("%d", &n);
				rowSum += n;
				colSums[k] += n;
				if (n > maxElement[i])
					maxElement[i] = n;
				if (n < minElement[i])
					minElement[i] = n;
				
			}
			if (rowSum > maxRowSum[i])
				maxRowSum[i] = rowSum;
			if (rowSum < minRowSum[i])
				minRowSum[i] = rowSum;
		}
		for (int j = 0; j < c; j++) {
			if (colSums[j] > maxColSum[i])
				maxColSum[i] = colSums[j];
			if (colSums[j] < minColSum[i])
				minColSum[i] = colSums[j];
		}
		
	}
	for (int i = 0; i < N; i++) {
		printf("maxElement[%d] = %d, minElement[%d] = %d\n", i, maxElement[i], i, minElement[i]);
		printf("maxColSum[%d] = %d, minColSum[%d] = %d\n", i, maxColSum[i], i, minColSum[i]);
		printf("maxRowSum[%d] = %d, minRowSum[%d] = %d\n", i, maxRowSum[i], i, minRowSum[i]);
	}
	getMinMax(minElement, maxElement);
	getMinMax(minRowSum, maxRowSum);
	getMinMax(minColSum, maxColSum);
	return 0;
}