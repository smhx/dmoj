/*input
0 0 3 3
1
4 3 2 4 2 4 1 3 1
*/
#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;
#define EPS 1e-9

struct point { 
	double x, y;
    point() { x = y = 0.0; }
    point(double _x, double _y) : x(_x), y(_y) {}
};


struct line { 
    double a, b, c; 
    line() : a(0.0), b(1.0), c(0.0) {}
    // line(double _a, double _b, double _c) : a(_a), b(_b), c(_c) {}
};

bool areParallel(line l1, line l2) { 
    return (fabs(l1.a-l2.a) < EPS) && (fabs(l1.b-l2.b) < EPS); 
}

void pointsToLine(point p1, point p2, line &l) {
    if (fabs(p1.x - p2.x) < EPS) { // vertical line is fine
        l.a = 1.0; l.b = 0.0; l.c = -p1.x; 
    } else { // default values
        l.a = -(double)(p1.y - p2.y) / (p1.x - p2.x);
        l.b = 1.0; // IMPORTANT: we fix the value of b to 1.0 
        l.c = -(double)(l.a * p1.x) - p1.y;
    }
}

bool areEqual(line l1, line l2) { 
    // also check coefficient c 
    return areParallel(l1 ,l2) && (fabs(l1.c - l2.c) < EPS); 
}

bool intersect(line l1, line l2, point &p) {
	if (areEqual(l1, l2)) {
		// printf("	from intersect returning true on equal\n");
		return true;
	}
    if (areParallel(l1, l2)) {
    	// printf("	from intersect returning false on parallel\n");
    	return false; 
    }
    p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
    if (fabs(l1.b) > EPS) p.y = -(l1.a * p.x + l1.c); 
    else p.y = -(l2.a * p.x + l2.c); 
    // printf("	from intersect returning true on default\n");

    return true; 
}

// double evaluate(line l, point p) {
// 	return l.a*p.x+l.b*p.y+l.c;
// }

int main() {

	point R, J; 
	line L;

	scanf("%lf%lf%lf%lf", &R.x, &R.y, &J.x, &J.y);

	pointsToLine(R, J, L);

	int N; scanf("%d", &N);
	int cnt = 0;
	while (N--) {

		bool blocks = false;

		int sz; scanf("%d", &sz);
		vector<point> pnts;

		for (int i = 0; i < sz; ++i) {
			double x, y; scanf("%lf%lf", &x, &y);
			pnts.push_back(point(x, y));
		}

		for (int i = 0; i < sz; ++i) {
			point p1 = pnts[i], p2 = pnts[(i+1)%sz], meet;
			// printf("p1 = (%lf, %lf), p2 = (%lf, %lf)\n", p1.x, p1.y, p2.x, p2.y);

			line l;
			pointsToLine(p1,p2,l);
			// printf("l: %lf x + %lf y + %lf = 0\n", l.a, l.b, l.c);
			bool b = intersect(l, L, meet);
			// printf("	meet = (%lf, %lf)\n", meet.x, meet.y);
			if (b) {
				if (
				  (	( (R.x <= meet.x && meet.x <= J.x) || (J.x <= meet.x && meet.x <= R.x) ) &&
					( (R.y <= meet.y && meet.y <= J.y) || (J.y <= meet.y && meet.y <= R.y) ) ) &&
				  (	( (p1.x <= meet.x && meet.x <= p2.x) || (p2.x <= meet.x && meet.x <= p2.x) ) &&
					( (p1.y <= meet.y && meet.y <= p2.y) || (p2.y <= meet.y && meet.y <= p1.y) ) )

				) {
					blocks = true;
					// printf("	BLOCK!!!\n");
				}
			}
		}
			
		if (blocks) ++cnt;
	}
	printf("%d\n", cnt);
}
