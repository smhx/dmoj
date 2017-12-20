#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int SIZE =1005, LOG = 12;
int K, M, N, empty[SIZE], st[SIZE][LOG];
int A[SIZE][SIZE]; // true if free

void build() { // correct
	for (int i = 1; i <= M; ++i) st[i][0] = empty[i];
	for (int k = 1; k < LOG; ++k) 
		for (int i = 1; i + (1<<k) - 1 <= M; ++i) 
			st[i][k] = min(st[i][k-1], st[i+(1<<(k-1))][k-1]);
}

int main() { 
	// freopen("data.txt", "r", stdin);
	scanf("%d", &K);
	while (K--) {
		memset(empty, 0, sizeof empty);
		scanf(" %d %d", &M, &N); // M num rows, N num cols
		for (int i = 1; i <= M; ++i) {
			for (int j = 1; j <= N; ++j) {
				char c; scanf(" %c", &c);
				A[i][j] = c=='R';
			}
		}
		int maxarea = 0;
		for (int c = 1; c <= N; ++c) {
			for (int r = 1; r <= M; ++r) {
				if (A[r][c]) empty[r]=0;
				else ++empty[r];
			}
			build();
			for (int r = 1; r <= M; ++r) {
				int left=r, right = r;
				for (int k = LOG-1; k>=0; --k) 
					if (right + (1<<k) <= M && st[right+1][k] >= empty[r]) right += 1<<k;
				for (int k = LOG-1; k>=0; --k) 
					if (left - (1<<k) > 0 && st[left-(1<<k)][k] >= empty[r]) left -= 1<<k;
 				maxarea = max(maxarea, (right-left+1)*empty[r]);
			}
		}
		printf("%d\n", 3*maxarea);
	}
}