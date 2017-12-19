#include <cstdio>
#include <algorithm>
#include <functional>
using namespace std;
const int SIZE = 1005, CIRC = 1e6, LOG = 22;

int H, K, h[SIZE], cw[SIZE][SIZE], ccw[SIZE][SIZE];

bool works(int x, const int addr[]) {
	int i = 0, req = 0;
	while (i < H) {
		++req;
		int cur = addr[i] + x;
		while (i < H && cur >= addr[i]-x) ++i;
	}
	return req <= K;
}

int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d", &H);
	for (int i = 0; i < H; ++i) {
		scanf("%d", &h[i]);
		for (int j = 0; j < H; ++j) cw[j][i] = h[i];
	}
	
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < H; ++j) cw[i][j] = (cw[i][j]-h[i]+CIRC)%CIRC;
		sort(cw[i], cw[i]+H);
		for (int j = 0; j < H; ++j) ccw[i][j] = (CIRC-cw[i][j])%CIRC;
		sort(ccw[i], ccw[i]+H);
	}

	scanf("%d", &K);
	
	if (H <= K) {
		printf("0\n");
		return 0;
	}

	int x = 0;
	for (int k = LOG-1; k >= 0; --k) {
		if (x + (1<<k) <= CIRC) {
			bool good = false;
			for (int i = 0; i < H && !good; ++i) 
				good |= works(x+(1<<k), cw[i]) | works(x+(1<<k), ccw[i]);
			if (!good) x += 1<<k;
		}
	}
	++x;
	printf("%d\n", x);
}