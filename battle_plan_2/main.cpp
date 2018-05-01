#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 2e5+5, MAXQ = 1e5+5, MAXK = 55, LOG = 20;

struct job {
	int l, r, id;
};

vector<job> jobs[MAXK];
int jobans[MAXQ];

int N, K, Q, nxt[MAXN][LOG], mx[MAXN][LOG];
ll a[MAXN], b[MAXN];
void build(int B) {
	int l = 1;
	ll sum = 0;
	for (int i = 1; i <= N; ++i) {
		sum += a[i];
		while (l < i && sum > B){
			nxt[l][0] = i;
			sum -= a[l];
			++l;
		}
	}
	for (; l <= N; ++l) {
		nxt[l][0] = N+1;
	}

	for (int k = 1; k < LOG; ++k) {
		for (int i = 1; i <= N; ++i) {
			nxt[i][k] = nxt[nxt[i][k-1]][k-1];
		}
	}
}

int query(int l, int r) {
	int cnt = 0, at = l;
	for (int k = LOG-1; k >= 0; --k) {
		if (nxt[at][k] != 0 && nxt[at][k] <= r) {
			at = nxt[at][k];
			cnt |= 1<<k;
		}
	}
	return cnt+1;
}

void buildmx() {
	for (int i = 1; i <= N; ++i) mx[i][0] = a[i];
	for (int k = 1; k < LOG; ++k) {
		for (int i = 1; i + (1<<k) - 1 <= N; ++i)
			mx[i][k] = max(mx[i][k-1], mx[i+(1<<(k-1))][k-1]);
	}
}

int querymx(int l, int r) {
	int k = 0;
	while (l+(1<<k)-1 <= r) ++k;
	--k;
	int ans = max(mx[l][k], mx[r-(1<<k)+1][k]);
	return ans;
}

int main() {
	scanf("%d%d%d", &N, &K, &Q);
	for (int i = 1; i <= N; ++i) {
		scanf("%lld", a+i);
	}
	buildmx();
	for (int i = 1; i <= K; ++i) {
		scanf("%lld", b+i);
	}
	for (int id = 0; id < Q; ++id) {
		job jb; int j;
		scanf("%d%d%d", &j, &jb.l, &jb.r);
		jb.id = id;
		jobs[j].push_back(jb);
	}

	for (int j = 1; j <= K; ++j) {
		build(b[j]);
		for (auto jb : jobs[j]) {
			int rangemx = querymx(jb.l, jb.r);
			if (rangemx > b[j]) jobans[jb.id] = -1;
			else jobans[jb.id] = query(jb.l, jb.r);
		}
	}
	for (int id = 0; id < Q; ++id) {
		printf("%d\n", jobans[id]);
	}
}