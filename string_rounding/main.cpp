#include <cstdio>
#include <cstring>
char S[105], pre;

void round(int i) {
    if (S[i] > 'm') {
        if (i-1 < 0 ) pre = 'a';
        else if (S[i-1] != 'z') ++S[i-1];
        else round(i-1);
    }
    S[i] = 'a';
}

int main() {
    // freopen("data.txt", "r", stdin);
    scanf(" %s", S);
    round(strlen(S)-1);
    if (pre) printf("%c", pre);
    printf("%s\n", S);
}