#include <cstdio>
#include <stack>
#include <cstring>
using namespace std;

typedef pair<int, int> point;

const int MAX = 2003, INF=0x3f3f3f3f, NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3;

int N, M, ice[MAX][MAX], lft[MAX], rt[MAX], top[MAX], btm[MAX];

stack<point> s;
int main() {
// 	freopen("data.txt", "r", stdin);
	scanf("%d%d", &N, &M);

	memset(rt, -1, sizeof rt);
	memset(btm, -1, sizeof btm);
	memset(lft, 0x3f, sizeof lft);
	memset(top, 0x3f, sizeof top);

	for (int r = 0; r < N; ++r) {
		for (int c = 0; c < M; ++c) {
			char in;
			scanf(" %c", &in);
			if (in=='.') ice[r][c] = -1;
			else {
				lft[r] = min(lft[r], c);
				rt[r] = max(rt[r], c);
				top[c] = min(top[c], r);
				btm[c] = max(btm[c], r);

				if (in=='N') ice[r][c] = NORTH;
				else if (in=='E') ice[r][c] = EAST;
				else if (in=='S') ice[r][c] = SOUTH;
				else if (in=='W') ice[r][c] = WEST;
			}
		}
	}


	for (int i = 0; i < N; ++i) {
		if (lft[i]!=INF && ice[i][lft[i]]==WEST) s.emplace(i, lft[i]);
		if (rt[i] != -1 && ice[i][rt[i]]==EAST) s.emplace(i, rt[i]);
	}

	for (int j = 0; j < M; ++j) {
		if (top[j]!=INF && ice[top[j]][j]==NORTH) s.emplace(top[j], j);
		if (btm[j]!=-1 && ice[btm[j]][j]==SOUTH) s.emplace(btm[j], j);
	}

	while (!s.empty()) {
		point p = s.top(); s.pop();
		int r = p.first, c = p.second;
		if (ice[r][c]==-1) continue;
		printf("(%d,%d)\n", r, c);
		ice[r][c] = -1;

		for (;lft[r]<M && ice[r][lft[r]]==-1; ++lft[r]);
		for (;rt[r]>=0 && ice[r][rt[r]]==-1; --rt[r]);
		for (;top[c]<N && ice[top[c]][c]==-1; ++top[c]);
		for (;btm[c]>=0 && ice[btm[c]][c]==-1; --btm[c]);

		if (lft[r] < M && ice[r][lft[r]]==WEST) s.emplace(r, lft[r]);
		if (rt[r] >= 0 && ice[r][rt[r]]==EAST) s.emplace(r, rt[r]);
		if (top[c] < N && ice[top[c]][c]==NORTH) s.emplace(top[c], c);
		if (btm[c] >= 0 && ice[btm[c]][c]==SOUTH) s.emplace(btm[c],c);
	}

}