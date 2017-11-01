#include <cstdio>
#include <vector>
#define SIZE 100000008
using namespace std;


int N, Q, v, l[11], a[11], bit[SIZE], val[SIZE];

/*
	a[n][m]

	a[i][j] = a[i] + j = a + m * i + j

	bit[dimension1][dimension2]...[dimensionN]

	bi[a[1]][a[2]][a[3]]...[a[N]] = bit + l[N] * l[N-1] * ... * l[2] * a[1]

	
	bit[X][Y]

	bit[x][y]

	for x
		for y
			for x
				update bit[x][y][z] = bit[x][y]+z
									= bit[x] + Z * y + z
									= bit + Y*Z * x + Z * y + z


*/


void update(int d, int idx) {
	// You've already done 1, ..., d-1. 
	
	for (int x = a[d]; x <= l[d]; x += x&-x) {
		if (d < N) {
			update(d+1, (idx+x)*l[d+1] );
		} else {
			bit[idx+x] += v;
		}
	}
}

int query(int d, int idx) {
	int res = 0;
	printf("d = %d, idx = %d\n", d, idx);
	for (int x = a[d]; x ; x -= x&-x) {
		printf("	x = %d\n", x);
		if (d < N) {
			res += query(d+1, (idx+x)*l[d+1]);
		} else {
			res += bit[idx+x];
			printf("	inc by bit[idx+x=%d]=%d\n", idx+x, bit[idx+x]);
		}
	}
	return res;
}

int at() {
	int j = 0, p = 1;
	for (int d = N; d >= 1; --d) {
		j += p * a[d];
		p *= l[j];
	}
	return j;
}

int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d%d", &N, &Q);
	for (int d = 1; d <= N; ++d) {
		scanf("%d", l+d);
	}

	while (Q--) {
		int op; scanf(" %d", &op);
		if (op==1) {
			for (int i = 1; i <= N; ++i) scanf("%d", a+i);
			scanf("%d", &v);
			int j = at();
			int w=v;
			v -= val[j];
			val[j] = w;
			update(1, 0);
		} else {

			for (int i = 1; i <= N; ++i) {
				scanf("%d", a+i);
				--a[i];
			}

			int res = -query(1, 0);

			printf("1st res is %d\n", res);

			for (int i = 1; i <= N; ++i) {
				scanf("%d", a+i);
			}

			int res2 = query(1, 0);
			printf("second res is %d\n", res2);

			res += res2;
			printf("%d\n", res);
		}
	}
}
