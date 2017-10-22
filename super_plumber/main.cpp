#include <cstdio>
#include <algorithm>
int R, C, grid[105][105], mem[105][105][105];

int dx[3] = {0, 1, 0};
int dy[3] = {1, 0, -1};

inline bool valid(int r, int c) {
    return 1 <= r && r <= R && 1 <= c && c <= C;
}

int dp(int r, int c, int prer) {
    // printf("(%d, %d, %d)\n", r, c, prer);
    if (mem[r][c][prer] != -2) return mem[r][c][prer];
    if (grid[r][c]==-1) return mem[r][c][prer]=-1;
    if (r==R && c==C) return mem[r][c][prer]=grid[r][c];
    int M = -1;
    for (int i = 0; i < 3; ++i) {
        int newr = r+dy[i], newc = c+dx[i];
        if (newr==prer) continue;
        if (valid(newr, newc)) {
            if (dp(newr, newc, newr != r ? r : -1) != -1)
                M = std::max(M, grid[r][c] + dp(newr, newc, newr != r ? r : -1));
        }
    }
    return mem[r][c][prer] = M;
}

int main() {
    freopen("data.txt", "r", stdin);
	while (1) {
        scanf("%d%d", &R, &C);
        if (!R && !C) return 0;
        for (int i = 0; i < 105; ++i) 
            for (int j = 0; j < 105; ++j) 
                for (int k = 0; k < 105; ++k) 
                    mem[i][j][k] = -2;
               
        for (int r = 1; r <= R; ++r) {
            for (int c = 1; c <= C; ++c) {
                char ch; scanf(" %c", &ch);
                if (ch=='*') grid[r][c] = -1;
                else if (ch != '.') grid[r][c]=ch-'0';
            }
        }
        // dp[r][c] := max money starting at (r, c). But this relies on both r, c+1 and r, c-1.
        // which creates loops. dp[r][c][pre]

        printf("%d\n", dp(R, 1, -1));
    }
	
}

/*
    Can you think of a nicer way to solve this dp problem?

    What you're doing right now is there are N^3 states. You're going through each.

    In reality, there are not so many states. Let dp[r][c][i] be max when you go the ith route

    Then i = 0 is up. i = 1 is side. i = 2 is down.

    dp[r][c][0] depends on r-1 and c
    dp[r][c][1] depends on r and c+1
    dp[r][c][2] depends on r+1 and c

*/