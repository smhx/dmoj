#include <cstdio>
#include <algorithm>
#include <vector>

#ifdef DMOJ
#define getchar() (*_pbuf ? *_pbuf++ : (_buf[fread_unlocked(_pbuf = _buf, 1, 1048576, stdin)] = 0, *_pbuf++))
char _buf[1048577], *_pbuf = _buf;
#endif

int readint() {
    int c, o = 0;
    while ((c = getchar()) < '0');
    do {o = (o<<3)+(o<<1) + (c - '0');} while ((c = getchar()) >= '0');
    return o;
}

using namespace std;

const int MAXN = 1000006, LOG=22;
int N, X[MAXN], R[MAXN], K[MAXN], rat[MAXN], id[MAXN], bit[MAXN];
char op[MAXN];

vector<int> v;
void update(int x, int v) {for (;x <= N; x += x&-x) bit[x] += v;}

int main() {
    freopen("data.txt", "r", stdin);
    N = readint();
    for (int i = 0; i < N; ++i) {
        while ((op[i] = getchar()) < '0');
        if (op[i]=='Q') K[i] = readint();
        else {
            X[i] = readint(); R[i] = readint();
            v.push_back(R[i]);
        }
    }
    sort(begin(v), end(v));

    int n = 0;

    for (int i = 0; i < N; ++i) {
        if (op[i]=='Q') {
            int j = 0, s = 0;
            for (int k = LOG; k>=0; --k) {
                if (j + (1<<k) > v.size() ) continue;
                if (s + bit[j + (1<<k)] <= n - K[i]){
                    s += bit[j + (1<<k)];
                    j += 1<<k;
                }
            }
            printf("%d\n", id[j+1]);

        } else if (op[i]=='N') {
            int rating = (lower_bound(begin(v), end(v), R[i])-begin(v))+1;
            rat[X[i]] = rating;
            id[rating] = X[i];
            update(rating, 1);
            ++n;
        } else {
            int rating = (lower_bound(begin(v), end(v), R[i])-begin(v))+1;
            update(rat[X[i]], -1);
            rat[X[i]] = rating;
            id[rating] = X[i];
            update(rating, 1);
        }
    }
}