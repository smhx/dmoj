#include <cstdio>
#include <algorithm>
typedef long long ll;

const int MAXN = 500005, LOG = 22;

char op;
int N, G;
ll W, p, c, pic[MAXN], cuteness[MAXN], width[MAXN];

int main() {
// 	freopen("data.txt", "r", stdin);
	scanf("%d%lld", &N, &W);
	while (N--) {
		scanf(" %c", &op);
		if (op=='D') {
			width[G] = cuteness[G] = pic[G] = 0;
			--G;
		} else {
			scanf("%lld%lld", &p, &c);
			++G;
			width[G] = width[G-1]+p;
			cuteness[G]=cuteness[G-1]+c;
			if (p > W) {
				pic[G] = pic[G-1];
			} else {
				int H = G;
				for (int k = LOG-1; k >= 0; --k) 
					if (H-(1<<k)>0) 
						if (width[G]-width[H-(1<<k)-1] <= W) 
							H = H-(1<<k);
				pic[G] = std::max(cuteness[G]-cuteness[H-1], pic[G-1]);
			}
			printf("%lld\n", pic[G]);
		}
	}
}