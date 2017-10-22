#include <algorithm>
#include <cstdio>
#include <vector>
#define MAXN 1005
using namespace std;
typedef long long ll;
struct strip {
    int y, l, r, d, on;
    strip() {}
    strip(int Y, int L, int R, int D) : y(Y), l(L), r(R), d(D), on(0) {}
    bool operator<(const strip& f) const { return y < f.y; }
};
int N, T;
ll A = 0;
vector<strip> strips;
vector<int> bars;
int main() {
    strips.reserve(MAXN);
    bars.reserve(MAXN);
    freopen("s4/s4.15.in", "r", stdin);
    scanf("%d%d", &N, &T);
    for (int i = 1; i <= N; ++i) {
        int l, r, b, t, tint;
        scanf("%d%d%d%d%d", &l, &t, &r, &b, &tint);
        bars.push_back(l);
        bars.push_back(r);
        strips.push_back(strip(t, l, r, tint));
        strips.push_back(strip(b, l, r, -tint));
    }
    sort(strips.begin(), strips.end());
    sort(bars.begin(), bars.end());
    for (size_t i = 0; i < bars.size() - 1; ++i) {
        int x = bars[i];
        ll nxtdist = bars[i + 1] - x;
        for (size_t j = 0; j < strips.size(); ++j) {
            if (strips[j].l <= x && strips[j].r > x)
                strips[j].on = 1;
            else
                strips[j].on = 0;
        }
        int tint = 0, last = -1;
        ll len = 0;
        for (size_t j = 0; j < strips.size(); ++j) {
            if (strips[j].on) {
                if (tint >= T && last != -1) len += (strips[j].y - last);
                tint += strips[j].d;
                if (tint >= T) last = strips[j].y;
            }
        }
        A += nxtdist * len;
    }
    printf("%lld\n", A);
}
