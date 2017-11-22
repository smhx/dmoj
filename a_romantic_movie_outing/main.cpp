#include <cstdio>
const int MAXL = 1003, BIT_SIZE = 2*MAXL;
int L, T;

int bit1[BIT_SIZE][BIT_SIZE], bit2[BIT_SIZE][BIT_SIZE];
void update(int (&bit)[BIT_SIZE][BIT_SIZE], int x, int y, int v) {
	for (; x < BIT_SIZE; x += x&-x) {
		for (; y < BIT_SIZE; y += y&-y) {
			bit[x][y] += v;
		}
	}
}

int sum(int (&bit)[BIT_SIZE][BIT_SIZE], int x, int y) {
	int res = 0;
	for (; x; x -= x&-x) {
		for (; y; y -= y&-y) {
			res += bit[x][y];
		}
	}
	return res;
}

int val(int r, int c) {

}
int main() {
	scanf("%d%d", &L, &T);
	while (T--) {
		char cmd; int r,c; scanf(" %c %d %d", &cmd, &r, &c);
		if (cmd=='E') {
			update(bit1, r+c-1, c, 1);
			update(bit2, r-c+L, c, 1);
		} else if (cmd=='L') {
			update(bit1, r+c-1, c, -1);
			update(bit2, r-c+L, c, -1);
		} else {
			if (val(r,c)) {
				printf("No\n");
			}
		}
	}
}
