#include <cstdio>
#define MAXN 100005
int N, T, m, v, h;

bool dir[MAXN]; // true for vertical, false for horizontal

int duration() {
    int ans = 0;
    if (dir[0]==true) ans = 1;
    else ans = h + 3*v;
    return ans;
}

int main() {
    // freopen("data.txt", "r", stdin);
    scanf("%d%d", &N, &T);
    for (int i = 0; i < N; ++i) {
        char c; scanf(" %c", &c);
        dir[i] = c=='|';
        if (dir[i]) ++v;
        else ++h;
    }
    while (T--) {
        scanf("%d", &m);
        --m;
        dir[m] = !dir[m];
        if (dir[m]) ++v, --h;
        else --v, ++h;
        printf("%d\n", duration());
    }
}