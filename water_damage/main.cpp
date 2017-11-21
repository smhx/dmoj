#include <iostream>
#include <cstring>
using namespace std;

const char EMPTY = '.', SPECIAL = 'A', FILLED = '#', SPECIAL_FILLED = 'B';

const int SIZE = 11;
int T = 5, W, R, C;

char map[SIZE][SIZE];

int main() {
	freopen("data.txt", "r", stdin);
	while (T--) {
		scanf("%d%d%d", &W, &C, &R);
		for (int r = 0; r < R; ++r) {
			scanf(" %s", map[r]);
		}

		while (W--) {
			int cr=0, cc=0;
			if (map[cr][cc] == FILLED || map[cr][cc]==SPECIAL_FILLED) break;
			while (1) {

				if (cr+1 < R && (map[cr+1][cc]==EMPTY || map[cr+1][cc]==SPECIAL)) {
					// You can go down
					++cr;
				} else if (cc +1 < C && (map[cr][cc+1]==EMPTY || map[cr][cc+1]==SPECIAL)) {
					// Can't go down but can go right
					++cc;
				} else {
					// You're stuck
					if (map[cr][cc]==EMPTY) map[cr][cc] = FILLED;
					else if (map[cr][cc] == SPECIAL) map[cr][cc] = SPECIAL_FILLED;
					else printf("ERROR!!!!\n");

					break;
				}

			}
		}

		int cnt = 0;
		for (int r = 0; r < R; ++r) {
			for (int c = 0; c < C; ++c) {
				if (map[r][c]==SPECIAL_FILLED) ++cnt;
			}
		}
		printf("%d\n", cnt);
	}
}