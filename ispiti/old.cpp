#include <cstdio>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int,int> ii;
const int MAXN = 200005, LOG = 18;

struct query {
	char cmd; 
	int A, B, idx, i;
} q[MAXN];

// B is knowdlege, A is understanding
int N, A[MAXN], B[MAXN], maxA[MAXN];

map<ii, int> mp;

vector<int> compressA, compressB;

set<int> Avals[MAXN];

struct node {int l, r, mx;} segt[4*MAXN];

void build(int u, int l, int r) {
	segt[u].l = l, segt[u].r = r;
	segt[u].mx = 0;
	if (l!=r) {
		int m = (l+r)/2;
		build(u<<1, l, m); build(u<<1|1, m+1, r);
	}
}

void update(int u, int idx, int val) {
	if (segt[u].l == idx && segt[u].r == idx) segt[u].mx = val;
	else {
		int m = (segt[u].l + segt[u].r)/2;
		if (segt[u].l <= idx && idx <= m) update(u<<1, idx, val);
		else update(u<<1|1, idx, val);
		segt[u].mx = max(segt[u<<1].mx, segt[u<<1|1].mx);
	}
}

int query(int u, int l, int r) {
	if (r < segt[u].l || l > segt[u].r) return 0;
	else if (l <= segt[u].l && segt[u].r <= r) return segt[u].mx;
	int left = query(u<<1, l, r), right = query(u<<1|1, l, r);
	return max(left, right);
}

void eraseUnique(vector<int>& x) {
	sort(x.begin(), x.end());
	compressA.erase(unique(x.begin(), x.end()), x.end());
}

int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d", &N);
	int idx = 1;
	for (int i = 1; i <= N; ++i) {
		scanf(" %c", &q[i].cmd);
		if (q[i].cmd == 'D') {
			scanf("%d %d", &q[i].A, &q[i].B);
			compressA.push_back(q[i].A);
			compressB.push_back(q[i].B);
			q[i].idx = idx;
			idx++;
		} else {
			scanf("%d", &q[i].i);
		}
	}
	eraseUnique(compressA);
	eraseUnique(compressB);
	for (int i = 1; i <= N; ++i) {
		if (q[i].cmd=='D') {
			q[i].A = lower_bound(compressA.begin(), compressA.end(), q[i].A)-compressA.begin()+1;
			q[i].B = lower_bound(compressB.begin(), compressB.end(), q[i].B)-compressB.begin()+1;
			A[q[i].idx] = q[i].A;
			B[q[i].idx] = q[i].B;
			mp[ii(q[i].A, q[i].B)] = q[i].idx;
		}
	}
	build(1, 1, compressB.size());
	for (int i = 1; i <= N; ++i) {
		if (q[i].cmd=='D') {
			if (maxA[q[i].B] < q[i].A) {
				maxA[q[i].B] = q[i].A;
				update(1, q[i].B, q[i].A);
			}
			Avals[q[i].B].insert(q[i].A);
		} else {
			int a = A[q[i].i], b = B[q[i].i];
			printf("query a = %d, b = %d\n", a, b);
			for (int i = 1; i <= compressB.size(); ++i) {
				printf("maxA[%d] = %d\n", i, maxA[i]);
			}
			if (maxA[b] == a) {
				if (b==compressB.size()) {
					printf("NE\n");
					continue;
				}
				++b;
				for (int k = LOG-1; k >= 0; --k) {
					if (b + (1<<k) <= compressB.size() ) {
						int x = query(1, b, b + (1<<k));
						if (x < a) {
							b += 1 << k;
						}
					}
				}
				if (b==compressB.size()) {
					printf("NE\n");
					continue;
				}				
				++b;
			}
			
			auto it = Avals[b].upper_bound(a);
			if (it==Avals[b].end()) {
				printf("NE\n");
			} else {
				printf("ANSWER: %d\n", mp[ii(*it, b)]);				
			}
		}
	}

}