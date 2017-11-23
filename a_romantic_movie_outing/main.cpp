#include <cstdio>
const int MAXL = 1003, BIT_SIZE = 4*MAXL, INF = 1000000000;
int L, T, bit1[BIT_SIZE][BIT_SIZE], bit2[BIT_SIZE][BIT_SIZE], grid[BIT_SIZE][BIT_SIZE];

void update(int (&bit)[BIT_SIZE][BIT_SIZE], int x, int z, int v) {
	for (; x < BIT_SIZE; x += x&-x) 
		for (int y = z; y < BIT_SIZE; y += y&-y) bit[x][y] += v;
}

int sum(int (&bit)[BIT_SIZE][BIT_SIZE], int x, int z) {
	int res = 0;
	for (; x; x -= x&-x) 
		for (int y = z; y; y -= y&-y) res += bit[x][y];
	return res;
}

int pyramid(int r, int c) {
	int x = sum(bit1, r+c-1, r);
	int y = sum(bit2, BIT_SIZE-1, r);
	int z = sum(bit2, r-c+1000, r);
	return x-y+z;
}

int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d%d", &L, &T);
	while (T--) {
		char cmd; int r,c; scanf(" %c %d %d", &cmd, &r, &c);
		if (cmd=='E') {
			update(bit1, r+c-1, r, 1);
			update(bit2, r-c+1000, r, 1);
			if (r < BIT_SIZE) grid[r][c] = 1;
		} else if (cmd=='L') {
			update(bit1, r+c-1, r, -1);
			update(bit2, r-c+1000, r, -1);
			if (r < BIT_SIZE) grid[r][c] = 0;
		} else {
			if (grid[r][c] || grid[r][c+1]) printf("No\n");
			else printf("%d\n", pyramid(r,c)+pyramid(r, c+1));
		}
	}

	int b1 = INF, b2 = INF;

	for (int r = L+1; r <= L+1001; ++r) {
		for (int c = 1; c <= 1000; ++c) {
			if (!grid[r][c]) {
				int x = pyramid(r,c);
				if (x<=b1) {
					b2 = b1;
					b1 = x;
				} else if (x < b2) b2 = x;
			}
		}
	}
	printf("%d\n", b1+b2);
}
