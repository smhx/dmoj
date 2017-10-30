#include <cstdio>
#include <unordered_map>
#include <queue>
#define INF 1000000000
#define MAX 33554432
using namespace std;
int K, L;
unordered_map<int, int> d;

void transform(int& X) {
	int cnt = 0;
	for (int j = 0; j <= K; ++j) {
		if ( X & (1<<j) ) ++cnt;
		else {
			if (cnt>=4) 
				for (int k = 1; k <= cnt; ++k) X^=(1<<(j-k));
			cnt = 0;
		}
	}
}

int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d", &K);
	for (int i = 0; i < K; ++i) {
		int l; scanf("%d", &l);
		L |= l << i;
	}
	queue<int> q;
	q.push(L);
	d[L] = 0;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		if (u==0) break;
		for (int i = 0; i < K; ++i) {
			if ( (u&(1<<i))==0 ) {
				int x = u|(1<<i);
				transform(x);
				if (d.find(x)==d.end()) {
					d[x] = 1 + d[u];
					q.push(x);
				}
			}
		}
	}
	printf("%d\n", d[0]);
}