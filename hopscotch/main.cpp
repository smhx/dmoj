#include <cstdio>
#include <cstring>
#include <algorithm>
#ifdef DMOJ
#define getchar() (*_pbuf ? *_pbuf++ : (_buf[fread_unlocked(_pbuf = _buf, 1, 1048576, stdin)] = 0, *_pbuf++))
char _buf[1048577], *_pbuf = _buf;
#endif
int readint() {
	int c, o = 0;
	while ((c = getchar()) < '0');
	do o = (o<<3)+(o<<1) + (c - '0'); while ((c = getchar()) >= '0');
	return o;
}

const int MAXN=205005, END = 300005;

int N, Q, SQRT=0, nxt[MAXN], block_nxt[MAXN], pre[MAXN], block_sz[MAXN];


void update_block(int blck, int hi) {

	if (hi==END) hi = blck*SQRT + SQRT - 1;

	for (int i = hi; i >= blck*SQRT; --i) {
		if (nxt[i] / SQRT != i / SQRT) {
			block_nxt[i] = nxt[i];
			block_sz[i] = 1;
		} else {
			block_nxt[i] = block_nxt[nxt[i]];
			block_sz[i] = 1+block_sz[nxt[i]];
		}
	}
}

int main() {
	freopen("data.txt", "r", stdin);
	N = readint();

	for (; SQRT*SQRT < N; ++SQRT); // Use actual square root

	for (int i = 0, K; i < N; ++i) {
		K = readint();
		nxt[i] = i+K < N ? i+K : END;
	}
	for (int i = 0; i < SQRT; ++i) update_block(i, END);
	Q = readint();
	while (Q--) {
		int cmd, x; cmd = readint(); x = readint();

		if (cmd==1) {
			int cnt = 0;
			for (; x != END; x = block_nxt[x]) cnt += block_sz[x];
			printf("%d\n", cnt);
		} else {
			int v; v = readint();
			nxt[x] = x+v < N ? x+v : END;
			update_block(x / SQRT, x);
		}
	}
}