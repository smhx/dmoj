#include <cstdio>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <cstring>
using namespace std;
typedef long long ll;
// state is a long long
const int INF = 1000000000;
int n, tmp[10];
unordered_map<ll,int> dist;
int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d", &n);
	while(n!=0){
		ll src=0LL, end=0LL;
		dist.clear();
		for (int i = 0; i < n; ++i) {
			int a; scanf("%d", &a);
			--a;
			src |= (1LL << (i*n + a));
			end |= (1LL << (i*n + i));
		}

		queue<ll> q;
		q.push(src);
		dist[src]=0;
		while (!q.empty()) {
			ll u = q.front(); q.pop();
			int d = dist[u];
			for (int i = 0; i < n; ++i) tmp[i] = INF;
			for (int box = 0; box < n; ++box) {
				for (int i = 0; i < n; ++i) {
					if (u&(1LL << (box*n+i))) {
						tmp[box] = i;
						break;
					}
				}
			}

			for (int i = 0; i < n; ++i) {
				if (tmp[i]!=INF) {
					if (i-1 >= 0) {
						if (tmp[i] < tmp[i-1]) {
							ll v = u;
							v ^= (1LL << (i*n + tmp[i]));
							v ^= (1LL << ((i-1)*n + tmp[i]));
							if (dist.find(v)==dist.end()) {
								dist[v] = 1 + d;
								q.push(v);
							}
						}
					}
					if (i+1 < n) {
						if (tmp[i] < tmp[i+1]) {
							ll v = u;
							v ^= (1LL << (i*n + tmp[i]));
							v ^= (1LL << ((i+1)*n + tmp[i]));
							if (dist.find(v)==dist.end()) {
								dist[v] = 1 + d;
								q.push(v);
							}
						}
					}
				}
			}
		}

		if (dist.find(end)==dist.end()) {
			printf("IMPOSSIBLE\n");
		} else {
			printf("%d\n", dist[end]);
		}
		scanf("%d", &n);
	}
}