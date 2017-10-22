#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
vector<string> p;
string in;


int main() {
    freopen("data.txt", "r", stdin);
    cin >> in;
    sort(in.begin(), in.end());
    do {
        p.push_back(in);
    } while (next_permutation(in.begin(), in.end()));
    
    sort(p.begin(), p.end());
    unique(p.begin(), p.end());
    for (string s : p)
        cout << s << endl;
}