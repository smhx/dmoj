#include <cstdio>
#include <algorithm>
#include <queue>
const int MAXN = 1505;

int N, nbars, A[MAXN], bars[MAXN];

std::queue<int> q;

bool possible() {
	int idx = 0;
	for (int b = 0; b < nbars; ++b) 
		for (; idx < bars[b]; ++idx) if (A[idx] > bars[b]) return false;
	return true;
}

inline void move(int i) {std::swap(A[i], A[i+1]); q.push(i);}

void bubble(int s, int n) {
	for (; n>1; --n) {
		int i = std::max_element(A+s, A+s+n)-A;
		while (i != s+n-1) {
			int k = 0;
			while (i+k+1 < s+n && A[i+k+1]==i+k) ++k;
			if (i+k==s+n-1) {
				for (int j = i; j < i+k; ++j) move(j);
				i = s+n-1;
			} else {
				for (int j = i+k; j > i; --j) move(j);
				for (int j=i; j <= i+k; ++j) move(j);
				i += k+1;
			}
		}
	}
}

int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		scanf("%d", A+i);
		if (A[i]==i) bars[nbars++] = i;
	}
	bars[nbars] = N;
	if (!possible()) return !printf("Give up\n"); 
	bubble(0, bars[0]);
	for (int b = 0; b < nbars; ++b) bubble(bars[b]+1, bars[b+1]-bars[b]-1);
	printf("%lu\n", q.size());
	for (; !q.empty(); q.pop()) printf("%d %d\n", q.front(), q.front()+1);
}