#include <bits/stdc++.h>
using namespace std;

int n, t[105][105], id;

int identity() {
	for (int i = 1; i <= n; ++i) {
		bool works = true;
		for (int x = 1; x <= n && works; ++x) if (t[i][x] != x || t[x][i] != x) works = false;
		if (works) return i;
	}
	return -1;
}
bool inverse() {
	for (int x = 1; x <= n; ++x) {
		bool has = false;
		for (int y = 1; y <= n && !has; ++y) {
			if (t[x][y]==id && t[y][x] == id) has = true;
		}
		if (!has) return false;
	}
	return true;
}
bool assoc() {
	for (int x = 1; x <= n; ++x) {
		for (int y = 1; y <= n; ++y) {
			for (int z = 1; z <= n; ++z) {
				if (t[x][t[y][z]] != t[t[x][y]][z]) return false;
			}
		}
	}
	return true;
}

int main() {
	// freopen("data.txt", "r", stdin);
	while (1) {
		scanf("%d", &n);
		if (n==0) return 0;
		for (int i = 1; i <= n; ++i) 
			for (int j = 1; j <= n; ++j) scanf("%d", &t[i][j]);

		id = identity();
		if (id==-1) printf("no\n");
		else if (!inverse()) printf("no\n");
		else if (!assoc()) printf("no\n");
		else printf("yes\n");
	}
}