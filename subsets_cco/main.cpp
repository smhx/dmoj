/*input
5
*/
#include <cstdio>
#include <cmath>
#include <unordered_map>
#include <vector>
#include <cstring>
using namespace std;

typedef long long ll;
const int MAXN = 100005;
const ll MOD = ll(1e9+1);

int pow3[14];
int n;
ll dp[MAXN], mem[MAXN];
const double l32 = log(2)/log(3);

unordered_map<int,int> mp[2];

bool valid(int mask1) {
	for (int k = 0; 1<<(k+1) <= mask1; ++k) {
		if ((mask1 & (1<<k)) && (mask1 & (1<<(k+1)))) return false;
	}
	return true;
}

bool valid(int mask1, int mask2) {
	for (int k=1; k <= mask1; k<<=1) {
		if ((mask1&k) && (mask2&k) ) return false;
	}
	return true;
}

ll f(int N) {
	printf("f(%d)\n", N);
	if (mem[N]!=-1) return mem[N];
	vector<int> a;

	int k = 0;
	while (1<<(k+1) <= N) ++k;
	int m = 0;
	for (; k>=0; --k) {
		while ((1<<k)*pow3[m+1] <= N) ++m;
		a.push_back(m+1);
	}
	reverse(a.begin(), a.end());

	mp[0].clear(); mp[1].clear();

	mp[(a.size()-1) & 1][0]=1;
	mp[(a.size()-1) & 1][1]=1;

	for (int k=a.size()-2; k>=0; --k) {
		mp[k&1].clear();
		for (int mask1 = 0; mask1 < (1<<a[k]); ++mask1) {
			if (!valid(mask1)) continue;
			ll cnt = 0LL;
			for (int mask2 = 0; mask2 < (1<<a[k+1]); ++mask2) {
				if (!valid(mask2)) continue;
				if (valid(mask1, mask2)) {
					cnt += 1LL*mp[(k+1)&1][mask2];
					cnt %= MOD;
				}
			}
			mp[k&1][mask1]=cnt;
		}
	}

	ll ans=0;
	for (auto p : mp[0]) {
		ans = (ans + 1LL * p.second)%MOD;
	}
	return mem[N]=ans;
}

int main() {
	scanf("%d", &n);
	memset(mem, -1, sizeof mem);

	pow3[0]=1;
	for (int i = 1; i < 14; ++i) pow3[i] = 3*pow3[i-1];

	ll total=1LL;
	for (int x = 1; x <= n; ++x) {
		if (x%2!=0 && x%3!=0) {
			total *= 1LL * f(n/x);
			total %= MOD;
		}	
	}
	printf("%lld\n", total);
}
