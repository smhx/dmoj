#include <cstdio>
int T, N, A[60][60], clow[60], chigh[60], rlow[60], rhigh[60];
int main() {
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t) {
        scanf("%d", &N);
        for (int i = 0; i < N; ++i){
            for (int j = 0; j < N; ++j) {
                char c; scanf(" %c", &c);
                A[i][j] = (c=='X') ? 1 : 0;
            }
        }
        int col_of_center = -1;
        for (int r = 0; r < N; ++r) {
            int cnt_x = 0, lst_col = -1, first_col=-1;
            for (int c = 0; c < N; ++c) {
                if (A[r][c]) {
                    if (cnt_x==0) first_col = c;
                    cnt_x++;
                    lst_col = c;
                }
            }
            if (cnt_x==2) {
                rlow[r]=first_col; rhigh[r]=lst_col;
            } else if (cnt_x==1 && col_of_center==-1) {
                col_of_center=lst_col;
                rlow[r]=first_col; rhigh[r]=lst_col;
            } else {
                goto IMPOSSIBLE;
            }
        }

        for (int c = 0; c < N; ++c) {
            int cnt_x=0, first_row=-1, lst_row=-1;
            for (int r = 0; r < N; ++r) {
                if (A[r][c]) {
                    if (cnt_x==0) first_row=r;
                    lst_row=r;
                    cnt_x++;
                }
            }
            if (cnt_x==2 || (cnt_x==1 && c==col_of_center)) {
                clow[c]=first_row;
                chigh[c]=lst_row;
            } else {
                goto IMPOSSIBLE;
            }
        }
        for (int r = 0; r < N; ++r) {
            int a = rlow[r], b = rhigh[r]; // cols
            int ah = chigh[a], bh = chigh[b]; // rows
            if (ah!=bh) {
                goto IMPOSSIBLE;
            }
        }
        printf("Case #%d: POSSIBLE\n", t);
        continue;
        IMPOSSIBLE: 
            printf("Case #%d: IMPOSSIBLE\n", t);
            continue;
    }

}