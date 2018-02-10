#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
typedef pair<int,int> ii;
const int MAXN = 200005, LOG = 20, INF = 1000000000;

struct query {
	char cmd;
	int A, B, idx;
} q[MAXN];

int N, M, numppl=0, maxa[MAXN], A[MAXN], B[MAXN], t[2*MAXN];

vector<int> cb;
set<ii> avals[MAXN];

// sets element x to v, zero indexed.
void update(int x, int v) {
    for (t[x+=M]=v; x>1; x >>= 1) t[x>>1] = max(t[x], t[x^1]);
}

// returns the max in the range [l, r), zero indexed.
int query(int l, int r) {
    int ans = 0;
    for (l+=M, r+=M; l < r; l >>= 1, r >>= 1) {
        if (l&1) ans = max(ans, t[l++]);
        if (r&1) ans = max(ans, t[--r]);
    } 
    return ans;
}

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) {
		scanf(" %c", &q[i].cmd);
		if (q[i].cmd =='D') {
			scanf("%d%d", &q[i].A, &q[i].B);
			cb.push_back(q[i].B);
			q[i].idx = ++numppl;
		} else {
			scanf("%d", &q[i].idx);
		}
	}
	sort(cb.begin(), cb.end());
	cb.erase(unique(cb.begin(), cb.end()), cb.end());
	M = cb.size();
	for (int i = 1; i <= N; ++i) {
		if (q[i].cmd=='D') {
			q[i].B = lower_bound(cb.begin(), cb.end(), q[i].B)-cb.begin();
			A[q[i].idx] = q[i].A;
			B[q[i].idx] = q[i].B;
		}
	}
	int maxb=-1;
	for (int i = 1; i <= N; ++i) {
		if (q[i].cmd=='P') {

			int idx = q[i].idx;
			int a = A[idx];
			int b = B[idx];
			if (maxa[b] == a) {
				if (b==maxb) {
					printf("NE\n");
					continue;
				}
				++b;
				if (maxa[b] < a) {
					for (int k = LOG-1; k>=0; --k) {
						if (b + (1<<k) <= maxb) {
							if (query(b+1, b+(1<<k)+1) < a) {
								b += (1<<k);
							}
						}
					}
					if (b==maxb) {
						printf("NE\n");
						continue;
					}
					++b;
				}
				auto it = avals[b].lower_bound(ii(a, -INF) );
				printf("%d\n", it->second);
			} else {
				auto it = avals[b].upper_bound(ii(a, INF) );
				printf("%d\n", it->second);
			}
		} else {
			maxb = max(maxb, q[i].B);
			if (maxa[q[i].B] < q[i].A) {
				maxa[q[i].B] = q[i].A;
				update(q[i].B, q[i].A);
			}
			avals[q[i].B].insert(ii(q[i].A, q[i].idx));
		}
	}
}