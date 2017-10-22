#include <iostream>
#include <unordered_map>
#include <cmath>
#include <stack>
#include <cstring>

#define mp make_pair
#define um unordered_map

const double INF = 100000.0;
using namespace std;

int N, M;
um<string, um<string, double> > adj;

int main() {
    cin.sync_with_stdio(0);
    cout.sync_with_stdio(0);
    cin >> N >> M;
    for (int i = 0; i < N; i++){
        string str; cin >> str;
        adj.insert(mp(str, um<string, double>()));
    }
    for (auto it = adj.begin(); it != adj.end(); ++it) {
        for (auto other : adj){
            if (it->first != other.first){
                it->second.insert(mp(other.first, 0.0));
            }
        }
    }
    for (int i = 0; i < M; i++) {
        string a, b; double w;
        cin >> a >> b >> w;
        adj[a][b] = -log(w);
    }
}