#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
typedef pair<int,int> ii;
const int MAXN=200005, LOG = 20;
int N, K, A[MAXN], B[MAXN], T[MAXN], press[3*MAXN], npnts=0, st[3*MAXN][LOG], bit[3*MAXN];
ii c[MAXN];
long long ans = 0;
void update(int x, int v) {for (; x < npnts; x += x&-x) bit[x]+=v;}
int sum(int x) {
	int res = 0;
	for (; x; x-=x&-x) res+=bit[x];
	return res;
}
int queryST(int l, int r) {
	if (l>r) return 0;
	if (l==r) return st[l][0];
	int k = 0;
	while (1<<(k+1) <= r-l) ++k;
	return max(st[l][k], st[r-(1<<k)+1][k]);
}
int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d%d", &N, &K);
	for (int i = 1; i <= N; ++i) {
		scanf("%d%d", A+i, B+i);
		press[++npnts] = A[i]; press[++npnts] = B[i];
	}
	for (int i = 1; i <= K; ++i) {
		scanf("%d", T+i);
		press[++npnts] = T[i];
	}
	++npnts;
	sort(press, press+npnts);
	npnts = unique(press, press+npnts)-press;
	for (int i = 1; i <= K; ++i) {
		T[i] = lower_bound(press, press+npnts, T[i])-press;
		st[T[i]][0] = i; // since i is increasing, this sets it to the maximum for equal values of T[i]
	}
	for (int k = 1; k < LOG; ++k) 
		for (int i = 1; i + (1<<k) - 1 < npnts; ++i) 
			st[i][k] = max(st[i][k-1], st[i+(1<<(k-1))][k-1]);
		
	for (int i = 1; i <= N; ++i) {
		A[i] = lower_bound(press, press+npnts, A[i])-press;
		B[i] = lower_bound(press, press+npnts, B[i])-press;
		c[i].first = queryST(min(A[i],B[i]), max(A[i], B[i]) - 1);
		c[i].second = i;
	}
	sort(c+1, c+1+N);
	int t = K, tot = 0;
	for (int i = N; i; --i) {
		for (; t && c[i].first < t; --t, ++tot) update(T[t], 1);
		int j = c[i].second;
		int after = tot - sum(max(A[j], B[j])-1);
		if (c[i].first==0) {
			if (after&1) ans += 1LL * press[B[j]];
			else ans += 1LL * press[A[j]];
		} else {
			if (after&1) ans += 1LL * press[min(A[j], B[j])];
			else ans += 1LL * press[max(A[j], B[j])];
		}
	}
	printf("%lld\n", ans);
}