#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int N;
string str[3], rstr[3];
int main() {
    cin >> N;
    while (N--) {
        
        cin >> str[0] >> str[1] >> str[2];
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (i==j) continue;
                if (str[i].size() > str[j].size()) continue;
                // test if str[i] is prefix of str[j]
                if (str[i]==str[j].substr(0, str[i].size())) {
                    cout << "No\n";
                    goto NEXT;
                }
                // test if str[i] is suffix of str[j]
                if (str[i]==str[j].substr(str[j].size()-str[i].size() , str[j].size()) ) {
                    cout << "No\n";
                    goto NEXT;
                }
            }
        }
        cout << "Yes\n";
        NEXT:;
    }
}