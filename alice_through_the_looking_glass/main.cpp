#include <cstdio>

int pow5[14];

bool solve(int m, int x, int y) {
	if (m==1) {
		if (y==0) return 1 <= x && x <= 3;
		else if (y==1) return x==2;
		return false;
	}

	int rx = x/pow5[m-1], ry = y/pow5[m-1];

	// printf("pow = %d, rx = %d, ry = %d\n", pow5[m-1], rx, ry);

	if (ry==0 && 1 <= rx && rx <= 3) return true;
	if (ry==1 && rx == 2) return true;
	if (ry==2 && rx==2) {
		y -= 2 * pow5[m-1];
		x %= pow5[m-1];
		return solve(m-1, x, y);
	}
	if (ry == 1 && (rx==1 || rx==3)) {
		y -= pow5[m-1];
		x %= pow5[m-1];
		return solve(m-1, x, y);
	}

	return false;
}

int main() {
	freopen("data.txt", "r", stdin);
	pow5[0] = 1;
	for (int i = 1; i < 14; ++i) {
		pow5[i]= 5*pow5[i-1];
	}

	int T;
	scanf("%d", &T);
	while (T--) {
		int m, x, y;
		scanf("%d%d%d", &m, &x, &y);
		bool filled = solve(m, x, y);
		if (filled) printf("crystal\n");
		else printf("empty\n");
	}
}