#include <cstdio>
const int SIZE = 200005;
int P, Q, N, X, sz=1, x[SIZE];

int read() {
	int pnt = 0, pow = 1, q;
	for (int j = 0; j < P; ++j) {
		scanf("%d", &q);
		pnt += pow * q;
		pow *= Q;
	}
	return pnt;
}

int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d%d%d", &P, &Q, &N);
	for (int i = 0; i < P; ++i) sz *= Q;
	for (int i = 0; i < N; ++i) {
		int pnt = read();
		++x[pnt]; 
	}
	int d = 1, dimSize = 1;
	for (int dim = 0; dim < P; ++dim) {
		dimSize *= Q;
		for (int pnt = sz-1; pnt >= 0; --pnt) {
			if (pnt+d < sz && (pnt+d)/dimSize == pnt/dimSize) 
				x[pnt] += x[pnt+d];
		}
		d *= Q;
	}
	scanf("%d", &X);
	while (X--) {
		int pnt = read();
		printf("%d\n", x[pnt]);
	}
}