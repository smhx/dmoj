#include <cstdio>
#include <vector>

using namespace std;

int main() {
	int n;
	scanf("%d", &n);
	vector< vector<int> > slides(n+1, vector<int>() );
	while (true) {
		int a, b;
		scanf("%d %d", &a, &b);
		if (a==0 && b==0) {
			break;
		}
		slides[a].push_back(b);
		slides[b].push_back(a);
	}
	
	vector<int> A(n+1);
	A[1] = 1;
	for (int i = 2; i <= n; i++) {
		for (int j = 0; j < (int)slides[i].size(); j++) {
			if (i > slides[i][j])
				A[i] += A[slides[i][j]];
		}
	}
	printf("%d\n", A[n]);
	return 0;
}