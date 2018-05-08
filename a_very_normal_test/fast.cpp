#include <bits/stdc++.h>

int n, ans[305], A[305][305];

char buff[10];

void rref() {
	int R = n, C = n+1;
	for (int c = 0, r = 0; c < C; ++c) {
		int p = r;
		while (p < R && !A[p][c]) ++p;
		if (p < R) {
			std::swap(A[r], A[p]);
			for (int q = 0; q < R; ++q) {
				if (q != r && A[q][c]) 
					for (int d = c; d < C; ++d) A[q][d]^=A[r][d];
			}
			++r;
		}
	}
}

bool solve() {
	rref();
	for (int i = 0, j = 0; i < n; ++i) {
		while (j <= n && !A[i][j]) ++j;
		if (j < n) ans[j] = A[i][n];
		else if (j == n) return false;
		else break;
	}
	return true;
}

void input() {
	int i, v1, v2;
	scanf("%d", &n);
	for (i = 0; i < n; ++i) {
		scanf(" %s", buff);
		A[i][i] = A[i][n] = 1;
		if (buff[0] == '!') {
			sscanf(buff, "!%d", &v1);
			A[i][v1-1] ^= 1;
		} else {
			sscanf(buff, "%d==%d", &v1, &v2);
			A[i][v1-1] ^= 1;
			A[i][v2-1] ^= 1;
		}
	}
}

int main() {
	input();
	if (!solve()) return !printf("No perfect solution found\n");
	for (int i = 0; i < n; ++i) {
		if (ans[i]) printf("true\n");
		else printf("false\n");
	}
}