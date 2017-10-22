#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 100005
using namespace std;
int T, t, N, bucket[MAXN], tmpBucket[MAXN], lcp[MAXN], rnk[MAXN];
char s[MAXN], sentinel[] = "$";

struct suffix {
    int idx;
    bool operator<(const suffix& sfx) const {
        if (t==0) return s[idx] < s[sfx.idx];
        else if (bucket[idx] != bucket[sfx.idx]) return bucket[idx] < bucket[sfx.idx];
        else return bucket[idx+t] < bucket[sfx.idx+t];
    }
    bool operator==(const suffix& sfx) const {return !(*this < sfx) && !(sfx < *this);}
} sa[MAXN];

bool update() {
    sort(sa, sa + N);
    int cur = 0;
    tmpBucket[sa[0].idx] = 0;
    for (int i = 1; i < N; ++i) {
        if (sa[i]==sa[i-1]) tmpBucket[sa[i].idx] = cur;
        else tmpBucket[sa[i].idx] = ++cur;
    }
    memcpy(bucket, tmpBucket, sizeof(int) * N);
    return cur == N-1;
}

void computeSA() {
    for (int i = 0; i < N; ++i) sa[i].idx = i;
    t = 0;
    update();
    for (t=1; 1; t <<= 1) 
        if (update()) break;
}

void computeLCP() {
    for (int i = 0; i < N; ++i) rnk[sa[i].idx] = i;
    for (int i = 0, k = 0; i < N; ++i, k?--k:0) {
        if (rnk[i]==N-1) {lcp[N-1]=k=0; continue;}
        int j = sa[rnk[i]+1].idx;
        for (;i+k<N && j+k<N && s[i+k]==s[j+k]; ++k);
        lcp[rnk[i]] = k;
    }
}

int main() {
    // freopen("data.txt", "r", stdin);
    scanf("%d", &T);
    while (T--) {
        scanf(" %s", s);
        strcat(s, sentinel);
        N = strlen(s);
        computeSA();
        computeLCP();
        int cnt = N-sa[0].idx;
        for (int i = 1; i < N; ++i) cnt += (N-sa[i].idx)-lcp[i-1];
        cnt -= N - 1;
        printf("%d\n", cnt);
    }
}