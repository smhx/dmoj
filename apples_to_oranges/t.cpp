#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <utility>
#include <stack>

#define INF 100000.0f
#define mp make_pair

using namespace std;

struct Edge {
    string src, dest;
    float w;
};

struct Node {
    vector<int> adj; // holds the index of the edge
    bool visited; int low, num, comp; float dist;
    Node() : adj(vector<int>()), visited(0), low(0), num(-1), comp(0), dist(INF) {}
};

const string A = "APPLES";

int N, M, dfsNum=0, numSCC=0;
unordered_map<string, Node> g = unordered_map<string, Node>();
Edge edges[4001];

stack<string> S = stack<string>();
void scc(string us){
    // cout << "In scc with " << us << "\n";
    S.push(us);
    Node* u = &g[us];
    u->low=u->num=dfsNum++;
    u->visited = 1;
    for (auto e : u->adj){
        // cout << "Looking at edge " << edges[e].dest << "\n";
        Node v = g[edges[e].dest];
        if (v.num==-1){
            scc(edges[e].dest);
            u->low = min(u->low, v.low);
        } 
        if (v.visited){
            u->low = min(u->low, v.low);
        }
    }
    if (u->low==u->num){
        ++numSCC;
        while (1){
            string v = S.top(); S.pop(); g[v].visited=0; g[v].comp=numSCC;
            if (us==v) break;
        }
    }
}

bool search() {
    g[A].dist=1.0f;
    const int acomp = g[A].comp;
    for (int i=1; i<= N; i++) {
        // printf("i=%d\n", i);
        for (int j = 0; j < M; j++) {
            Node *u = &g[edges[j].src], *v = &g[edges[j].dest]; float w = edges[j].w;
            // cout << "   Node u is " << edges[j].src << " and node v is " << edges[j].dest << "\n";
            if (u->comp==acomp && v->comp==acomp && u->dist != INF && u->dist*w < v->dist ) {
                // cout << "setting v.dist to " << u->dist*w;
                v->dist=u->dist*w;
                if (i==N){
                    // cout << "i==N returning true there is a negative cycle\n";
                    // there is a negative weight cycle
                    return true;
                }
            }
        }
    }
    // there is no negative weight cycle. But if the best weight is zero...
    // cout << "Returning false there is no negative cycle\n";
    return false;
}

int main() {
    cin.sync_with_stdio(0);
    cout.sync_with_stdio(0);
    cin >> N >> M;
    for(int i=0;i<N;i++){
        string str;
        cin >> str;
        g.insert( mp(str, Node() ) );
    }
    for (int i=0; i < M; i++){
        cin >> edges[i].src >> edges[i].dest >> edges[i].w;
        edges[i].w=1/edges[i].w;
        g[edges[i].src].adj.push_back(i);
    }

    for (auto p : g){
        if (p.second.num==-1) scc(p.first);
    }

    // for (auto p : g){
    //     cout << "Node " << p.first << " has comp " << p.second.comp << "\n";
    // }
    if (search()) cout << "Ya\n";
    else cout << "Naw\n";
    return 0;
}