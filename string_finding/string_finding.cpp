#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> computePrefixFunction(const string& P) {
    int m = (int)P.size();
    vector<int> pi(m);
    pi[0] = 0;
    int k = 0;
    for (int q=2; q<=m; q++) {
        while (k>0 && P[k] != P[q-1]) {
            k = pi[k-1];
        }
        if (P[k]==P[q-1]){
            ++k;
        }
        pi[q-1] = k;
    }
    return pi;
}

void KnuthMorrisMatcher(const string& T, const string& P) {
    int n = (int) T.size();
    int m = (int) P.size();
    vector<int> pi= computePrefixFunction(P);
    int q=0;
    for(int i = 1; i <= n; i++) {
        while (q>0 && P[q] != T[i-1]) {
            q=pi[q-1];
        }
        if (P[q]==T[i-1]){
            ++q;
        }
        if (q==m) {
            cout << i-m << endl;
            return;
        }
    }
    cout << -1 << endl;
    return;
}


int main () {
    string T, P;
    cin >> T >> P;
    KnuthMorrisMatcher(T, P);
    return 0;
}