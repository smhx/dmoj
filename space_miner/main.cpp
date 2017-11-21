#include <cstdio>
#include <algorithm>
const int MAXM = 1003;
typedef long long ll;
int M, N;
struct point {
	ll x, y, z;
} pl[MAXM], pnt[MAXM];

ll v[MAXM], r[MAXM], D, minerals=0;

bool mined[MAXM];

inline ll sqd(ll a) {
	return a*a;
}


inline ll d2(point p1, point p2) {
	return sqd(p1.x-p2.x) + sqd(p1.y-p2.y) + sqd(p1.z-p2.z);
}


int main() {
	// freopen("data.txt", "r", stdin);
	scanf("%d", &M);
	for (int i = 0; i < M; ++i) {
		scanf("%lld %lld %lld %lld %lld", &pl[i].x, &pl[i].y, &pl[i].z, &v[i], &r[i]);
	}
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) {
		scanf("%lld %lld %lld", &pnt[i].x, &pnt[i].y, &pnt[i].z);
	}
	pnt[0] = {0, 0, 0};
	++N;
	scanf("%lld", &D);
	for (int i = 0; i + 1 < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (mined[j]) continue;

			ll d1sq, d2sq, d3sq; 
			
			d1sq = d2(pnt[i], pl[j]);
			d2sq = d2(pnt[i+1], pl[j]);
			d3sq = d2(pnt[i], pnt[i+1]);

			if (d1sq+d3sq-d2sq >= 0 && sqd(d1sq+d3sq-d2sq) <= 4 * sqd(d3sq) ) {
				if (4*d1sq*d3sq-sqd(d1sq+d3sq-d2sq) <= 4*d3sq*sqd(r[j]+D)) {
					minerals += v[j];
					mined[j] = true;
				}
			} else {
				ll dsqd = std::min(d1sq, d2sq);
				if (dsqd <= sqd(r[j]+D)) {
					minerals += v[j];
					mined[j] = true;
				}
			}

		}
	}
	printf("%lld\n", minerals);
}