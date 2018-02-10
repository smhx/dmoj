#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <functional>
using namespace std;
const int MAXN = 100005;
typedef pair<int,int> ii;
int N, A[MAXN], idx[MAXN], bit[MAXN], lowans[MAXN], hians[MAXN];

vector<ii> lower, upper;

void updateLeft(int x, int v) {
	for (; x<MAXN; x+=x&-x) bit[x]+=v;
}

int sumLeft(int x) {
	int res = 0;
	for (; x; x-=x&-x) res += bit[x];
	return res;
}

void updateRight(int x, int v) {
	for (; x; x-=x&-x) bit[x] += v;
}

int sumRight(int x) {
	int res = 0;
	for (; x < MAXN; x += x&-x) res += bit[x];
	return res;
}

void processLower() {
	int hi = 1;
	for (ii q : lower) {
		int k = q.second;
		int hval = N - k/2+1; 
		int idx = q.first;
		while (hi <= idx) {
			updateRight(A[hi], 1);
			++hi;
		}

		lowans[k] = sumRight(hval); 
	}
}

void processUpper() {
	int lo = N;
	for (ii q : upper) {
		int k = q.second;
		int lval = k/2; 
		int idx = q.first;

		while (lo>=idx) {
			updateLeft(A[lo], 1);
			--lo;
		}
		hians[k] = sumLeft(lval);
	}
}

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) {
		scanf("%d", A+i);
		idx[A[i]] = i;
	}
	int lo = 0, hi = N+1;
	for (int k = 1; k <= N; ++k) {
		int val;
		if (k&1) val = ++lo;
		else val = --hi;
		lower.push_back(ii(idx[val]-1, k));
		upper.push_back(ii(idx[val]+1, k));
	}
	sort(lower.begin(), lower.end());
	sort(upper.begin(), upper.end(), greater<ii>());
	processUpper();
	memset(bit, 0, sizeof bit);
	processLower();
	for (int k = 1; k <= N; ++k) {
		int swaps;
		if (k&1) {
			int val = k/2+1;
			swaps = idx[val] - lowans[k] + hians[k] - val;
		} else {
			int val = N-k/2+1;
			swaps = val - idx[val] + lowans[k] - hians[k];
		}
		printf("%d\n", swaps);
	}
}