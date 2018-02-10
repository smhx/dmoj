#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
const int MAXN = 100005;

int N, Q, s[MAXN], idx[2*MAXN];

set<int> marked[2];

template <int SZ>
struct BIT {
	int _tot=0;
	int _bit[SZ];
	void update(int x) {++_tot; for (; x < SZ; x += x&-x) ++_bit[x];}
	int sum(int x) const {
		int res=0;
		for (; x; x-=x&-x) res+=_bit[x];
		return res;
	}
};

BIT<2*MAXN> confirmed;
BIT<MAXN> rowcnt[2];


int count(int row, int v) {
	printf("counting row %d v = %d\n", row, v);

	int lval1, rval1, lval2, rval2;
	int l1, r1, l2, r2;
	auto l_it1 = marked[row].lower_bound(v);
	if (*l_it1 == v) return 1;
	auto r_it1 = l_it1;
	l_it1--;

	lval1 = *l_it1;
	rval1 = *r_it1;

	l1 = idx[lval1];
	r1 = idx[rval1];

	auto l_it2 = marked[row^1].lower_bound(v);
	if (*l_it2==v) return 1;

	auto r_it2 = l_it2;
	l_it2--;

	lval2 = *l_it2;
	rval2 = *r_it2;

	l2 = idx[lval2];
	r2 = idx[rval2];

	printf("	l1 = %d, lval1 = %d, r1 = %d, rval1 = %d\n", l1, lval1, r1, rval1);

	printf("	l2 = %d, lval2 = %d, r2 = %d, rval2 = %d\n", l2, lval2, r2, rval2);

	int lo, hi=0;

	int minlval = min(lval1, lval2);

	int nplace = v-minlval + 1 - ( confirmed.sum(v) - confirmed.sum(minlval) + 1);

	// int nspotsbottom = r2-l2-1;
	int nspotsbottom = r2 - rowcnt[row^1].sum(r2);
	int nspotstop = l1 - rowcnt[row].sum(l1);

	printf("	minlval = %d, nplace = %d, nspotsbottom = %d, nspotstop =%d\n", minlval, nplace, nspotsbottom, nspotstop);

	if (nplace <= nspotsbottom+nspotstop) {
		printf("	setting lo to +1\n");
		lo = l1+1;
	} else {
		nplace -= nspotsbottom + nspotstop;
		if (nplace <= r1-l1-1) {
			lo = l1 + nplace;
		} else {
			printf("	returning a 0\n");
			return 0;
		}
	}


	// Do the same thing with right...

	int maxrval = max(rval1, rval2);
	nplace = maxrval-v+1 -  (confirmed.sum(maxrval) - confirmed.sum(v) );

	nspotsbottom = N+1 - l2 - (rowcnt[row^1]._tot - rowcnt[row^1].sum(l2));
	nspotstop = N+1-r1 - (rowcnt[row]._tot - rowcnt[row].sum(r1));
	printf("	confirmed.sum(maxrval) = %d, confirmed.sum(v) = %d\n", confirmed.sum(maxrval), confirmed.sum(v));
	printf("	maxrval = %d, nplace = %d, nspotsbottom = %d, nspotstop =%d\n", maxrval, nplace, nspotsbottom, nspotstop);

	if (nplace <= nspotsbottom + nspotstop ) {
		hi = r1-1;
	} else {
		nplace -= nspotsbottom+nspotstop;
		if (nplace <= r1-l1-1) {
			hi = r1 - nplace;
		} else {
			printf("	returning b 0\n");
			return 0;
		}
	}

	if (lo > hi) {
		printf("	returning c 0\n");
		return 0;
	}
	printf("	returning d %d. lo = %d, hi = %d\n", hi-lo+1, lo, hi);
	return hi-lo+1;
}

int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d%d", &N, &Q);
	
	for (int i = 0; i < 2; ++i) {
		marked[i].insert(0);
		marked[i].insert(2*N+1);
		rowcnt[i].update(N+1);
	}
	idx[0] = 0;
	idx[2*N+1] = N+1;
	while (Q--) {
		int op; scanf("%d", &op);
		if (op==1) {
			int r, i, v; scanf("%d%d%d", &r, &i, &v);
			--r;
			marked[r].insert(v);
			idx[v] = i;
			confirmed.update(v);
			rowcnt[r].update(i);
			printf("confirming row %d i = %d, v = %d\n", r, i, v);
		} else {
			int v; scanf("%d", &v);
			printf("%d\n", count(0, v) + count(1, v));
		}
	}
}