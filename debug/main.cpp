#include <bits/stdc++.h>
using namespace std;

const int SIZE = 305;

int R, C, A[SIZE][SIZE];

int main() {
	scanf("%d%d", &R, &C);
	for (int r = 0; r < R; ++r) {
		for (int c = 0; c < C; ++c) {
			scanf("%d", &A[r][c]);
		}
	}


}


/*

	(l, b) and (l+sz-1, b+sz-1)

	then a[l+i][b+j] = a[l+sz-i-1][b+sz-j-1].


*/