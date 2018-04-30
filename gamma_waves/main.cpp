#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
ll x, a[100005], b[100005];
map<ll, queue<ll>> bv;
int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d %lld", &n, &x);
	for (int i = 1; i <= n; ++i) {
		scanf("%lld %lld", a+i, b+i);
	}
	int ai = n, bi = n;
	ll modsum = 0;
	while (ai) {
		while (bi && b[bi] >= a[ai]) {
			bv[b[bi]%x].push(b[bi]);
			--bi;
		}
		auto it = bv.upper_bound(a[ai]%x);
		if (it != bv.begin()){
			--it;
		} else {
			it = --bv.end();
		}
		if (it->second.front() == a[ai]) {
			if (it != bv.begin()) --it;
			else it = --bv.end();
		}
		if (it->second.front() == a[ai]) {
			modsum -= 1LL;
		} else {
			modsum += (it->second.front()-a[ai]-1LL)%x;
		}
		it->second.pop();
		if (it->second.empty()) bv.erase(it);	
		--ai;
	}
	ll diffsum = 0;
	for (int i = 1; i <= n; ++i) diffsum += b[i]-a[i]-1LL;
	printf("%lld\n", (diffsum-modsum)/x);
}
