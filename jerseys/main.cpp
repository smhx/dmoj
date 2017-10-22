#include <cstdio>
#define MAX 1000007

int J, A, size[MAX];
bool taken[MAX];
int cnt = 0;


int main(){ 
    freopen("s2/s2.6.in", "r", stdin);
    scanf("%d%d", &J, &A);
    for (int i = 1; i <= J; ++i) {
        char c; scanf(" %c", &c);
        if (c=='S') size[i] = 0;
        else if (c=='M') size[i] = 1;
        else size[i] =2;
    }
    for (int i = 1; i <= A; ++i) {
        int num; char c;
        scanf(" %c %d", &c, &num);
        int si;
        if (c=='S') si = 0;
        else if (c=='M') si = 1;
        else si =2;
        if (!taken[num] && si <= size[num]) {
            ++cnt; taken[num] = true;
        }
    }
    printf("%d\n", cnt);
}