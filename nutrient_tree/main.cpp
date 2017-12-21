#include <iostream>
#include <string>
#include <cstring>
using namespace std;

const int NODES = 800, MAX_X = 2505;

int totX, tree[NODES], mem[NODES][MAX_X],best[NODES][MAX_X];
string in;

bool calc[NODES];

void input(int u, int& i) {
    while (i < in.size() && in[i] < '(') ++i;
    if (i>=in.size()) return;
    tree[u] = 0;  
    if (in[i]=='(') {   
        ++i;
        input(u<<1, i);
        input(u<<1|1, i);
        while (i < in.size() && in[i] < '(') ++i;
        ++i;
    } else {
        while (i < in.size() && '0' <= in[i] && in[i] <= '9') 
            tree[u] = 10*tree[u] + (in[i++]-'0');
    }
}

int dp(int, int);

void calcbest(int u) {
   calc[u] = true;
   int lowbound = 0; 
   for (int a = 0; a <= totX; ++a) {
        if (dp(u,lowbound)>(1+a-lowbound)*(1+a-lowbound)) {
            best[u][a] = (1+a-lowbound)*(1+a-lowbound); 
            continue;
        }
        while (lowbound + 1 <= a && dp(u, lowbound+1) <= (a-lowbound)*(a-lowbound)) ++lowbound;
        if (lowbound < a) best[u][a]= max(dp(u,lowbound), (a-lowbound)*(a-lowbound));
        else best[u][a] = dp(u,lowbound);
   }
}

int dp(int u, int x) {
    if (mem[u][x]!=-1) return mem[u][x];
    else if (tree[u<<1]==-1 && tree[u<<1|1]==-1) return mem[u][x] = tree[u]+x; 
    else if (tree[u<<1]!=-1 && tree[u<<1|1]==-1) {
        if (!calc[u<<1]) calcbest(u<<1);
        return mem[u][x] = best[u<<1][x]; 
    } else if (tree[u<<1]==-1 && tree[u<<1|1] != -1) {
        if (!calc[u<<1|1]) calcbest(u<<1|1);
        return mem[u][x] = best[u<<1|1][x]; 
    } else {
        if (!calc[u<<1]) calcbest(u<<1);
        if (!calc[u<<1|1]) calcbest(u<<1|1);
        mem[u][x]=0; 
        for (int a = 0; a <= x; ++a) 
            mem[u][x] = max(mem[u][x], best[u<<1][a]+best[u<<1|1][x-a]);
        return mem[u][x];
    } 
}

int main() {
    freopen("data.txt", "r", stdin);
    getline(cin, in);
    int tridx = 0;
    memset(tree, -1, sizeof tree);
    memset(mem, -1, sizeof mem);
    input(1, tridx);
    cin >> totX;
    printf("%d\n", dp(1, totX));
}