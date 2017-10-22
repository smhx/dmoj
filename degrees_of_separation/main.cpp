#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
#define MAXN 52

using namespace std;

vector<int> adj[MAXN];
int mem[MAXN], lvl[MAXN];
char cmd;

int dist(int x, int y) {
    memset(lvl, -1, sizeof lvl);
    lvl[x] = 0;
    queue<int> q;
    q.push(x);
    while (!q.empty()) {
        int u=q.front();
        q.pop();
        if (u==y) break;
        for (size_t i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i];
            if (lvl[v]==-1) {
                lvl[v] = lvl[u] + 1;
                q.push(v);
            }
        }
    }
    return lvl[y];
}

int main() {
    // freopen("data.txt", "r", stdin);
    
    int f1[1] = {6};
    int f2[1] = {6};
    int f3[4] = {4, 5, 6, 15};
    int f4[3] = {3, 5, 6};
    int f5[3] = {4, 6, 3};
    int f6[6] = {1, 2, 3, 4, 5, 7};
    int f7[2] = {6, 8};
    int f8[2] = {7, 9};
    int f9[3] = {8, 10, 12};
    int f10[2] = {9, 11};
    int f11[2] = {10, 12};
    int f12[3] = {9, 11, 13};
    int f13[3] = {12, 15, 14};
    int f14[1] = {13};
    int f15[2] = {3, 13};
    int f16[2] = {18, 17};
    int f17[2] = {16, 18};
    int f18[2] = {16, 17};

    adj[1] = vector<int>(f1, f1+1);
    adj[2] = vector<int>(f2, f2+1);
    adj[3] = vector<int>(f3, f3+4);
    adj[4] = vector<int>(f4, f4+3);
    adj[5] = vector<int>(f5, f5+3);
    adj[6] = vector<int>(f6, f6+6);
    adj[7] = vector<int>(f7, f7+2);
    adj[8] = vector<int>(f8, f8+2);
    adj[9] = vector<int>(f9, f9+3);
    adj[10] = vector<int>(f10, f10+2);
    adj[11] = vector<int>(f11, f11+2);
    adj[12] = vector<int>(f12, f12+3);
    adj[13] = vector<int>(f13, f13+3);
    adj[14] = vector<int>(f14, f14+1);
    adj[15] = vector<int>(f15, f15+2);
    adj[16] = vector<int>(f16, f16+2);
    adj[17] = vector<int>(f17, f17+2);
    adj[18] = vector<int>(f18, f18+2);


    while (1) {
        scanf(" %c", &cmd);
        
        if (cmd=='i') {
            // add friend
            int x, y;
            scanf("%d%d", &x, &y);
            for (vector<int>::iterator it = adj[x].begin(); it != adj[x].end(); ++it) { 
                if (*it==y) {
                    adj[x].erase(it);
                    break;
                }
            }

            for (vector<int>::iterator it = adj[y].begin(); it != adj[y].end(); ++it) {
                if (*it==x) {
                    adj[y].erase(it);
                    break;
                }
            }
        
            adj[x].push_back(y);
            adj[y].push_back(x);
        } else if (cmd=='d') {
            int x, y;
            scanf("%d%d", &x, &y);
            for (vector<int>::iterator it = adj[x].begin(); it != adj[x].end(); ++it) { 
                if (*it==y) {
                    adj[x].erase(it);
                    break;
                }
            }

            for (vector<int>::iterator it = adj[y].begin(); it != adj[y].end(); ++it) {
                if (*it==x) {
                    adj[y].erase(it);
                    break;
                }
            }
            
            
        } else if (cmd=='n') {
            int x; 
            scanf("%d", &x);
            printf("%d\n", (int)adj[x].size());
        } else if (cmd=='f') {
            int x; 
            scanf("%d", &x);
            memset(mem, 0, sizeof mem);
            mem[x] = 1;
            int cnt=0;
            for (size_t i = 0; i < adj[x].size(); ++i) {
                mem[adj[x][i]] = 1;
            }
            for (size_t i = 0; i < adj[x].size(); ++i) {
                int y = adj[x][i];
                for (size_t j = 0; j < adj[y].size(); ++j) {
                    int z = adj[y][j];
                    if (!mem[z]) {
                        ++cnt; mem[z] = 1;
                    } 
                }
            }
            printf("%d\n", cnt);
        } else if (cmd=='s') {
            int x, y;
            scanf("%d%d", &x, &y);
            int d = dist(x, y);
            if (d==-1) printf("Not connected\n");
            else printf("%d\n", d);
        } else return 0;
    }
}