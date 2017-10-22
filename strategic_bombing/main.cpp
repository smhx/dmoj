#include <cstdio>
#include <vector>
#include <cstring>
#define MAXN 26

using namespace std;

int adj[MAXN][MAXN], cnt=0, visited[MAXN];

bool connected() {
    memset(visited, 0, sizeof visited);    
    vector<int> s;
    s.push_back(0);
    while (!s.empty()) {
        int u = s.back(); s.pop_back();
        if (u==1) return true;
        visited[u] = 1;
        for (int v = 0; v < MAXN; ++v) {
            if (adj[u][v] && !visited[v] && v != u) {
                s.push_back(v);
            }
        }
    }
    return false;
}

int main() {
    // freopen("data.txt", "r", stdin);
    while (1) {
        char u, v;
        scanf(" %c %c", &u, &v);
        if (u=='*') break;
        adj[u-'A'][v-'A']=1;
        adj[v-'A'][u-'A']=1;
    }

    for (int i= 0; i < MAXN-1; ++i ) {
        for (int j = i + 1; j < MAXN; ++j) {
            if (adj[i][j]) {
                adj[i][j] = 0;
                adj[j][i] = 0;
                if (!connected()) {
                    ++cnt;
                    printf("%c%c\n", i+'A', j+'A');
                }
                adj[i][j] = 1;
                adj[j][i] = 1;
            }
        }
    }
    printf("There are %d disconnecting roads.\n", cnt);
}
