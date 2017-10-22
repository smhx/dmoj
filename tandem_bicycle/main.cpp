#include <cstdio>
#include <algorithm>
#include <functional>
#include <cstdlib>
#define MAXN 100
using namespace std;
int N, T, a[MAXN], b[MAXN], totSpeed=0;

int main() {
    // freopen("data.txt","r", stdin);
    scanf("%d%d", &T, &N);
    for (int i = 0; i < N; ++i) scanf("%d", a+i);
    for (int i = 0; i < N; ++i) scanf("%d", b+i);
    sort(a, a+N);
    if (T==1) sort(b, b+N);
    else sort(b, b+N, greater<int>());

    for (int i = 0; i < N; ++i)
        totSpeed += max(a[i], b[i]);
    printf("%d\n", totSpeed);
}