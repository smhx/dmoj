#include <queue>
#include <set>
#include <vector>
using namespace std;

typedef pair<int,int> ii;
typedef pair<int,ii> diff_t;

const int MAXN = 10005, SQRT = 130;

int N, Q, c[MAXN];

struct query {
	int l, r, lca, id;
	bool operator<(const query& q) const {return (l-1)/SQRT!=(q.l-1)/SQRT?l<q.l:r<q.r;}
} q[MAXN];

int ans[MAXN];
priority_queue<diff_t, vector<diff_t>, greater<diff_t> > pq;
bool active[MAXN];

multiset<ii> ms;
void remove(int pos) {
	printf("removing %d\n", pos);
	active[pos] = false;
	auto it = ms.lower_bound(ii(c[pos], pos));
	if (it != --ms.end() && it != ms.begin()) {
		auto pre = it, nxt = it;
		--pre; ++nxt;
		pq.push({nxt->first - pre->first, {pre->second, nxt->second}});
	}
	ms.erase(ii(c[pos], pos));
}

void add(int pos) {
	printf("adding pos = %d\n", pos);
	active[pos] = true;
	auto it = ms.lower_bound(ii(c[pos], -1));
	if (it != ms.end()) {
		printf("	next after pos. adding diff = %d with pos2 = %d\n", it->first-c[pos], it->second);
		pq.push({it->first - c[pos], {pos, it->second}});
	}
	if (it != ms.begin()) {
		--it;
		printf("	pre before pos. adding diff = %d with pos2 = %d\n", c[pos]-it->first, it->second);
		pq.push({c[pos]-it->first, {it->second, pos}});
	}
	ms.insert({c[pos], pos});
}

int query() {
	while (!pq.empty()) {
		diff_t d = pq.top();
		if (active[d.second.first] && active[d.second.second]) {
			printf("query returning (%d, (%d, %d) )\n", d.first, d.second.first, d.second.second);
			return d.first;
		} 
		pq.pop();
	}
	return -1;
}

void MO() {
	sort(q, q+Q);
	int curL = 1, curR = 1;
	for (int i = 0; i < Q; ++i) {
		printf("QUERY (%d, %d)\n", q[i].l, q[i].r);
		while (curR <= q[i].r) {
			add(curR);
			++curR;
		}
		while (curR > q[i].r+1) {
			remove(curR-1);
			--curR;
		}

		while (curL > q[i].l) {
			curL--;
			add(curL);
		}

		while (curL < q[i].l) {
			remove (curL);
			curL++;
		}
		ans[q[i].id] = query();
	}
}

int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d%d", &N, &Q);
	for (int i = 1; i <= N; ++i) scanf("%d", c+i);
	for (int i = 0; i < Q; ++i) {
		scanf("%d%d", &q[i].l, &q[i].r);
		q[i].id = i;
	}
	MO();
	for (int i = 0; i < Q; ++i) {
		printf("%d\n", ans[i]);
	}
}