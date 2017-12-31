#include <cstdio>
#include <algorithm>
#include <stack>
#include <cstring>
using namespace std;
typedef pair<int,int> ii;
const int MAXN = 100005;

int N, leaf, pre[MAXN], h[MAXN], idx[MAXN], cnt[MAXN], maxr, rpress[MAXN], bit[MAXN];

ii pnts[MAXN];

void update(int x, int idx) {
	for (; x; x-=x&-x) 
		if (cnt[bit[x]] < cnt[idx]) bit[x] = idx;
}

int query(int x) {
	int res=0;
	for (; x <= maxr; x += x&-x) 
		if (cnt[bit[x]]> cnt[res]) res = bit[x];
	return res;
}

int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d", &N);
	for (int i = 0; i < N; ++i){
		scanf("%d%d", &pnts[i].first, &pnts[i].second);
		rpress[maxr++] = pnts[i].second;
	}
	sort(pnts, pnts+N, [](ii a, ii b) {return a.first != b.first ? a.first < b.first : a.second > b.second;});
	sort(rpress, rpress+maxr);
	maxr = unique(rpress, rpress+maxr)-rpress;
	idx[0] = -1;
	for (int i = 0; i < N; ++i) {
		int r_idx = lower_bound(rpress, rpress+maxr, pnts[i].second)-rpress+1;
		int last = query(r_idx); 
		pre[i] = idx[last];
		h[i] = h[pre[i]]+1;
		cnt[r_idx] = h[i];
		update(r_idx, r_idx);
		idx[r_idx]=i;
		if (h[i] > h[leaf]) leaf = i;
	}
	stack<ii> display;
	for (;leaf!=-1; leaf=pre[leaf]) display.push(pnts[leaf]);
	for (;!display.empty(); display.pop()) printf("%d %d\n", display.top().first, display.top().second);
}
