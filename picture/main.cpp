#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int,int> ii;
typedef vector<int> vi;
const int MAXN=3000, SIZE = 10005;

int N, perimeter=0, diff[MAXN][MAXN], cnt[MAXN][MAXN], ymap[2*SIZE], xmap[2*SIZE];
vi tmpx, tmpy, xcompress, ycompress;
vector<pair<ii,ii> > rects;

inline void add(vi& v, int x) {v.push_back(x-1); v.push_back(x); v.push_back(x+1);}

void display(const vi& v) {
	for (int x : v) printf("%d ", x);
	printf("\n");
}
int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d", &N);

	if (N==0) return 0;

	for (int i = 0; i < N; ++i) {
		int l, b, r, t; scanf("%d%d%d%d", &l, &b, &r, &t);
		l += SIZE, b+=SIZE, r+=SIZE, t+=SIZE;
		add(tmpx, l); add(tmpx, r);
		add(tmpy, b); add(tmpy, t);
		rects.push_back({{l,b}, {r,t}});
	}
	sort(tmpx.begin(), tmpx.end());
	sort(tmpy.begin(), tmpy.end());
	xcompress.push_back(tmpx[0]);
	for (int i = 1; i < tmpx.size(); ++i) 
		if (tmpx[i]!=tmpx[i-1]) xcompress.push_back(tmpx[i]);

	ycompress.push_back(tmpy[0]);
	for (int i = 1; i < tmpy.size(); ++i) 
		if (tmpy[i]!=tmpy[i-1]) ycompress.push_back(tmpy[i]);

	for (int i = 0; i < xcompress.size(); ++i) xmap[xcompress[i]]=i;
	for (int i = 0; i < ycompress.size(); ++i) ymap[ycompress[i]]=i;

	for (auto rect : rects) {
		int l = xmap[rect.first.first], r = xmap[rect.second.first];
		int b = ymap[rect.first.second], t = ymap[rect.second.second];
		++diff[l][b];
		--diff[l][t];
		--diff[r][b];
		++diff[r][t];
	}

	for (int i = 1; i < xcompress.size(); ++i) {
		for (int j = 1; j < ycompress.size(); ++j) {
			cnt[i][j] = diff[i][j] + cnt[i-1][j]+ cnt[i][j-1] - cnt[i-1][j-1];
		}
	}

	for (int i = 0; i < xcompress.size(); ++i) {
		for (int j = 0; j < ycompress.size(); ++j) {
			cnt[i][j] = cnt[i][j] ? 1 : 0;
		}
	}

	for (int x = 1; x < xcompress.size(); ++x) {
		for (int y = 0; y < ycompress.size()-1; ++y) {
			if (cnt[x-1][y] ^ cnt[x][y]) {
				perimeter += ycompress[y+1] - ycompress[y];
			}
		}
	}

	for (int y = 1; y < ycompress.size(); ++y) {
		for (int x = 0; x < xcompress.size()-1; ++x) {
			if (cnt[x][y-1] ^ cnt[x][y]) {
				perimeter += xcompress[x+1] - xcompress[x];
			}
		}
	}

	printf("%d\n", perimeter);
}