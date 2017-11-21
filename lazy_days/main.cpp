#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

#ifdef DMOJ
#define getchar() (*_pbuf ? *_pbuf++ : (_buf[fread_unlocked(_pbuf = _buf, 1, 1048576, stdin)] = 0, *_pbuf++))
char _buf[1048577], *_pbuf = _buf;
#endif

int readint() {
	int c, o = 0;
	while ((c = getchar()) < '0');
	do {o = (o<<3)+(o<<1) + (c - '0');} while ((c = getchar()) >= '0');
	return o;
}

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
const int MAXN = 200005, INF = 1000000000, LOG=18;

int N,lbound=INF, ubound=INF, A[MAXN], B[MAXN], w[MAXN], ans[MAXN];

int bit[MAXN], bitsize=0;
ii C[MAXN];
vector<pair<int, vi > > v;

int sum(int x) {
	int res = 0; 
	for (; x; x-=x&-x) res += bit[x];
	return res;
}

void update(int x, int v) {for(;x<= N; x+=x&-x) bit[x]+=v;}

int get(int k) {
	int x = 0, s = 0;
	for (int i = LOG; i >= 0; --i) 
		if (x+ (1<<i) <= N) 
			if (s + bit[x+(1<<i)] < k) s += bit[x+(1<<i)], x += 1<<i;
	return x+1;
}

int main() {
	freopen("data.txt", "r", stdin);
	N = readint();
	for (int i = 0; i < N; ++i) A[i] = readint();
	for (int i = 0; i < N; ++i) B[i] = readint();

	for (int i = 0; i < N; ++i) C[i] = ii(min(A[i], B[i]), i );

	for (int i = 0; i < N; ++i) 
		lbound = min(lbound, A[i]), ubound = min(ubound, max(A[i], B[i]));

	sort(C, C+N);

	for (int i = 0; i < N;) {
		int n = C[i].first;
		v.emplace_back(pair<int, vi>(n, vi()));
		for (; C[i].first == n && i < N; ++i) 
			v.back().second.emplace_back(C[i].second);
	}


	for (int i = 0; i < v.size(); ++i) {
		if (i) w[i] = w[i-1];
		for (int j = 0; j < v[i].second.size(); ++j) {
			int cur = v[i].second[j];
			if (A[cur]==B[cur]) continue;
			int cur_ch = A[cur] > B[cur] ? 0 : 1;
			if (!bitsize) {
				if (cur_ch) ++w[i];
			} else {
				int k = sum(cur+1);

				if (!k) {
					int nxt = get(k+1)-1;
					if (A[nxt] > B[nxt] && cur_ch==1) w[i] += 2;
				} else {
				
					int pre = get(k)-1;

					int pre_ch = A[pre] > B[pre] ? 0 : 1;

					if (k == bitsize) {
						if (pre_ch != cur_ch) ++w[i];
					} else {
						int nxt = get(k+1)-1;
						int nxt_ch = A[nxt] > B[nxt] ? 0 : 1;
						if (nxt_ch==pre_ch && pre_ch != cur_ch) w[i] += 2;
					}
				}
			}
			update(cur+1, 1);
			++bitsize;
		}
	}
	memset(ans, -1, sizeof ans);
	ans[0] = lbound;
	for (int i = 0; i < v.size(); ++i) 
		ans[w[i]] = min(ubound, max(ans[w[i]], i+1 >= v.size() ? INF : v[i+1].first) );
	
	printf("%d\n", ans[0]);
	for (int i = 1, p = ans[0]; i <= N; ++i) {
		if (ans[i]==-1) ans[i] = p;
		else p = ans[i];
		printf("%d\n", ans[i]);
	}
}