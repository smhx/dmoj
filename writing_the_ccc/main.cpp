#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
using namespace std;


int main() {
    freopen("data.txt", "r", stdin);
    int T; cin >> T;

    vector<string> probs;
    unordered_map<string, vector<int> > order;

    for (int i = 0; i < T; ++i) {
        string name; cin >> name; 
        probs.push_back(name);
        order[name] = {};
    }
    
    int N; cin >> N;
    for (int i = 1; i <= N; ++i) {
        string type; cin >> type; 
        order[type].push_back(i);
    }
    for (string type : probs) {
        for (int idx : order[type]) printf("%d\n", idx);
    }
}