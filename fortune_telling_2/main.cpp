#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
typedef pair<int,int> ii;
typedef long long ll;
const int MAXN = 200005, LOG = 20, INF = 1000000009;
int N, K;
int A[MAXN], B[MAXN], T[MAXN];
int last[MAXN];

int bit[MAXN];

int sparse[MAXN][LOG];

int after[MAXN];

vector<ii> tvals;

int sum(int x) {
	int res = 0;
	for (; x ; x-=x&-x) res += bit[x];
	return res;
}

void update(int x, int v) {
	for (; x < MAXN; x+=x&-x) bit[x]+=v;
}

int compressedIndex(int x) {
	return lower_bound(tvals.begin(), tvals.end(), ii(x, -INF)) - tvals.begin();
}

int querySparse(int a, int b) {
	if (a==b) return sparse[a][0];
	int k=0;
	// a + 2^k <= b. k <= log(b-a)
	while (1<<(k+1) <= b-a) ++k;
	int x = sparse[a][k];
	int y = sparse[b-(1<<k)+1][k];

	return max(x,y);
}

int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d%d", &N, &K);
	for (int i = 0; i < N; ++i) {
		scanf("%d %d", A+i, B+i);
	}

	for (int i = 0; i < K; ++i) {
		scanf("%d", T+i);
		tvals.push_back({T[i], i});
	}

	sort(tvals.begin(), tvals.end());

	for (int i = 0; i < tvals.size(); ++i) {
		sparse[i][0] = tvals[i].second; // the T number
	}

	for (int k = 1; k < LOG; ++k) {
		for (int i = 0; i + (1<<k)< tvals.size(); ++i) {
			int a = sparse[i][k-1];
			int b = sparse[i+(1<<(k-1))][k-1];
			if (a >= b) sparse[i][k] = a;
			else sparse[i][k] = b;
		}
	}

	for (int i = 0; i < N; ++i) {
		
		if (A[i]==B[i]) {
			last[i] = -1;
		} else {
			int compressA = compressedIndex(min(A[i], B[i]));
			int compressB = compressedIndex(max(B[i], A[i]) );
			--compressB;
			if (compressB < compressA) last[i] = -1;
			else last[i] = querySparse(compressA, compressB);

		}
	}

	vector<ii> x;
	for (int i = 0; i < N; ++i) x.push_back({last[i],i});
	sort(x.begin(), x.end());
	
	int xidx = x.size()-1;

	for (int k = K-1; k>=0; --k) {
		while (xidx>=0 && x[xidx].first == k) {
			int i = x[xidx].second;
			int b = max(A[i], B[i]);
			int cmpr = lower_bound(tvals.begin(), tvals.end(), ii(b, -INF) )-tvals.begin();
			if (cmpr==0) after[i] = sum(MAXN-1);
			else after[i] = sum(MAXN-1)-sum(cmpr);
			--xidx;
		}
		int tidx = compressedIndex(T[k]);
		update(tidx+1, 1);
	}
	while (xidx>=0) {
		int i = x[xidx].second;
		int b = max(A[i], B[i]);
		int cmpr = lower_bound(tvals.begin(), tvals.end(), ii(b, -INF) )-tvals.begin();
		if (cmpr==0) after[i] = sum(MAXN-1);
		else after[i] = sum(MAXN-1)-sum(cmpr);
		--xidx;
	}
	ll ans =0;
	for (int i=0; i<N;++i) {
		if (last[i]==-1) {
			if (after[i]&1) ans += 1LL*B[i];
			else ans += 1LL*A[i];
		} else {
			if (after[i]&1) ans += 1LL*min(A[i], B[i]);
			else ans += 1LL*max(A[i], B[i]);
		}
	}
	printf("%lld\n", ans);
}