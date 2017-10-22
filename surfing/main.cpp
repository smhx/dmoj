#include <iostream>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <regex>
using namespace std;

unordered_map<string, int> linkNum;

char ending[] = "</HTML>";

int N, visited[101], num[101], conn[101][101];
vector<int> adj[101];

const regex rgxLink("<A HREF=\"([^\"]+)\">");  

bool connected(int x, int y) {
    if (conn[x][y]!=0) return conn[x][y]>0;
    for (int i = 0; i < N; i++) visited[i]=0;
    vector<int> q = vector<int>();
    q.push_back(x);
    while (!q.empty()){
        int t=q.back();q.pop_back();
        visited[t]=1;
        for (auto n : adj[t]){
            if (n==y) {
                conn[x][y]=1; return true;
            }
            if (!visited[n]){
                q.push_back(n);
            }
        }
    }
    conn[x][y]=-1; return false;
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
        int needed=0;
        while (1) {
            char c=getchar();
            body+=c;
            if (c==ending[needed]){
                if (needed==6) break;
                ++needed;
            } else needed=0;
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
    while (1) {
        cin >> link1 >> link2;
        if  (link1=="The" && link2=="End") break;
        if ( connected(linkNum[link1], linkNum[link2]) )
            cout << "Can surf from " << link1 << " to " << link2 << ".\n";
        else    
            cout << "Can't surf from " << link1 << " to " << link2 << ".\n";
    }
}

