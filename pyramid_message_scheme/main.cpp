#include <iostream>
#include <cstring>
#include <unordered_map>
#include <vector>
using namespace std;

int L, n;
unordered_map<string, int> dict;
vector< vector<int> > adj;
int main() {
    cin >> L;
    while (L--) {
        cin >> n;
        adj = vector< vector<int> >(n);
        int prev = -1, cnt=0;
        // numbered from 0 to n-1
        for (int i = 0; i < n; ++i) {
            string name;
            cin >> name;
            if (dict.find(name) != dict.end()) {
                if (prev != -1) adj[prev].push_back(cnt);  
                dict[name]=cnt++;
            } 
            prev = dict[name];
        }
    }
}

