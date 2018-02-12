/*input
16 1
25
7
10
32
25
29
29
29
27
25
27
11
18
27
9
13
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN = 1e6+5, MAXV = 1e5+5, LOG = 22;

int gcd(int a, int b) {
	return b==0 ? a : gcd(b, a%b);
}

int N, K, st[MAXN][LOG], f[MAXV], prime[MAXV], pfactor[MAXV];

ll cnt = 0;

void build() {
	for (int k = 1; k < LOG; ++k) {
		for (int i = 1; i + (1<<k) - 1 <= N; ++i) {
			st[i][k] = gcd(st[i][k-1], st[i+(1<<(k-1))][k-1]);
			printf("gcd[%d][%d] = %d\n", i, i+(1<<k)-1, st[i][k]);
		}
	}
}

void carol() {
	for (int i = 2; i < MAXV; ++i) prime[i] = 1;
	for (int x = 2; x*x < MAXV; ++x) {
		if (prime[x]){
			for (int y = x*x; y < MAXV; y += x) {
				prime[y] = false;
				pfactor[y] = x;
			}
		}
	}
	f[1] = 0;
	for (int x = 2; x < MAXV; ++x) {
		if (prime[x]) f[x] = 1;
		else f[x] = 1 + f[x/pfactor[x]];
	}
}

int lowerbound(int x, int v) {
	int cur = st[x][0];

	if (f[cur] <= v) return x;

	for (int k = LOG-1; k >= 0; --k) {
		if (x + (1<<k) <= N) {
			int d = gcd(cur, st[x+1][k]);
			if (f[d] > v) {
				x += (1<<k);
				cur = d;
			}
		}
	}
	return x+1;
}

int main(){
	scanf("%d%d", &N, &K);
	for (int i = 1; i <= N; ++i) scanf("%d", &st[i][0]);
	build();
	carol();
	for (int l = 1; l <= N; ++l) {
		int r2 = lowerbound(l, K-1);
		int r1 = lowerbound(l, K);
		cnt += 1LL*(r2-r1);
	}
	printf("%lld\n", cnt);
}