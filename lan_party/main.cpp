#include <cstdio>
#include <algorithm>
#include <vector>
#define MAX_SZ 352
#define MAX_SQ 50000000
using namespace std;

struct square {
	int r, c, sz;
} sq[MAX_SQ];

int R, C, M, r, c, nsq;

vector<int> roots, tmp;

vector<int> adj[MAX_SQ];

int build(int p, int r, int c, int sz) {
	if (sz==0) return -1;
	adj[p].push_back(++nsq);
	sq[nsq] = {r, c, sz};
	int u = nsq;
	build(u, r, c, sz-1);
	build(u, r, c+1, sz-1);
	build(u, r+1, c, sz-1);
	build(u, r+1, c+1, sz-1);
	return u;
}

bool dfs(int x, int p) {
	if (sq[x].r <= r && r < sq[x].r + sq[x].sz && sq[x].c <= c && c < sq[x].c + sq[x].sz) {
		// cut it out
		return true;
	}

	for (int y : adj[x]) {
		
	}

	return false;
}

int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d%d%d", &R, &C, &M);
		
	for (int r = 1; r + min(R, C) - 1 <= R; ++r) {
		for (int c = 1; c + min(R, C) -1 <= C; ++c) {
			roots.push_back(build(0, r, c, min(R, C)));
		}
	}
		
	while (M--) {
		scanf("%d%d", &r, &c);
		for (auto x : roots) {
			dfs(x, 0);
		}
		if (roots.empty()) printf("0\n");
		else printf("%d\n", sq[roots[0]].sz);
	}
}

/*
	This does not work. You cannot update. Wait can you? No.

	You need to represent a state. How? 

	The most obvious way is to store a list of every existing square.

	Then for updates, if (r, c) is within the square, simply remove it.

	This is N^2 * N^3 because there are N^3 squares. 
	
	So you have an N^5 solution 

	Any other way to represent states? 

	Only store the maximum sized squares
	
	Then keep a list of squares
	For every update
		If every square in the list contains (r, c)
			Then update to next highest sizes. How?
			It works
		Otherwise remove all squares that contain (r, c)
*/