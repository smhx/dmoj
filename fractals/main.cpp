#include <cstdio>
#include <utility>

#define x first
#define y second

typedef std::pair<int,int> ii;

int grid[100][100];

inline ii add(ii a, ii b){return ii(a.x+b.x, a.y+b.y);}
inline ii add(ii a, ii b, ii c) {return add(add(a,b),c);}
inline ii multiply(ii a, int c) {return ii(a.x*c, a.y*c);}
inline ii neg(ii a) {return ii(-a.x, -a.y);}

void build(ii zero, ii par, ii perp, int n, int w) {
	if (n==0) {
		ii v = zero;
		for (int i = 0; i <= w; ++i) {
			grid[v.x][v.y] = 1;
			v = add(v, par);
		}
	} else {
		build(zero, par, perp, n-1, w/3);
		build(add(zero, multiply(par, w/3)), perp, neg(par), n-1, w/3);
		build(add(zero, multiply(par, w/3), multiply(perp, w/3)), par, perp, n-1, w/3);
		build(add(zero, multiply(par, 2*w/3)), perp, par, n-1, w/3);
		build(add(zero, multiply(par, 2*w/3)), par, perp, n-1, w/3);
	}
}

int main() {
	// freopen("data.txt", "r", stdin);
	int n, w, x; scanf("%d%d%d", &n, &w, &x);
	build(ii(0, 1), ii(1, 0), ii(0, 1), n, w);
	for (int y = 0; y <= w; ++y) if (grid[x][y]) printf("%d ", y);
	printf("\n");
}

