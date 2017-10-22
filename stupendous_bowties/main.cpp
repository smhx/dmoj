#include <cstdio>
#include <algorithm>
#include <unordered_map>
#include <vector>
#define MAXN 100005
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> ii;

unordered_map<ll, int> xmap, ymap; // maps x, y coordinate to index
int N, uniqueX=0, uniqueY=0, left[MAXN], right[MAXN], under[MAXN], above[MAXN];
pll pnts[MAXN];
ll cnt;
vector<ll> xpnts, ypnts;

vector<ii> col[MAXN], row[MAXN];

int main() {
    // freopen("data.txt", "r", stdin);
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%lld %lld", &pnts[i].first, &pnts[i].second);
        xpnts.push_back(pnts[i].first);
        ypnts.push_back(pnts[i].second);
    }
    sort(xpnts.begin(), xpnts.end());
    sort(ypnts.begin(), ypnts.end());

    xmap[xpnts[0]] = 0;

    ymap[ypnts[0]] = 0;
    for (int i = 1; i < (int)xpnts.size(); ++i) {
        if (xpnts[i] != xpnts[i-1]) 
            xmap[xpnts[i]] = ++uniqueX;
    }

    for (int i = 1; i < (int)ypnts.size(); ++i) {
        if (ypnts[i] != ypnts[i-1]) 
            ymap[ypnts[i]] = ++uniqueY;
    }

    ++uniqueX, ++uniqueY;

    for (int i = 0; i < N; ++i) {
        col[xmap[pnts[i].first]].push_back(ii(ymap[pnts[i].second], i));
        row[ymap[pnts[i].second]].push_back(ii(xmap[pnts[i].first], i ));
    }

    for (int i = 0; i < uniqueY; ++i) sort(row[i].begin(), row[i].end());
    for (int i = 0; i < uniqueX; ++i) sort(col[i].begin(), col[i].end());

    for (int i = 0; i < uniqueY; ++i) {
        if (row[i].size()) {
            left[row[i][0].second] = 0;
            for (int j = 1, lft=0; j < (int)row[i].size(); ++j) {
                if (row[i][j].first != row[i][j-1].first) ++lft;
                left[row[i][j].second] = lft;
            }
            right[row[i][row[i].size()-1].second] = 0;
            for (int j = (int)row[i].size()-2, rt=0; j >=0; --j) {
                if (row[i][j].first != row[i][j+1].first) ++rt;
                right[row[i][j].second] = rt;
            }
        }
    }

    for (int i = 0; i < uniqueX; ++i) {
        if (col[i].size()) {
            under[col[i][0].second] = 0;
            for (int j = 1, undr=0; j < (int)col[i].size(); ++j) {
                if (col[i][j].first != col[i][j-1].first) ++undr;
                under[col[i][j].second] = undr;
            }
            above[col[i][col[i].size()-1].second] = 0;
            for (int j = (int)col[i].size()-2, rt=0; j >= 0; --j) {
                if (col[i][j] != col[i][j+1])++rt;
                above[col[i][j].second] = rt;
            }
        }
    }

   for (int i = 0; i < N; ++i) 
        cnt += 2LL * ll(under[i]) * ll(above[i]) * ll(left[i]) * ll(right[i]);
   
    printf("%lld\n", cnt);

}