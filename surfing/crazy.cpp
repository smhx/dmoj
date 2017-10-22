#include <iostream>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <regex>
#include <algorithm>
using namespace std;

unordered_map<string, int> linkNum;

int N, visited[101], num[101], low[101], comp[101], numCount=0,sccCount=0;
vector<int> adj[101], dag[101], S;

const regex rgxLink("<A HREF=\"([^\"]+)\">");  

bool connected(int x, int y) {
    for (int i = 0; i < N; i++) visited[i]=0;
    vector<int> q = vector<int>();
    q.push_back(x);
    while (!q.empty()){
        int t=q.back();q.pop_back();
        visited[t]=1;
        for (auto n : adj[t]){
            if (n==y) return true;
            if (!visited[n]){
                q.push_back(n);
            }
        }
    }
    return false;
}

void scc(int u) {
    low[u]=num[u]=numCount++;
    visited[u]=1;
    S.push_back(u);
    for (int j=0;j<(int)adj[u].size();j++){
        int v=adj[u][j];
        if (num[v]==-1) {
            scc(v);
            low[u]=min(low[u], low[v]);
        } else if (visited[v]){
            low[u]=min(low[u], low[v]);
        }
    }
    if (low[u]==num[u]){
        comp[u]=++sccCount;
        while (1){
            int v=S.back();S.pop_back();visited[v]=0;
            if (u==v) break;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> N;
    int idx=0;
    for (int i = 0; i < N; i++) {
        string link;
        cin >> link;
        if (linkNum.find(link)==linkNum.end()) linkNum[link]=idx++;
        int num = linkNum[link];
        string body=""; 
        getchar();
        while (1) {
            body+=getchar();
            if (body.size()>=7){
                if (body.substr(body.size()-7)=="</HTML>") break;
            }
        }
        smatch m;
        while (regex_search(body, m, rgxLink)){
            if (linkNum.find(m[1])==linkNum.end()){
                linkNum[m[1]]=idx; 
                adj[num].push_back(idx++);
            } else adj[num].push_back(linkNum[m[1]]);
            cout << "Link from " << link << " to " << m[1] << "\n";
            body=m.suffix();
        }
    }
    
    string link1, link2;
    memset(num, -1, sizeof(int));
    memset(visited, -1, sizeof(int));
    for (int i = 0; i < N; i++){
        if (num[i]==-1) scc(i);
    }
    


    while (1) {
        cin >> link1 >> link2;
        if  (link1=="The" && link2=="End") break;
        if ( connected(linkNum[link1], linkNum[link2]) )
            cout << "Can surf from " << link1 << " to " << link2 << ".\n";
        else    
            cout << "Can't surf from " << link1 << " to " << link2 << ".\n";
    }
}

