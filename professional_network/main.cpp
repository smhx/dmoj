#include <cstdio>
#include <vector>
#include <set>
#include <functional>

using namespace std;

const int MAX = 1 << 30;

int main () {
	int N;
	scanf("%d", &N);

	vector< vector<int> > A(N);
	vector<int> c(N+1);

	int p=0, k=0, b=0;

	multiset<int> buyable;

	for (int i = 0; i < N; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		if (a==N) {
			k++;
			p += b;
			continue;
		}
		A[a].push_back(b);
	}

	c[0] = 0;

	for (int i = 0; i < N; i++) {
		// printf("i in start is %d\n", i);
		if (A[i].empty()) continue;
		sort(A[i].begin(), A[i].end(), greater<int>() );
		if (c[i] + A[i].size()-1 >= i) {
			buyable.insert(A[i][0]);
		}
		for (int j = 1; j < (int)A[i].size(); j++) {
			// printf("inserting j = %d\n", j);
			buyable.insert(A[i][j]);
		}
		c[i+1] = c[i]+A[i].size();
	}


	for (int i = 0; i < N; i++) {
		// printf("i is %d\n", i);
		if (!A[i].empty()) {
			b += A[i].size()-1;
			// You have to remove
			if (c[i] >= i) {
				buyable.erase(buyable.find(A[i][0]));
			}
			for (int j = 1; j < (int)A[i].size(); j++){
				buyable.erase(buyable.find(A[i][j]));
			}
			continue;
		}

		if (b) {
			b--;
			continue;
		}

		if (k) {
			k--;
			continue;
		}
		
		int min = *buyable.begin();
		// printf("min is %d\n", min);
		buyable.erase(buyable.begin());
		p += min;
	}
	printf("%d\n", p);
	return 0;
}

