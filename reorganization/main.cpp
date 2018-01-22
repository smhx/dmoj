#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
int n, rnk[maxn];

int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", rnk+i);
		if (rnk[i] < rnk[1]) return !printf("NO\n");
	}

	map<int,int> leaves;
	leaves[rnk[1]]=0;
	for (int id = 2; id <= n; ++id) {
		auto it = leaves.lower_bound(rnk[id]);
		if (it==leaves.begin()) return !printf("NO\n");
		--it;
		if (it->second==1) leaves.erase(it);
		else ++(it->second);
		leaves[rnk[id]]=0;
	}
	printf("YES\n");
}