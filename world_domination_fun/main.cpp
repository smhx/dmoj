#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int MAXN = 100005, LOG = 32;
int N, M;
ll h[MAXN], bit[MAXN], K;

const ll INF = 10000000000000LL;

ll sum(int x) {
	ll ans=0;
	for (; x; x -= x&-x) ans += bit[x];
	return ans;
}

void update(int x, ll v) {
	for (; x <= N; x += x&-x) bit[x] += v;
}

bool works(ll target) {
	ll used = 0LL;
	for (int i = N-M+1; i; --i) {
		ll val = h[i+M-1] + sum(i+M-1);
		if (val < target) {
			ll need = target-val;
			update(i, need);
			update(i+M, -need);
			used += need;
			if (used > K) return false;
		}
	}
	ll lowest = INF;
	for (int i = 1; i < M; ++i) lowest = min(lowest, h[i]+sum(i));
	used += target-lowest;
	return used <= K;
}

int main() {
	scanf("%d%d%lld", &N, &M, &K);
	for (int i = 1; i <= N; ++i) scanf("%lld", h+i);
	ll minh = 0;
	for (int k = LOG-1; k>=0; --k) {
		memset(bit, 0, sizeof bit);
		if (works(minh|(1LL << k))) minh |= 1LL << k;
	}
	printf("%lld\n", minh);
}