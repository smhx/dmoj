#include <cstdio>
int mem[400][400], N, max=-1;

int main() {

    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &mem[i][i]);
        mem[i][i] *= -1;
    }

    for (int i = 0; i < N; i++) 
        for (int j = i+1; j < N; j++) 
            mem[i][j] = mem[j][j]+mem[i][j-1];
    
    for (int h = 0; h < N; h++) {
        for (int l = h; l >= 0; l--) {
            if (l==h) mem[l][h] *= -1;
            else {
                int i = l, j = h;
                while (i < j) {
                    if (mem[l][i] < 0) ++i;
    
                    else if (mem[j][h] < 0) --j;

                    else if (mem[j][h] > mem[l][i]) ++i;

                    else if ( (j==i+1 || mem[i+1][j-1] > 0) && mem[l][i]==mem[j][h] ) {
                        mem[l][h] *= -1;
                        break;
                    }

                    else --j;
                }
            }
            if (max < mem[l][h]) max = mem[l][h];
        }
    }
    printf("%d\n", max);
    return 0;
}
