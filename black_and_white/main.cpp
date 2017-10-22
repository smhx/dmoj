#include <cstdio>
#include <vector>
#include <algorithm>
#define MAXN 10005

#define getchar() (*_pbuf ? *_pbuf++ : (_buf[fread_unlocked(_pbuf = _buf, 1, 16384, stdin)] = 0, *_pbuf++))
char _buf[16385], *_pbuf = _buf;

int read() {
    int c, o = 0;
    while ((c = getchar()) < '0');
    do o = o*10 + c - '0';
    while ((c = getchar()) >= '0');
    return o;
}

using namespace std;

int N, M, cnt = 0, A[MAXN];
vector<int> S[MAXN];

int main() {
    scanf("%d%d", &N, &M);
    N = read(); M = read();
    for (int i = 0; i < M; ++i) {
        // int x, y, w, h; scanf("%d%d%d%d", &x, &y, &w, &h);
        int x = read(), y = read(), w = read(), h = read();
        S[x].push_back(y);
        S[x].push_back(y+h);
        S[x+w].push_back(y);
        S[x+w].push_back(y+h);
    }

    for (int i = 0; i < N; ++i) sort(S[i].begin(), S[i].end());

    for (int j = 0, presum=0; j < N; ++j) {
        if (!S[j].size()) cnt += presum;
        else {
            int i = presum = 0;
            for (size_t k = 0; k < S[j].size(); ++k) 
                for (; i < S[j][k]; ++i) A[i] += k, presum += A[i]&1;
        
            for (; i < N; ++i) presum += A[i]&1;

            cnt += presum;
        }
        
    }

    printf("%d\n", cnt);
}