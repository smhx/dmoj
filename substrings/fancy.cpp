#include <cstdio>
#include <cstring>
#include <set>
#define MAX_LEN 5005
#define MAX_NODES 4000000 // estimate
using namespace std;
int N, L;
char s[MAX_LEN];
typedef pair<char, int> ci;
typedef set<ci> node;

node nodes[MAX_NODES];

int main () {
    // freopen("data.txt", "r", stdin);
    scanf("%d", &N);
    while (N--) {
        scanf(" %s", s);
        L = strlen(s);
        for (int i = 0; i < MAX_NODES; ++i) 
            nodes[i] = node();
        
        int nodecnt=1;
        for (int i = 0; i < L; ++i) {
            int u = 0;
            for (int j = i; j < L; ++j) {
                node::iterator itr = lower_bound(nodes[u].begin(), nodes[u].end(), ci(s[j], 0) );
                if (itr->first==s[j]) {
                    u = itr->second;
                } else {
                    int w = nodecnt++;
                    nodes[u].insert( ci(s[j], w) );
                    u = w;
                }

            }
        }
        printf("%d\n", nodecnt);
    }
	return 0;
}