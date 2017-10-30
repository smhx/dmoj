#include <cstdio>
#include <algorithm>
#include <vector>
#include <limits>
using namespace std;
typedef long long ll;

const int MAXN = 100005;

int N, M, f[MAXN], b[MAXN], grid[MAXN][6], bit[MAXN];
ll A, B, s[MAXN];
void update(int x, int v) {
	for (;x <= N; x += x&-x) bit[x] += v;
}

int sum(int x) {
	int res = 0;
	for (;x;x-=x&-x) res += bit[x];
	return res;
}

int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d%d%lld%lld", &N, &M, &A, &B);
	ll bsum = 0;
	for (int i = 1; i <= M; ++i) {
		int row; char seat;

		scanf("%d %c", &row, &seat);
		grid[row][seat-'A']=1;

		int insiderow = 0;

		if (seat > 'D') for (int j = (seat-'A')-1; j > 3; --j) insiderow += 1-grid[row][j];
		else for (int j = (seat-'A')+1; j < 2; ++j) insiderow += 1-grid[row][j];

		if (seat=='C' || seat=='D') update(row, 1);

		f[i] = 2 * row - sum(row) + insiderow;

		b[i] = 2 * (N-row+1) - (sum(N)-sum(row-1)) + insiderow;

		bsum += ll(b[i]);

		s[i] = f[i]-b[i];
	}

	sort(s+1, s+1+M);
	for (int i = 1; i <= M; ++i) s[i] += s[i-1];

	ll ans = numeric_limits<ll>::max();

	for (ll F = 0; F <= ll(M); ++F) {
		ll fromB =   ( (F*(F-1) )>>1) + ( ( (ll(M)-F)*(ll(M)-F-1LL) )>>1) ;
		ll fromA = bsum + s[F];
		ans = min(ans, fromA*A+fromB*B);
	}
	printf("%lld\n", ans);
}