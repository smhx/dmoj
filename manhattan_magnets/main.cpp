#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <vector>
using namespace std;
typedef pair<int, int> ii;
const int MAXN = 100005, INF = 1000000000;//, EXTRA_X = 8000, EXTRA_Y = 12000;
int N, M, metalx[MAXN], metaly[MAXN], magx[MAXN], magy[MAXN], d[MAXN];
vector<pair<ii, int> > tmp_diff, diff;
vector<int> compressX, compressY;
bool cmpy(const pair<ii,int>& a, const pair<ii,int>&b ) {return a.first.second != b.first.second ? a.first.second < b.first.second : a.first.first < b.first.first;}
inline int compressedIndex(const vector<int>& a, int b) {return lower_bound(begin(a), end(a), b) - begin(a);}
int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d", &M);
	for (int i = 1; i <= M; ++i) scanf("%d%d", magx+i, magy+i);
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) {
		scanf("%d%d", metalx+i, metaly+i);
		d[i] = INF;
		for (int j = 1; j <= M; ++j) 
			d[i] = min(d[i], abs(metalx[i]-magx[j]) + abs(metaly[i] - magy[j]) );
		--d[i];
	}
	for (int i = 1; i <= N; ++i) {
		int x = metalx[i], y = metaly[i];
		int xlo = x-d[i]+y;
		int xhi = x+d[i]+y;
		int ylo = y-x-d[i];
		int yhi = y-x+d[i];
		tmp_diff.push_back({{xlo, ylo}, 1});
		tmp_diff.push_back({ {xhi+1, yhi+1}, 1});
		tmp_diff.push_back({{xlo, yhi+1}, -1});
		tmp_diff.push_back({{xhi+1, ylo}, -1});
	}
	sort(begin(tmp_diff), end(tmp_diff));
	diff.push_back(tmp_diff[0]);
	for (int i = 1; i < tmp_diff.size(); ++i) {
		if (tmp_diff[i].first != diff.back().first) diff.push_back({tmp_diff[i].first, 0});
		diff.back().second += tmp_diff[i].second;
	}
	compressX.push_back(diff[0].first.first);
	for (int i = 1; i < diff.size(); ++i) 
		if (diff[i].first.first != compressX.back() ) compressX.push_back(diff[i].first.first);
	sort(begin(diff), end(diff), cmpy);
	compressY.push_back(diff[0].first.first);
	for (int i = 1; i < diff.size(); ++i) 
		if (diff[i].first.second != compressY.back() ) compressY.push_back(diff[i].first.second);
	int nx = compressX.size(), ny = compressY.size();
	vector<int> slide[2];
	slide[0] = vector<int>(nx); slide[1] = vector<int>(nx);
	int ans = 0, idx = 0, add = 0;
	int curRow, curCol;
	curRow = compressedIndex(compressY, diff[idx].first.second);
	curCol = compressedIndex(compressX, diff[idx].first.first);
	for (int r = 0; r < ny; ++r) {
		for (int c = 0; c < nx; ++c) {
			if (r==curRow && c==curCol) {
				add += diff[idx].second;
				++idx;
				int newRow = compressedIndex(compressY, diff[idx].first.second);
				if (newRow != curRow) {
					add = 0;
					curRow = newRow;
				}
				curCol = compressedIndex(compressX, diff[idx].first.first);
			}
			slide[r&1][c] = add;
			if (r) slide[r&1][c] += slide[(r-1)&1][c];
			ans = max(ans, slide[r&1][c]);
		}
	}
	printf("%d\n", ans);
}