#include <map>
#include <unordered_map>
#include <unordered_set>
using namespace std;
typedef pair<int,int> ii;
typedef long long ll;

unordered_map<int,int> cntvalR, cntvalC;
map<ii, int> power;
unordered_map<int,int> xorR, xorC;
unordered_set<int> rv, cv, xorvals;
int N, K, P;

int main() {
	scanf("%d%d%d", &N, &K, &P);
	for(int i = 0; i < K; ++i) {
		int r, c, p; scanf("%d%d%d", &r, &c, &p);
		power[{r,c}] = p;
		xorR[r]^=p;
		xorC[c]^=p;
		rv.insert(r);
		cv.insert(c);
	}
	for (auto q : xorR) {
		cntvalR[q.second]++;
		xorvals.insert(q.second);
	}
	for (auto q : xorC) {
		cntvalC[q.second]++;
		xorvals.insert(q.second);
	}

	cntvalR[0] += N - rv.size();
	cntvalC[0] += N - cv.size();
	ll nzero =0;
	for (int v : xorvals) {
		nzero += 1LL * cntvalR[v] * cntvalC[v];
	}


	for (int i = 0; i < P; ++i) {
		int r1, r2, c1, c2; 
		scanf("%d%d%d%d", &r1, &c1, &r2, &c2);

		int p = power[{r1, c1}];
		power[{r1,c1}] = 0;
		power[{r2,c2}] = p;

		unordered_set<int> vals;
		vals.insert(xorR[r1]); 
		vals.insert(xorR[r2]);
		vals.insert(xorC[c1]);
		vals.insert(xorC[c2]);
		vals.insert(xorR[r1]^p);
		vals.insert(xorR[r2]^p);
		vals.insert(xorC[c1]^p);
		vals.insert(xorC[c2]^p);

		ll oldv = 0;
		for (int v : vals) {
			oldv += 1LL * cntvalR[v] * cntvalC[v];
		}

		if (r1!=r2) {
			--cntvalR[xorR[r1]];
			++cntvalR[xorR[r1]^p];
			--cntvalR[xorR[r2]];
			++cntvalR[xorR[r2]^p];

		}
		
		if (c1 != c2) {
			--cntvalC[xorC[c1]];
			++cntvalC[xorC[c1]^p];
			--cntvalC[xorC[c2]];
			++cntvalC[xorC[c2]^p];
		}

		vals.clear();
		vals.insert(xorR[r1]); 
		vals.insert(xorR[r2]);
		vals.insert(xorC[c1]);
		vals.insert(xorC[c2]);
		vals.insert(xorR[r1]^p);
		vals.insert(xorR[r2]^p);
		vals.insert(xorC[c1]^p);
		vals.insert(xorC[c2]^p);
		ll newv = 0;
		for (int v : vals) {
			newv += 1LL * cntvalR[v] * cntvalC[v];
		}
		xorR[r1]^=p;
		xorR[r2]^=p;
		xorC[c1]^=p;
		xorC[c2]^=p;
		nzero += newv - oldv;
		printf("%lld\n", 1LL*N*N - nzero);
	}
}