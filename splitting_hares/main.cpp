#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
const int MAXN = 4003;
const double PI = atan(1) * 4.0, EPS = 1e-6;
struct point {double x,y;} p[MAXN];
int N, best = -1000000000, w[MAXN];
double angle(point p1, point p2) {
	if (fabs(p1.x-p2.x) <= EPS) {
		if (p1.y < p2.y) return PI/2.0;
		else return 3.0*PI/2.0;
	}
	if (p1.x < p2.x) {
		double theta = atan((p2.y-p1.y)/(p2.x-p1.x));
		if (theta >= 0) return theta;
		else return theta+2*PI;
	}

	double theta = atan((p2.y-p1.y)/(p1.x-p2.x));
	return PI-theta;
}

inline int sumFromTo(int a, int b,const vector<int>& presum) {
	if(a<=b) {
		if (a==0) return presum[b];
		else return presum[b]-presum[a-1];
	}

	return presum[b] + presum.back() - presum[a-1];
}

void solve(const vector<pair<double,int> >& q, int i) {

	if (q[0].first >= PI) return;

	vector<pair<double, int> > l;

	l.push_back({q[0].first, q[0].second});
	for (int i = 1; i < q.size(); ++i) {
		if (fabs(q[i].first-l.back().first) <= EPS) l.back().second+=q[i].second;
		else l.push_back({q[i].first, q[i].second});
	}

	vector<int> presum(l.size());

	presum[0] = l[0].second;
	for (int i = 1; i < l.size(); ++i) presum[i] = presum[i-1] + l[i].second;
	
	int a = 0, b = 0;
	while (1) {
		int nxt = (b+1)%l.size();
		if (nxt==a) break;
		if (l[nxt].first > l[a].first + PI) break;
		b = nxt;
	}
	int suma=0, sumb=0;
	suma = sumFromTo(a,b,presum);
	if (fabs(l[b].first - l[a].first - PI) <= EPS) sumb = sumFromTo(b, a, presum);
	else sumb = sumFromTo(b+1, a, presum);

	best = max(best, max(w[i],0) + max(suma, sumb));
	for (++a; l[a].first < PI && a < l.size(); ++a) {
		while (1) {
			int nxt = (b+1)%l.size();
			if (nxt==a) break;
			if (!( (l[nxt].first > l[a-1].first + PI) && l[nxt].first <= l[a].first+PI) ) break;
			b = nxt;
		}
		suma = sumFromTo(a,b,presum);
		if (fabs(l[b].first - l[a].first - PI) <= EPS) sumb = sumFromTo(b, a, presum);
		else sumb = sumFromTo(b+1, a, presum);

		best = max(best, max(w[i],0) + max(suma, sumb));
	}
}


int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) scanf("%lf%lf%d", &p[i].x, &p[i].y, w+i);

	for (int i = 0; i < N; ++i) {
		vector<pair<double, int> > q;
		for (int j = 0; j < N; ++j) {
			if (i!=j) {
				double theta = angle(p[i], p[j]);
				q.push_back({theta, w[j]});
			}
		}
		sort(begin(q), end(q));
		solve(q, i);

		for (pair<double,int>& p : q) {
			if (p.first >= PI) p.first -= PI;
			else p.first += PI;
		}
		sort(begin(q), end(q));
		solve(q, i);
	}
	printf("%d\n", best);
}