#include <cstdio>
#include <vector>
#include <algorithm>
#include <stack>
#include <cstring>
#define MAX 10001
using namespace std;
typedef vector<int> vi;
int N, M;
vi adj[MAX], rings[MAX], cities_in_ring[MAX], chains[MAX];
int end_of_chain[MAX];

int lowlink[MAX], idx[MAX], idxcnt=1, chain_cnt=1, ring_cnt=1;
stack<int> hist;

int legit_memo[MAX], loop_memo[MAX];

void label(int u, int par) {
    lowlink[u]=idx[u]=idxcnt++;
    hist.push(u);
    for (auto v : adj[u]) {
        if (v==par) continue;
        if (idx[v]) {
            lowlink[u]=min(lowlink[u], idx[v]);
        } else {
            label(v, u);
            if (lowlink[v]<idx[u]) {
                lowlink[u]=min(lowlink[u], lowlink[v]);
            } else if (lowlink[v]==idx[u]) {
                // pop it!
                rings[u].push_back(ring_cnt);
                while (1) {
                    int t = hist.top(); hist.pop();
                    cities_in_ring[ring_cnt].push_back(t);
                    if (cities_in_ring[ring_cnt].back()==v) break;
                }
                ++ring_cnt;
            } else {
                int t = hist.top(); hist.pop();
                chains[u].push_back(chain_cnt);
                end_of_chain[chain_cnt++] = t;
            }
        }
    }
}

int loop(int u) {
    if (loop_memo[u] != -1) return loop_memo[u];
    int loop_dist=0;
    for (auto r : rings[u]) {
        loop_dist += (int)cities_in_ring[r].size()+1;
        for (auto city : cities_in_ring[r]){
            if (city==u) printf("WRONG!!!\n");
            loop_dist += loop(city);
        }
    }
    return loop_memo[u]=loop_dist;
}

int legit(int u) {
    if (legit_memo[u]!=-1) return legit_memo[u];
    int looper = loop(u);
    int cur_max = looper;
    for (auto c : chains[u]) {
        cur_max = max(cur_max, looper+1+legit(end_of_chain[c]) );
    }
    for (auto r : rings[u]) {
        int best = 0;
        int sub1=1, sub2=1;
        int s = (int)cities_in_ring[r].size();
        for (int i = 0; i < s; ++i) {
            int c = cities_in_ring[r][i];
            best = max(best, looper-sub1+legit(c)-loop(c));
            sub1 += 1+loop(c);
            int d = cities_in_ring[r][s-i-1];

            best = max(best, looper-sub2+legit(d)-loop(d));
            sub2 += 1+loop(d);
        }
        cur_max = max(cur_max, best);
    }
    return legit_memo[u]=cur_max;
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; ++i) {
        int a, b; scanf("%d%d", &a, &b);
        adj[a].push_back(b); adj[b].push_back(a);
    }
    memset(legit_memo, -1, sizeof legit_memo);
    memset(loop_memo, -1, sizeof loop_memo);
    label(1, -1);
    // for (int i = 1; i <= N; ++i) {
    //     printf("rings[%d]:\n", i);
    //     for (auto r : rings[i]) {
    //         printf("%d ", r);
    //     }
    //     printf("\n");
    // }
    // for (int i = 1; i < 5; i++) {
    //     printf("cities_in_ring[%d]:\n", i);
    //     for (auto c :cities_in_ring[i]) {
    //         printf("%d ", c);
    //     }
    //     printf("\n");
    // }

    loop(1);
    // printf("looped\n");
    // for (int i = 1; i <= N; ++i) {
    //     printf("loop(%d)=%d\n", i, loop(i));
    // }
    // for (int i = 1; i <= N; ++i) {
    //     printf("legit(%d)=%d\n", i, legit(i));
    // }
    printf("%d\n", legit(1));
}