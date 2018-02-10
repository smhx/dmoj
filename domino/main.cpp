#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

const int MAXN = 2003, INF = 1000000000;
int N, M, K, t[MAXN][MAXN];

typedef pair<int, pair< pair<int,int>, bool> > dominoe;

vector<dominoe> d;

bool adj[100][100];

int A = 20;
int mem[2000000];

bool overlap(dominoe a, dominoe b) {
	if (a.second.first == b.second.first) return true;
	// overlap end of a, start of b
	pair<int,int> enda, endb;

	if (a.second.second) enda = {a.second.first.first+1, a.second.first.second};
	else enda = {a.second.first.first, a.second.first.second+1};

	if (enda == b.second.first) return true;

	if (b.second.second) endb = {b.second.first.first+1, b.second.first.second};
	else endb = {b.second.first.first, b.second.first.second+1};

	if (endb == a.second.first) return true;

	if (endb == enda) return true;

	return false;
}

int dp(int mask) {
	if (mem[mask]!=-1) return mem[mask];

	int sz = 0;
	for(int i = 0; i < A; ++i) if (mask&(1<<i)) ++sz;

	if (sz > K) {
		int ans = -INF;
		for (int i = 0; i < A; ++i) {
			if (mask&(1<<i)) {
				ans = max(ans, dp(mask^(1<<i)));
			}
		}
		return mem[mask] = ans;
	}

	for (int i = 0; i < A; ++i) {
		for (int j = i+1; j < A; ++j) {
			if ((mask&(1<<i)) && (mask&(1<<j))) {
				if (!adj[i][j]) return mem[mask] = -INF;
			}
		}
	}
	int sum = 0;
	for (int i = 0; i < A; ++i) if (mask&(1<<i)) sum += d[i].first;
	return mem[mask] = sum;
}

int main() {
	scanf("%d%d", &N, &K);

	M = 7*(K-1)+1;

	for (int i = 1; i <= N; ++i) 
		for (int j = 1; j <= N; ++j) scanf("%d", &t[i][j]);

	for (int i = 1; i <= N; ++i) 
		for (int j = 1; j < N; ++j) d.push_back({t[i][j]+t[i][j+1], {{i,j}, true}} );

	for (int j = 1; j <= N; ++j)
		for (int i = 1; i < N; ++i) d.push_back({t[i][j]+t[i+1][j], {{i,j}, false}});

	sort(d.begin(), d.end());
	
	// Take M.
	
	M = min(M, (int)d.size());
	
	for (int i = 0; i < M; ++i) {
		for (int j = i+1; j < M; ++j) {
			if (!overlap(d[i], d[j])) {
				adj[i][j] = adj[j][i] = true;
			}
		}
	}		
	A = min(A, M);

	int B = M-A;
	for (int D = 0; D <= K; ++D) {
		int mask = 0;
		for (int i = 0; i < A; ++i) mask |= 1<<i;
		memset(mem, -1, sizeof mem);
		dp(mask);
		for (mask = 0; mask < (1<<B); ++mask) {
			int amask = 0;
			for (int i = 0; i < A; ++i) {
				bool works = true;
				for (int j = A; j < M; ++j) {
					
				}
			}
		}
	}

	

	
}
