#include <iostream>
#include <string>
using namespace std;
int N, M;
string word;

int main() {
    // freopen("data.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    scanf("%d", &N);
    for (int j = 1; j <= N; ++j) {
        printf("%d ", j);
        scanf("%d ", &M);
        getline(cin, word);
        for (int i = 1; i <= (int)word.size(); ++i)
            if (i != M) printf("%c", word[i - 1]);
        printf("\n");
    }
}