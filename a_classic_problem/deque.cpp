#include <cstdio>
#include <algorithm>
#include <deque>
#define MAXN 3000005
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
typedef pair<int, int> ii;
typedef long long ll;
int N, K, A[MAXN];
deque<ii> m, M;
ll cnt = 0;
int main() {
    // freopen("data.txt", "r", stdin);
    N = read();
    K = read();
    for (int i = 0; i < N; ++i) A[i] = read();

    
    int start = 0, end = 1;
    m.push_back(ii(A[0], 0));
    M.push_back(ii(A[0], 0));
    while (end != N+1) {
        while (M.front().first-m.front().first <= K && end <= N) {
            cnt += end - start;
            while (!M.empty() && M.back().first < A[end]) M.pop_back();
            M.push_back(ii(A[end], end));
            while (!m.empty() && m.back().first > A[end]) m.pop_back();
            m.push_back(ii(A[end], end));
            ++end;
        }
        while (M.front().first-m.front().first > K) {
            start = min(m.front().second, M.front().second)+1;
            while (M.front().second < start) M.pop_front();
            while (m.front().second < start) m.pop_front();
        }
    }
    
    printf("%lld\n", cnt);
    
}