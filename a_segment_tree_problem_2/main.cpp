#include <queue>
#include <cstdio>
using namespace std;
int N, M, C, i, a, maxl = 1, minl = 1;
bool good = 0;
int main() {
	scanf("%d%d%d", &N, &M, &C);
	queue<int> minq, maxq;
	for (i = 1; i <= N; ++i) {
		scanf("%d", &a);
		while (!minq.empty() && minl <= i-M) {
			minq.pop();
			minl++;
		}
		while (!maxq.empty() && maxl <= i-M) {
			maxq.pop();
			maxl++;
		}
		while (!minq.empty() && minq.front() >= a) {
			minq.pop();
			minl++;
		}
		while (!maxq.empty() && maxq.front() <= a) {
			maxl++;
			maxq.pop();
		}

		minq.push(a);
		maxq.push(a);

		if (i >= M && maxq.front() - minq.front() <= C) {
			printf("%d\n", i-M+1);
			good = true;
		}
	}
	if (!good) printf("NONE\n");
}