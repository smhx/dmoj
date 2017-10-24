#include <cstdio>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <queue>
#define MAXN 2000005
using namespace std;

typedef pair<int, int> ii;

unordered_map<int, vector<ii> > row, col; // row[i] is everything in row i

vector<int> adj[MAXN];


int N, M, O, E, x[MAXN], y[MAXN], d[MAXN], visit[MAXN];

void insert(unordered_map<int, vector<ii> >& m, int k, int v, int i) {
	if (m.find(k)==m.end()) m[k]=vector<ii>();
	m[k].push_back(ii(v, i));
}

void graph(unordered_map<int, vector<ii> >& m) {
	// printf("GRAPHING\n");
	for (auto x : m) {
		sort(x.second.begin(), x.second.end());
		for (size_t i = 0; i+1 < x.second.size(); ++i) {
			adj[x.second[i].second].push_back(x.second[i+1].second);
			adj[x.second[i+1].second].push_back(x.second[i].second);
			// printf("connecting (%d, %d)\n", x.second[i].second, x.second[i+1].second);
		}
	}
}

int bfs() {
	queue<int> q;
	q.push(0);
	visit[0] = 1;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		// printf("u = %d\n", u);
		for (int v : adj[u]) {
			if (!visit[v]) {
				// printf("  v = %d\n", v);
				visit[v] = 1;
				d[v] = 1+d[u];
				if (v>O) {
					// reached an end point
					return d[v]-1;
				}
				q.push(v);
			}
		}
	}
	return -1;
}

int main() {
	// freopen("data.txt", "r", stdin);
	scanf("%d%d%d%d%d", &N, &M, &x[0], &y[0], &O);
	insert(row, y[0], x[0], 0);
	insert(col, x[0], y[0], 0);
	for (int i = 1; i <= O; ++i) {
		scanf("%d%d", x+i, y+i);
		insert(row, y[i], x[i], i);
		insert(col, x[i], y[i], i);
	}
	scanf("%d", &E);
	for (int i = O+1; i <= O+E; ++i) {
		scanf("%d%d", x+i, y+i);
		insert(row, y[i], x[i], i);
		insert(col, x[i], y[i], i);
	}
	graph(row);
	graph(col);
	printf("%d\n", bfs());
}