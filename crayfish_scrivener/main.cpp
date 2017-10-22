#include <cstdio>
#include <vector>
using namespace std;
#define MAX 1000005
#define LOG 22

int word[MAX][LOG], len[MAX];
char letter[MAX];
vector<int> moves;
int curnode = 1, nodecnt=0;

void Init() {
    nodecnt = 1, curnode = 1;
    len[1]=0, letter[1] = '\0';
    moves.push_back(1);
}
void TypeLetter(char L) {
    letter[++nodecnt] = L;
    word[nodecnt][0] = curnode;
    len[nodecnt] = 1 + len[curnode];
    curnode = nodecnt;
    for (int j = 1; j < LOG; ++j) word[curnode][j] = word[ word[curnode][j-1] ][j-1];
    moves.push_back(curnode);
}
void UndoCommands(int U) {
    int target = moves[moves.size()-1-U];
    moves.push_back(target);
    curnode = target;
}
char GetLetter(int P) {
    int anc = len[curnode]-P-1;
    int x = curnode;
    for (int j = LOG-1; j >= 0; --j) if (anc&(1<<j)) x=word[x][j];
    return letter[x];
}

int main() {
    int N; 
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        int q;
        scanf("%d", &q);
        if (q==1) {
            char c; scanf(" %c", &c); TypeLetter(c);
        } else if (q==0) {
            int P; scanf("%d", &P); printf("%c\n", GetLetter(P));
        } else if (q==2) {
            int P; scanf("%d", &P); UndoCommands(P);
        }
    }
}

