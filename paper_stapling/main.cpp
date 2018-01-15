/*input
6 1
1 5
*/
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <limits>
using namespace std;

#define x first
#define y second

typedef long double ld;

typedef pair<ld,ld> point;

int main() {
	point p1, p2;
	cin >> p1.x >> p1.y >> p2.x >> p2.y;

	if (p1 > p2) swap(p1, p2);
	ld area = numeric_limits<ld>::max();

	if (p2.y <= 2*p1.y - p1.y/p1.x * p2.x) area = min(area, 2*p1.x*p1.y);
	if (p1.y <= 2*p2.y - p2.y/p2.x * p1.x) area = min(area, 2*p2.x*p2.y);

	if (p1.x < p2.x && p1.y > p2.y) {
		ld dy_top = p1.x * (p1.y-p2.y)/(p2.x-p1.x);
		ld dx_bot = p2.y*(p2.x-p1.x)/(p1.y-p2.y);
		ld base = dx_bot + p2.x;
		ld height = dy_top+p1.y;
		area = min(area, base*height/2.0);
	} 
	cout.precision(9);
	cout << fixed << area << endl;
}