#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 300005;
int N;
vector<int> adj[MAXN];

int main() {
	scanf("%d", &N);
	for (int i = 1, a,b; i <= N; ++i) {
		scanf("%d%d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
}