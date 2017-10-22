#include <cstdio>
#include <vector>
#include <functional>
#include <queue>

using namespace std;
typedef long long ll;
typedef pair<int, int> ii;

int N; 

ll R, dp[2005];
ll E, C1, V1, CA, CB, CM, VA, VB, VM;

priority_queue<int, vector<int>, greater<int> > vforc[2005];

int main() {
	// freopen("data.txt", "r", stdin);
	scanf("%d%lld", &N, &R);
	for (int i = 0; i < N; ++i) {
		scanf("%lld%lld%lld%lld%lld%lld%lld%lld%lld", &E, &C1, &V1, &CA, &CB, &CM, &VA, &VB, &VM);
		int c = C1, v = V1;
		for (int i = 0; i < E; ++i) {
			if (!c) dp[0] += ll(v);
			else if (c <= R) {
				vforc[c].push(v);
				if ( ll(vforc[c].size()) * ll(c) > R) vforc[c].pop();
			}
			c = int( (ll(c)*CA+CB)%CM );
			v = int( (ll(v)*VA+VB)%VM );  
		}
	}

	for (int c = 1; c <= R; ++c) dp[c] = dp[0];

	for (int c = 1; c <= R; ++c) {
		while (!vforc[c].empty()) {
			int v = vforc[c].top(); vforc[c].pop();
			for (int r = R; r >= c; --r) 
				dp[r] = max(dp[r], v+dp[r-c]);
		}
	}

	printf("%lld\n", dp[R]);
}