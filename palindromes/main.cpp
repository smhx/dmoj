#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXSTR = 3e5+5, ALPHA_SIZE = 30;
int s[MAXSTR], len[MAXSTR], sufflink[MAXSTR], ch[MAXSTR][ALPHA_SIZE], occ[MAXSTR];
int nn = 2, suffx = 0, nc = 0; 
void init() {
	memset(ch, -1, sizeof ch);
	memset(occ, 0, sizeof occ);
	len[0] = -1;
	sufflink[0] = 0;
	len[1] = 0;
	sufflink[1] = 0;
	nn = 2;
	suffx = 0;
	nc = 0;
}
int getlink(int u) {
	while (u) {
		if (nc-len[u]-2 >= 0 && s[nc-len[u]-2] == s[nc-1]) break;
		u = sufflink[u];
	}
	return u;
}
void addchar(int c) {
	s[nc++] = c;
	suffx = getlink(suffx);
	if (ch[suffx][c] == -1) {
		len[nn] = len[suffx]+2;
		ch[suffx][c] = nn;
		sufflink[nn] = len[nn] != 1 ? ch[getlink(sufflink[suffx])][c] : 1;
		++nn;
	}
	suffx = ch[suffx][c];
	++occ[suffx];
}
long long maxoccv() {
	long long ans = 0;
	for (int i = nn-1; i >= 2; --i) {
		occ[sufflink[i]] += occ[i];
		ans = max(ans, 1LL * occ[i] * len[i]);
		// if (1LL * occ[i] * len[i] > ans) ans = 1LL * occ[i] * len[i];
	}
	return ans;
}
int main() {
	init();
	char in;
	while ((in=getchar()) >= 'a') addchar(in-'a'+2);
	printf("%lld\n", maxoccv());
}