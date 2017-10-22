#include <iostream>
#include <cstring>
#include <regex>
using namespace std;
int main() {
    string str;
    getline(cin, str);
    regex r("<A HREF=\"([^\"]+)\">.*?</A>");  
    smatch m;
    while (regex_search(str, m, r)) {
        cout << m[1] << endl;
        str=m.suffix();
        cout << "str is now:" << str << endl;
    }
}