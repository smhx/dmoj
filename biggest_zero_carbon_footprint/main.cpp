#include <cstdio>
#include <algorithm>
typedef long long ll;
using namespace std;

const int MAX = 10004;
int n, m, t;
ll area = 0;

struct point{int x, y;} p[MAX];

bool cmpx(const point& p1, const point& p2) {return p1.x < p2.x;}
bool cmpy(const point& p1, const point& p2) {return p1.y < p2.y;}

int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d%d%d", &n, &m, &t);
	for (int i = 0; i < t; ++i) scanf("%d%d", &p[i].x, &p[i].y);	

	sort(p, p+t, cmpx);

	for (int i = 0; i < t; ++i) {
		int top = 0, bottom = m;
		for (int j = i + 1; j < t; ++j) {
			area = max(area, 1LL * (p[j].x-p[i].x) * (bottom-top));
			if (top < p[j].y && p[j].y < bottom) {
				if (p[j].y < p[i].y) top = p[j].y;
				else if (p[j].y > p[i].y) bottom = p[j].y;
				else {
					bottom=top=0;
					break;
				}
			}
		}
		area = max(area, 1LL * (n-p[i].x) * (bottom-top));
 	}
	
	sort(p, p+t, cmpy);

	for (int i = 0; i < t; ++i) {
		int left = 0, right = n;
		for (int j = i + 1; j < t; ++j) {
			area = max(area, 1LL * (p[j].y-p[i].y) * (right-left));
			if (left < p[j].x && p[j].x < right) {
				if (p[j].x < p[i].x) left = p[j].x;
				else if (p[j].x > p[i].x) right = p[j].x;
				else {
					right = left = 0;
					break;
				}
			}
		}
		area = max(area, 1LL * (m-p[i].y) * (right-left));
	}

 	for (int i = 0, r = n; i < t; ++i) {
 		area = max(area, 1LL * r * p[i].y);
 		if (p[i].x < r) r = p[i].x;
 	}
	
	printf("%lld\n", area);
}

/*
	Assume that you make the rectangle with bottom y > 0.

	So the bottom of your rectangle is (l, y) ... (r, y) inclusively

	Let's say that there is no tree t = (a, y) with l < a < r.

	Then you can just decrease y to y-1. 

	Therefore you can solve all positive y.

	You can apply the exact same argument to x and solve all positive x.

	The only other case is non positive x and y, which occurs only if the 

	bottom left corner is (0, 0).

*/

