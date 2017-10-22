#include <cstdio>
#include <cstring>
#include <vector>
#define MAX_LEN 5005
#define MAX_NODES 5000005 // estimate
using namespace std;
int N, L;
char s[MAX_LEN];
vector<int> adj[MAX_NODES];
char ltr[MAX_NODES];

int main () {
    // freopen("data.txt", "r", stdin);
    scanf("%d", &N);
    while (N--) {
        scanf(" %s", s);
        L = strlen(s);
        for (int i = 0; i < MAX_NODES; ++i) 
            adj[i] = vector<int>();
        
        int nodecnt=1;
        for (int i = 0; i < L; ++i) {
            int u = 0;
            for (int j = i; j < L; ++j) {
                bool found = false;
                for (size_t k = 0; k < adj[u].size(); ++k) {
                    int v = adj[u][k];
                    if (ltr[v]==s[j]) {
                        u = v;
                        found=true;
                        break;
                    }
                }
                if (!found) {
                    int w = nodecnt++;
                    ltr[w] = s[j];
                    adj[u].push_back(w);
                    u = w;
                }

            }
        }
        printf("%d\n", nodecnt);
    }
	return 0;
}