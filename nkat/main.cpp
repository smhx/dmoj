#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
typedef pair<int,int> ii;
const int MAXN = 23, INF = 1000000000;

vector<ii> sums;

int N, s[MAXN];

int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) scanf("%d", s+i);
	for (int mask = 1; mask < (1<<N) - 1; ++mask) {
		int cursum = 0;
		for (int k = 0; k < N; ++k) 
			if (mask & (1<<k)) cursum += s[k];
		sums.push_back({cursum, mask});
	}
	sort(sums.begin(), sums.end());
	int minDiff = INF, a = 0, b = 0;
	for (int i = 0; i < sums.size() - 1; ++i) {

		// check if completely contained
		int cura = sums[i].second, curb = sums[i+1].second;
		if (( (cura|curb) == curb) || ( (cura|curb) == cura)) continue;

		int curdiff = sums[i+1].first-sums[i].first;
		if (curdiff<0) curdiff *= -1;
		if (curdiff < minDiff) {
			minDiff = curdiff;
			a = cura;
			b = curb;
		}
	}
	for (int k = 0; k < N; ++k) {
		if ((a&(1<<k)) && (b&(1<<k))) {
			a ^= 1<<k;
			b ^= 1<<k;
		}
	}
	for (int k = 0; k < N; ++k) {
		if (a & (1<<k)) printf("%d ", k+1);
	}
	printf("\n");
	for (int k = 0; k < N; ++k) {
		if (b & (1<<k)) printf("%d ", k+1);
	}
	printf("\n");
}

