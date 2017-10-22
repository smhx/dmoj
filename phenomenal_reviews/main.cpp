#include <cstdio>
#include <vector>
#include <stack>
#include <list>
using namespace std;

struct Node {
    bool ignore, visit, pho, attack;
    int steps;
    vector<Node*> adj;
};

int N, M, numEdges, phoo;
Node nodes[100001];

void trim() {
    list<Node*> border = list<Node*>();
    for (int i = 0; i < N; i++) {
        if (nodes[i].adj.size()==1 && !nodes[i].pho) border.push_back(&nodes[i]);
    }
    while ( !border.empty() ) {
        printf("border is not empty. Has %d\n", (int)border.size() );
        for (auto it = border.begin(); it != border.end(); ) {
            Node* u = *it;
            printf("At node %d\n", int(u-nodes) );
            if (u->pho) {
                printf("u is pho erasing\n");
                it = border.erase(it);
                continue;
            }
            
            // Take the next step. Well first you need to make sure there is only one step...
            // If there is more, suicide. 
            int cnt= 0;
            Node* dest = u;
            for (auto v : u->adj) {
                if (!v->ignore) {
                    ++cnt;
                    dest = v;
                }
            }
            
            if (cnt > 1 || cnt==0) {
                printf("not a leaf dying\n");
                // Not a leaf. Die.
                u->attack = false;
                it = border.erase(it);
                continue;
            }

            u->ignore = true;

            printf("dest is %d\n", int(dest-nodes) );
            --numEdges;
            if (dest->attack) {
                printf("dest is attacked\n");
                it = border.erase(it);
                continue;
            }
            printf("moving to dest\n");
            *it = dest;
            dest->attack = true;
            ++it;
            
        }
    }
}


Node* opposite(Node* u) {
    stack<Node*> bag = stack<Node*>();
    Node* mx = u;
    bag.push(u);
    while (!bag.empty()) {
        Node* top = bag.top();
        top->visit = true;
        bag.pop();
        if (top->steps > mx->steps) mx = top;
        for (auto v : top->adj) {
            if (!v->ignore && !v->visit) {
                v->steps = top->steps+1;
                bag.push(v);
            }
        }
    }
    return mx;
}

int heaviestPath() {
    Node* a = opposite(&nodes[phoo]);
    for (int i = 0; i < N; i++) {
        nodes[i].visit = false;
        nodes[i].steps = 0;
    }    
    Node* b = opposite(a);
    return b->steps;
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; i++) {
        scanf("%d", &phoo);
        nodes[phoo].pho = true;
    }
    for (int i = 0, a, b; i < N-1; i++) {
        scanf("%d%d", &a, &b);
        nodes[a].adj.push_back(&nodes[b]);
        nodes[b].adj.push_back(&nodes[a]);
    }

    numEdges = N-1;
    
    trim();

    for (int i = 0; i < N; i++) {
        if (nodes[i].ignore) continue;
        printf("%d: ", i);
        for (auto n : nodes[i].adj) {
            if (n->ignore) continue;
            printf("%d ", int(n-nodes));
        }
        printf("\n");
    }
   
    int dw = 2*numEdges;
    int p = heaviestPath();
    printf("dw is %d, p is %d\n", dw, p);
    printf("%d\n", dw-p);
    return 0;
}