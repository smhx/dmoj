#include <vector>
#include <queue>
#include <cstdio>
#include <functional>
#include <algorithm>
using namespace std;

const int MAXN = 200005;

int N, cost, cnt[MAXN];
vector<int> p[MAXN];

priority_queue<int, vector<int>, greater<int> > pq;

int main() {
	scanf("%d", &N);
	for (int i = 0, a, b; i < N; ++i) {
		scanf("%d%d", &a, &b);
		p[a].push_back(b);
	}
	for (int a = 0; a <= N; ++a) {
		cnt[a] = p[a].size();
		if (a) cnt[a] += cnt[a-1]; 
	}
	int l = 0, r = N, extra=0;
	while (l < r) {
		if (!p[l].empty()) {
			extra += p[l].size()-1;
		} else if (extra) {
			--extra;
		} else {
			while (r > l && cnt[r-1]-cnt[l-1] >= r-l) {
				while (!p[r].empty()) {
					pq.push(p[r].back());
					p[r].pop_back();
				}
				--r;
			}
			if (l==r) break;
			while (!p[r].empty()) {
				pq.push(p[r].back());
				p[r].pop_back();
			}
			cost += pq.top();
			pq.pop();
		}
		++l;
	}
	printf("%d\n", cost);
}