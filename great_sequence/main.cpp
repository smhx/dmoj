/*input
5 6 3
1 3 4 5 6
3 6 2 5
1 4 1 4
5 6 1 3
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 1e5+5;


int N, K, Q, seq[MAXN];

ll presum[MAXN];

vector<int> idx[2018];

bool contains(int v, int x, int y) {
	v += 1000;

	// find one where x <= *it <= y

	auto it = lower_bound(idx[v].begin(), idx[v].end(), x);
	if (it == idx[v].end()) return false;
	if (*it > y) return false;
	return true;
}

int main() {
	scanf("%d%d%d", &N, &K, &Q);
	for (int i = 1; i <= N; ++i) {
		scanf("%d", seq+i);
		presum[i] = presum[i-1]+1LL*seq[i];
		if (-1000 <= seq[i] && seq[i] <= 1000) idx[seq[i]+1000].push_back(i);
	}
	while (Q--) {
		int a, b, x, y; scanf("%d%d%d%d", &a, &b, &x, &y);
		if (presum[y]-presum[x-1] <= K) printf("No\n");
		else {
			if (contains(a, x, y) && contains(b, x, y)) printf("Yes\n");
			else printf("No\n");
		}
	}
}