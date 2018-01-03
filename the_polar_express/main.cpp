#include <cstdio>
#include <vector>
#include <utility>
using namespace std;
typedef long long ll;
typedef pair<ll, int> range;

vector<range> decompose(ll A, ll B) {
	vector<range> v;
	int exp=0;
	ll pow = 1LL, x = A;
	while (true) {
		if (x % (10LL * pow) == 0) ++exp, pow *= 10LL;
		if (x + pow > B) break;
		v.push_back({x, exp});
		x += pow;
	}

	while (x <= B) {
		while (x % pow != 0) --exp, pow /= 10LL;
		while (x + pow > B + 1) --exp, pow /= 10LL;
		v.push_back({x, exp});
		x += pow;
	}
	return v;
}

int digsum(ll x) {
	int sum=0;
	for (;x; x/=10LL) sum += x%10LL;
	return sum;
}

int cnt[200];

int main() {
	ll L, R;
	scanf("%lld %lld", &L, &R);
	vector<range> v = decompose(L, R);
	for (range r : v) {
		// printf("[%lld, %lld)\n", r.first, r.first + tenpow[r.second]);
		int dsum = digsum(r.first);
		++cnt[dsum];
		--cnt[dsum+9*r.second+1];
	}
	int num = 0;
	for (int i = 0; i < 200; ++i) {
		if (i) cnt[i] += cnt[i-1];
		if (cnt[i] > 0) ++num;
	}
	printf("%d\n", num);
}