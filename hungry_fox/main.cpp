#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstdlib>
using namespace std;
typedef long long ll;
int N, W;
ll m, M1, M2;

vector<int> t, s;

void minsolve() {

	sort(t.begin(), t.end());

	int i = 0;
	for (; t[i] != W; ++i) m += t[i+1]-t[i];
	
	for (int j = i; j + 1 < t.size(); ++j) m += t[j+1]-t[j];
}

void maxsolve(ll& M, int dir) { // dir=1 for right first
	sort(s.begin(), s.end());

	int c = W, l = 0, r = s.size()-1;
	while (1) {
		// how do you know you can take more?
		if (dir){
			M += 1LL * max(abs(s[r]-c), abs(s[r]-W));
			c=s[r];
			--r;
			if (l>r) break;
		} else {
			M += 1LL * max(abs(s[l]-c), abs(s[l]-W));
			c = s[l];
			++l;
			if (l>r) break;

		}

		if (!dir){
			M += 1LL * max(abs(s[r]-c), abs(s[r]-W));
			c=s[r];
			--r;
			if (l>r) break;
		} else {
			M += 1LL * max(abs(s[l]-c), abs(s[l]-W));
			c = s[l];
			++l;
			if (l>r) break;

		}
		
	}
}


int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d%d", &N, &W);
	t = vector<int>(N+1);
	s = vector<int>(N);
	t[0] = W;
	for (int i = 1; i <= N; ++i) {
		scanf("%d", &t[i]);
		s[i-1] = t[i];
	}


	minsolve();
	
	maxsolve(M1, 1);
	maxsolve(M2,0);

	printf("%lld %lld\n", m, max(M1, M2));
}
