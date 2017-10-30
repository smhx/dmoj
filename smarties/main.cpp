#include <cstdio>
#include <unordered_map>
#include <queue>
#define MAX 1000006
using namespace std;
typedef long long ll;
int N, K, F[MAX], last[MAX];

ll cnt = 0;

priority_queue<int, vector<int>, greater<int> > pq;

int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d%d", &N, &K);
	for (int i = 1; i <= N; ++i) scanf("%d", F+i);

	ll cnt = 0;

	int l = 1, r = 1, sz=0;

	while (l <= N) {
		int rs = r;
		for (; r <= N; ++r) {
			if (!last[F[r]]) ++sz;
			last[F[r]] = r;
			if (sz >= K) break;
		}

		for (int i = rs; i <= r; ++i) {
			pq.push(last[F[i]]);
		}

		if (sz<K) break;

		while (!pq.empty()) {
			int u = pq.top();
			if (u==last[F[u]]) break;
			else pq.pop();
		}

		int lowlast = pq.top();


		cnt += ll(lowlast-l+1) * ll(N-r+1);

		--sz;

		last[F[lowlast]] = 0;
		l = lowlast + 1;
		++r;
	}
	printf("%lld\n", cnt);
}