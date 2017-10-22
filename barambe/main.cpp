#include <iostream>
#include <string>
using namespace std;


int main() {
    // freopen("data.txt", "r", stdin);
    string line;

    getline(cin, line);
    bool firstWord = true;
    bool startOfWord = true;
    for (int i = 0; i < line.size(); ++i) {
        if (startOfWord) {
            if (isupper(line[i]) && !firstWord) {
                printf(". %c", line[i]);
            } else {
                if (!firstWord) printf(" %c", line[i]);
                else printf("%c", line[i]);
            }
            startOfWord = false;
        } else {
            if (isalpha(line[i])) {
                startOfWord = false;
                printf("%c", line[i]);
            } else {
                startOfWord = true;
            }
        }
        firstWord = false;
    }
    printf(".\n");
}