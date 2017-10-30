#include <cstdio>
#include <algorithm>
#define MAXN 20

using namespace std;
typedef pair<int, int> ii;

int N, M;
ii t[1<<(MAXN+1)]; // first is val, second is index

int main() {
// 	freopen("data.txt", "r", stdin);
	scanf("%d%d", &N, &M);
	for (int i = 0; i < (1<<N); ++i) {
		scanf("%d", &t[i + (1<<N)].first);
		t[i+(1<<N)].second = i;
	}
	for (int i = (1<<N)-1; i; --i) t[i] = max(t[i<<1], t[i<<1|1]);
	while (M--) {
		char op; scanf(" %c", &op);
		if (op=='W') {
			printf("%d\n", t[1].second+1);
		} else if (op=='S') {
			int i; scanf("%d", &i);
			--i;
			int h = 0;
			int x = i + (1<<N);
			while (x && t[x].second==i) {
				++h;
				x >>= 1;
			}
			printf("%d\n", h-1);
		} else {
			int i, S; scanf("%d%d", &i, &S);
			--i;
			t[i + (1<<N) ] = {S, i};
			int x = i + (1<<N);
			x >>= 1;
			while (x) {
				t[x] = max(t[x<<1], t[x<<1|1]);
				x >>= 1;
			}
		}
	}
}