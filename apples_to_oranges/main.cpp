#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <utility>
#include <stack>
#include <cmath>
#include <iomanip>

#define less(a,b) (a<b-0.000001)
using namespace std;

const double INF = 1000000000.0;
const string A = "APPLES";

struct Node {
    vector<Node*> adj; 
    bool inStack; int low, num, comp;  double dist;
    Node() : adj(vector<Node*>()), inStack(0), low(-1), num(-1), comp(0), dist(INF) {}
};

struct Edge {
    Node *src, *dest;
    double w;
};

int N, M, dfsNum=0, numSCC=0;
unordered_map<string, Node> g = unordered_map<string, Node>();
Edge edges[4000];
stack<Node*> s = stack<Node*>();

void scc(Node* u){
    s.push(u);
    u->low=u->num=dfsNum++;
    u->inStack = 1;
    for (Node* v : u->adj){
        if (v->num==-1){ scc(v); u->low = min(u->low, v->low);} 
        else if (v->inStack) u->low = min(u->low, v->low);
    }
    if (u->low==u->num){
        ++numSCC;
        while (1){
            Node* v = s.top(); s.pop(); v->inStack=0; v->comp=numSCC;
            if (u==v) break;
        }
    }
}

bool search() {
    g[A].dist=0;
    const int acomp = g[A].comp;
    for (int i=1; i<=N; i++) {
        for (int j = 0; j < M; j++) {
            Node *u = edges[j].src, *v = edges[j].dest; double w = edges[j].w;
            if (u->comp==acomp && v->comp==acomp && less(u->dist+w, v->dist) ) {
                v->dist=u->dist+w;
                if (i==N) return 1;
            } 
        }
    }
    return 0;
}

int main() {
    cin.sync_with_stdio(0);
    cout.sync_with_stdio(0);
    cin >> N >> M;
    for(int i=0; i<N; i++){
        string str; cin >> str;
        g.insert( make_pair(str, Node() ) );
    }
    for (int i=0; i < M; i++){
        string a, b;
        cin >> a >> b >> edges[i].w;
        edges[i].src = &g[a]; edges[i].dest = &g[b];
        edges[i].w = -log(edges[i].w);
        edges[i].src->adj.push_back( edges[i].dest );
    }
    for (auto p : g) if (p.second.num==-1) scc(&p.second);
    if (search()) cout << "YA\n";
    else cout << "NAW\n";
    return 0;
}