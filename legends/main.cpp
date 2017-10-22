#include <cstdio>
#include <vector>
#include <cstring>
#include <unordered_map>
#define MAXN 100005
using namespace std;

// #define getchar() (*_pbuf ? *_pbuf++ : (_buf[fread_unlocked(_pbuf = _buf, 1, 16384, stdin)] = 0, *_pbuf++))
char _buf[16385], *_pbuf = _buf;

int read() {
    int c, o = 0;
    while ((c = getchar()) < '0');
    do o = o*10 + c - '0';
    while ((c = getchar()) >= '0');
    return o;
}
typedef pair<int, int> ii;
int S, T, N, M, dfscnt, visit[MAXN], p[MAXN], lowlink[MAXN], dfsidx[MAXN];
bool found;
vector<int> adj[MAXN];
vector<ii> s;

void dfs1(int u) {
    int cycles = 0;
    lowlink[u] = dfsidx[u] = ++dfscnt;
    for (int v : adj[u]) {
        if (found) return;
        if (dfsidx[v]==0) {
            p[v] = u;
            dfs1(v);
            if (lowlink[v] < dfsidx[u]) ++cycles;
            lowlink[u] = min(lowlink[u], lowlink[v]);
        } else if (v != p[u]) {
            lowlink[u] = min(lowlink[u], dfsidx[v]);
            if (dfsidx[v] < dfsidx[u]) ++cycles;
        }
        if (cycles ==  2) found = true;
    }
}

void dfs2(int u) {
    visit[u] = 2;
    for (int v : adj[u]) {
        if (found) return;
        if (visit[v]==0) {
            p[v] = u;
            dfs2(v);
        } else if (v != p[u] && visit[v]==2) found = true;
    }
    visit[u] = 1;
}

void dfs3(int u) {
    lowlink[u] = dfsidx[u] = ++dfscnt;    
    for (int v : adj[u]) {
        if (found) return;
        if (dfsidx[v]==0) {
            s.push_back(ii(u, v));
            p[v] = u;
            dfs3(v);
            lowlink[u] = min(lowlink[u], lowlink[v]);        
            if ( dfsidx[u] <= lowlink[v]) {
                int cnt = 1;
                while (s.back() != ii(u, v)) s.pop_back(), ++cnt;       
                s.pop_back();
                if (cnt > 3) {
                    found  = true;
                    return;
                }
            }
        } else if (v != p[u] && dfsidx[u] > dfsidx[v]) {
            lowlink[u] = min(lowlink[u], dfsidx[v]);
            s.push_back(ii(u, v));
        }
    }
}   

void dfs5(int u) {
    lowlink[u] = dfsidx[u] = ++dfscnt;
    for (int v : adj[u]) {
        if (found) return;
        if (dfsidx[v]==0) {
            s.push_back(ii(u, v));
            p[v] = u;
            dfs5(v);
            lowlink[u] = min(lowlink[u], lowlink[v]);        
            if ( dfsidx[u] <= lowlink[v]) {
                unordered_map<int, int> nodes;
                vector<ii> edges;
                while (1) {
                    ii back = s.back();
                    edges.push_back(back);
                    if (nodes.find(back.first)==nodes.end()) nodes[back.first] = 1;
                    else ++nodes[back.first];
                    if (nodes.find(back.second)==nodes.end()) nodes[back.second] =1;
                    else ++nodes[back.second];
                    s.pop_back();
                    if (back==ii(u, v)) break;
                }
                
                if (nodes.size() > 4) {
                    bool special = false;
                    int a = -1, b = -1;
                    for (ii x : nodes) {
                        if (x.second!=2) {
                            if (a==-1) a = x.first;
                            else if (a != -1 && b==-1) b = x.first, special = true;
                            else special = false;
                        }
                    }

                    if (special) 
                        for (ii e : edges) 
                            if (e.first!=a && e.first!=b && e.second!=a && e.second!=b) 
                                special = false;
                            
                    if (!special) {
                        int cnt=0;
                        for (ii x : nodes) 
                            if (adj[x.first].size()>2) ++cnt;
                        if (cnt>1) found = true;
                    } else {
                        if (edges.size() >= 7) found = true; 
                        for (ii x : nodes) 
                            if (adj[x.first].size()>x.second) found = true;
                    }
                
                } else if (nodes.size()==4 && edges.size() > 4){
                    for (ii x : nodes) 
                        if (adj[x.first].size()-x.second > 0) found = true;
                } else if (nodes.size()==4 || nodes.size()==3) {
                    int cnt=0;
                    for (ii x : nodes) 
                        if (adj[x.first].size()>2) ++cnt;
                    if (cnt > 1) found = true;
                }
            }

        } else if (v != p[u] && dfsidx[v] < dfsidx[u]) {
            lowlink[u] = min(lowlink[u], dfsidx[v]);
            s.push_back(ii(u, v));
        }
    }
}   


int main() {
    S = read(); T = read();
    while (T--) {
        N = read(); M = read();
        for (int i = 1; i <= N; ++i) adj[i].clear();
        for (int i = 0, a, b; i < M; ++i) {
            a = read(); b = read();    
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        if (S != 4) {
            memset(p, 0, sizeof(int) * (N+2));
            memset(visit, 0, sizeof(int) * (N+2));
        }
        if (S==3 || S==5 || S==1) {
            memset(dfsidx, 0, sizeof(int) * (N+2));
            memset(lowlink, 0, sizeof(int) * (N+2));
            dfscnt = 0;
        }
        if (S==3 || S==5) s.clear();
        
        found = false;

        if (S==1) dfs1(1);
        else if (S==2) dfs2(1);
        else if (S==3) dfs3(1);
        else if (S==4) {
            for (int i = 1; i <= N && !found; ++i) 
                if (adj[i].size() > 2) found = true;
        } else dfs5(1);
        
        printf("%s\n", found ? "YES" : "NO");
        
    }


}