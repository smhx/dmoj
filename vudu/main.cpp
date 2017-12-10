#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int MAXN = 1000006;
int N, np;
ll P, ans=0, x[MAXN], mp[MAXN], bit[MAXN];

void update(int x, ll v){
	for(; x <= np; x += x&-x) bit[x]+=v;
}

ll sum(int x) {
	ll res = 0;
	for (; x; x-=x&-x) res+=bit[x];
	return res;
}

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) {
		scanf("%lld", x+i);
		x[i] += x[i-1];
	}

	scanf("%lld", &P);
	for (int i = 1; i <= N; ++i) {
		x[i] -= P*i;
		mp[i] = x[i];
	}
	sort(mp, mp+N+1);
	np = unique(mp, mp+N+1)-mp;

	for (int i = 0; i <= N; ++i) 
		x[i] = (lower_bound(mp, mp+np, x[i])-mp)+1;
	
	for (int i = N-1; i>=0; --i) {
		update(x[i+1], 1LL);
		ans += (N-i) - sum(x[i]-1);
	}

	printf("%lld\n", ans);
}