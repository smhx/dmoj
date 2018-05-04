#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
using namespace std;
typedef long long ll;
const ll LAST_SLOT = 1e9;
int n, k;
ll sameside = 0, a[100005], b[100005];

void input() {
	int nn = 0;
	scanf("%d %d", &k, &n);
	for (int i = 1; i <= n; ++i) {
		char p, q; ll s, t;
		scanf(" %c %lld %c %lld", &p, &s, &q, &t);
		if (p == q) {
			sameside += abs(s-t);
		} else {
			++nn;
			a[nn] = min(s,t);
			b[nn] = max(s,t);
		}
	}
	n = nn;
}

ll f1(ll x) {
	ll ans = 0;
	for (int i = 1; i <= n; ++i) {
		ans += abs(a[i]-x)+abs(b[i]-x)+1;
	}
	return ans + sameside;
}

ll solve1() {
	ll lo = 0, hi = LAST_SLOT;
	while (lo < hi) {
		ll m1 = lo + (hi-lo)/3;
		ll m2 = hi - (hi-lo)/3;
		assert(lo <= m1 && m1 < m2 && m2 <= hi);
		ll fm1 = f1(m1), fm2 = f1(m2);
		if (fm1 <= fm2) {
			hi = m2-1;
		} else {
			lo = m1+1;
		}
	}
	assert(lo == hi);
	ll ans = f1(lo);
	return ans;
}

// 2
ll pnts[200005], npnts = 0;

ll g2(int x, int y) {
	ll ans = 0;
	for (int i = 1; i <= n; ++i) {
		ans += min(abs(a[i]-pnts[x])+abs(b[i]-pnts[x]), abs(a[i]-pnts[y])+abs(b[i]-pnts[y])) + 1;
	}
	return ans+sameside;
}

void init2() {
	for (int i = 1; i <= n; ++i) {
		pnts[npnts++] = a[i];
		pnts[npnts++] = b[i];
	}
	sort(pnts, pnts+npnts);
	npnts = unique(pnts, pnts+npnts)-pnts;
}

ll end2(int i) {
	ll maxs = 0;
	for (int k = 1; k <= n; ++k) {
		if (pnts[i] < a[k]) maxs = max(maxs, a[k]+b[k]);
	}
	ll bound = maxs-pnts[i];
	int j = 1;
	while (j < npnts && pnts[j] < bound) ++j;
	j = max(j, i+1);
	return j;
}

ll f2(int i) {
	// ll lo = i+1, hi = end2(i);
	ll lo = i+1, hi = max(1LL*i+1,npnts-1);
	// assert(g2(x,hi)==g2(x,hi+1));
	assert(lo <= hi);
	while (lo < hi) {
		int m1 = lo + (hi-lo)/3;
		int m2 = hi - (hi-lo)/3;
		assert(lo <= m1 && m1 < m2 && m2 <= hi);
		ll fm1 = g2(i, m1), fm2 = g2(i, m2);
		// printf("lo = %lld, hi = %lld, m1 = %lld, m2 = %lld, fm1 = %lld, fm2 = %lld\n", lo, hi, m1, m2, fm1, fm2);

		if (fm1 <= fm2) {
			hi = m2-1;
		} else {
			lo = m1+1;
		}
	}
	assert(lo == hi);
	ll ans = g2(i, lo);
	// printf("f2(%lld) = %lld, lo = %lld\n", x, ans, lo);
	return ans;
}

ll solve2() {
	if (n == 0) {
		return sameside;
	}
	int lo = 0, hi = npnts-1;
	// printf("lo = %d, hi = %d\n", lo, hi);
	while (lo < hi) {
		// printf("lo = %d, hi = %d\n", lo, hi);
		int m1 = lo + (hi-lo)/3;
		int m2 = hi - (hi-lo)/3;
		assert(lo <= m1 && m1 < m2 && m2 <= hi);
		// printf("solve2 m1 = %lld, m2 = %lld\n", m1, m2);
		ll fm1 = f2(m1), fm2 = f2(m2);
		if (fm1 <= fm2) {
			hi = m2-1;
		} else {
			lo = m1+1;
		}
	}
	assert(lo == hi);
	// printf("x = %lld\n", lo);
	ll ans = f2(lo);
	// printf("%lld\n", ans);
	return ans;
}

ll solve2_correct() {
	if (n==0) return sameside;
	ll ans = 1000000000000000LL;
	for (int i = 1; i <= n; ++i) {
		ans = min(ans, f2(a[i]));
		ans = min(ans, f2(b[i]));
	}
	return ans;
}

void test2() {
	srand(time(0));
	int ntest = 1;
	while (ntest--) {
		n = 100;
		for (int i = 1; i <= n; ++i) {
			int s =	rand(); 
			int t = rand();
			a[i] = min(s,t);
			b[i] = max(s,t);
			// printf("[%d, %d]\n", a[i], b[i]);
		}
		k = 2;
		ll correct = solve2_correct();
		ll totest = solve2();
		printf("Got %lld, expected %lld\n", totest, correct);
		if (correct == totest) {
			printf("AC!\n");
		} else {
			printf("WA :(\n");
			printf("n = %d, k = 2\n", n);
			for (int i = 1; i <= n; ++i) {
				printf("[%d, %d]\n", (int)a[i], (int)b[i]);
			}
			return;
		}
	}
}

int main() {
	freopen("data.txt", "r", stdin);
	input();
	// test2();	
	if (k==1) {
		printf("%lld\n",solve1());
	} else {
		init2();
		printf("%lld\n", solve2());
		// for (ll x = 0; x < 7; ++x) {
			// printf("x = %lld: ", x);
			// for (ll y = x+1; y <= 20; ++y) {
				// printf("g2(%lld, %lld) = %lld\n", x, y, g2(x, y)+sameside);
				// printf("(y = %lld, %lld) ",y, g2(x,y));
				// printf("%lld ", g2(x,y));
			// }
			// printf("\n");
		// }
		// printf("f(2) = %lld\n", f2(2));
	}
}