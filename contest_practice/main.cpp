#include <cstdio>
const int SIZE = 200005;
int P, Q, N, X, sz=1, x[SIZE];

#ifdef DMOJ
#define getchar() (*_pbuf ? *_pbuf++ : (_buf[fread_unlocked(_pbuf = _buf, 1, 1048576, stdin)] = 0, *_pbuf++))
char _buf[1048577], *_pbuf = _buf;
#endif

int read_int() {
	int c, o = 0;
	while ((c = getchar()) < '0');
	do {o = (o<<3)+(o<<1) + (c - '0');} while ((c = getchar()) >= '0');
	return o;
}

int read() {
	int pnt = 0, pow = 1;
	for (int j = 0; j < P; ++j) {
		pnt += pow * read_int();
		pow *= Q;
	}
	return pnt;
}

int main() {
	freopen("data.txt", "r", stdin);
	P = read_int(); Q = read_int(); N = read_int();
	for (int i = 0; i < P; ++i) sz *= Q;
	for (int i = 0; i < N; ++i) ++x[read()]; 
	int d = 1, dimSize = 1;
	for (int dim = 0; dim < P; ++dim) {
		dimSize *= Q;
		for (int pnt = sz-1; pnt >= 0; --pnt) 
			if (pnt+d < sz && (pnt+d)/dimSize == pnt/dimSize) 
				x[pnt] += x[pnt+d];
		d *= Q;
	}
	X = read_int();
	while (X--) printf("%d\n", x[read()]);
}