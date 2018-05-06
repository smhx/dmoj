#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
int N;
pll pnts[100005];

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) scanf("%lld%lld", &pnts[i].first, &pnts[i].second);
	sort(pnts, pnts+N);
	for (int i = 1; i < N - 1; ++i) {
		if ((pnts[i+1].second-pnts[i].second) * (pnts[i].first-pnts[i-1].first) != (pnts[i].second-pnts[i-1].second) * (pnts[i+1].first-pnts[i].first)){
			return !printf("no\n");
		}		
	}
	for (int i = 0; i < N; ++i) if (pnts[i].first != pnts[i].second && pnts[i].first * pnts[i].second == 0) return !printf("no\n");

	for (int i = 0; i < N-1; ++i) {
		if (pnts[i].second * pnts[i+1].first != pnts[i+1].second * pnts[i].first) return !printf("no\n");
	}
	printf("yes\n");
}

