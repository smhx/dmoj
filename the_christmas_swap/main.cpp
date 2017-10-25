#include <cstdio>
#include <vector>
#include <algorithm>
#define MAXN 100005
int n, k;
bool A[MAXN];

using namespace std;


void solve() {
	// max ones
	printf("SOLVING\n");
	for (int i = 0; i < n; ++i) {
		printf("%d", A[i]);
	}
	printf("\n");
	vector<int> a;
	for (int i = 0; i < n; ++i)
		if (A[i]) a.push_back(i);

	printf("a\n");
	for (auto x : a) printf("%d ", x);
	printf("\n");
	int ans = 0;
	for (int i = 0; i < (int)a.size(); ++i) {
		int j, m = 0;
		printf("i = %d\n", i);
		for (j=0; ; ++j) {

			if (i+j >= a.size()) {
				--j;
				break;
			}
			m += a[i+j]-j-a[i];
			printf("  j = %d, m = %d\n", j, m);
			if (m>k || i+j >= a.size()){
				--j;
				printf("breaking and setting j = %d\n", j);
				break;
			}
		}
		printf("FINISH j = %d\n", j);
		ans = max(ans, j+1);
	}

	printf("%d\n", ans);
}

int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; ++i) {
		char c=getchar(); 
		A[i] = c=='1';
	}
	solve();
	for (int i = 0; i < n; ++i) A[i]=!A[i];
	solve();
}