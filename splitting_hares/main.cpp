#include <cstdio>
#include <algorithm>
#include <vector>
#include <deque>
#include <cmath>

using namespace std;
const int MAXN = 4003;
const double PI = 3.141592653589793, EPS = 1e-6;


struct bunny {
	double x, y;
	int g;
} p[MAXN];

typedef pair<double, int> pdi;

int N, M =0, T=0, sum[MAXN];

double ang(bunny to, bunny from) {
	// angle with x axis
	if (abs(to.x-from.x) <= EPS) {
		return to.y > from.y ? PI/2.0 : 1.5*PI;
	} 
	if (to.x > from.x) {
		double tangent = (to.y-from.y) / (to.x-from.x);
		double a = atan(tangent);
		if (a<0) a+=2*PI;
		return a;
	} 
	double tangent = (to.y-from.y) / (from.x-to.x);
	double a = atan(tangent);
	a = PI-a;
	return a;
}

inline double cwrot(double a1, double a2) {
	return a2-a1 >= 0 ? a2-a1 : a2-a1+2*PI;
}

int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		scanf("%lf%lf%d", &p[i].x, &p[i].y, &p[i].g);
		T+=p[i].g;
	}
	printf("T = %d\n", T);
	for (int i = 0; i < N; ++i) {
		printf("i = %d, point %d (%lf, %lf)\n",i, p[i].g, p[i].x, p[i].y);
		vector<pdi> v;
		for (int j = 0; j < N; ++j) {
			if (j!=i) {
				double angle = ang(p[j], p[i]);
				v.push_back({angle, j});
			}	
		}
		sort(v.begin(), v.end());

		for (int j = 0; j < v.size(); ++j) {
			printf("	j=%d, point %d, angle %lf\n", j, p[v[j].second].g, v[j].first * 180.0 / PI);
		}
	

		deque<int> dq;
		dq.push_back(0);

		int s = p[i].g + p[v[0].second].g;
		for (int j = 1; j < v.size(); ++j) {
			if (v[j].first - v[0].first > PI) break;
			dq.push_front(j);
			s += p[v[j].second].g;
		}
		printf("	s = %d, dq.size()=%lu\n", s, dq.size());
		M = max(M, s);

		for (int j = 1; j < v.size(); ++j) {
			printf("  j = %d\n", j);
			for (int k = dq.front()+1; cwrot(v[(dq.back()+1)%v.size()].first,v[k].first) <= PI+EPS; k = (k+1) % v.size()) {
				s += p[v[k].second].g;
				printf("	adding k=%d\n", k);
				dq.push_front(k);
				if (k==dq.back()) break;
			}
			s -= p[v[j-1].second].g;
			dq.pop_back();

			printf("	s = %d, front=%d, back=%d, OTHER = %d\n", s, p[v[dq.front()].second].g, p[v[dq.back()].second].g,T-s + p[i].g + p[v[dq.back()].second].g );

			M = max(M, s);
			M = max(M, T-s + p[i].g + p[v[dq.back()].second].g);
		}

		printf("M is now %d\n", M);

	}
	printf("%d\n", M);
}
