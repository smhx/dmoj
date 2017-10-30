#include <cstdio>
#include <cmath>
#define MAXN 10004
#define EPS 1e-6
struct vec { double x, y; };

vec scale(vec v, double s) { return {v.x * s, v.y * s}; }

double dot(vec a, vec b) { return (a.x * b.x + a.y * b.y); } 
 
vec a[MAXN], v[MAXN];

int main() {
	// freopen("data.txt", "r", stdin);
	int N; double R;
	scanf("%d%lf", &N, &R);
	for (int i = 1; i <= N; ++i) {
		double speed;
		vec end;
		scanf("%lf%lf%lf%lf%lf", &a[i].x, &a[i].y, &end.x, &end.y, &speed);
		vec delta = {end.x-a[i].x, end.y-a[i].y};
		v[i] = scale(delta, speed/sqrt(dot(delta, delta)) );
	}

	for (int i = 2; i <= N; ++i) {

		vec da = {a[1].x-a[i].x, a[1].y-a[i].y};
		vec dv = {v[1].x-v[i].x, v[1].y-v[i].y};
        // difference is da + dv t. So diff ^ 2 is da * da + 2*da*dv*t^2+dv*dv*t^2 

		double A = dot(dv, dv);
		double B = 2.0 * dot(da, dv);
		double C = dot(da, da); // subtract R*R. quadratic continuous so should work

		if (fabs(A) < EPS) {
			if (C <= R*R) {
				printf("%d\n", i);
			}
		} else {
			// quadratic
			double T = -B / (2.0 * A);
			if (T >= 0) {
				if (A*T*T+B*T+C <= R*R){
					printf("%d\n", i);
				}
			} else {
				if (C <= R*R) {
					printf("%d\n",i);
				}
			}

		}
		
	}
}