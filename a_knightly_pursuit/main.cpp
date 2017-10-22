#include <cstdio>
#include <queue>
#include <utility>
using namespace std;

#define mp make_pair
const int MAX = 1<<20;
int n, r, c, pr, pc, kr, kc, minW, minS, fillRow=0, board[101][101];
queue< pair<int, int> > bag = queue< pair<int, int> >();

const pair<int, int> kMoves[8] = {
    mp(1, 2), mp(2, 1), mp(1, -2), mp(2, -1),
    mp(-1,-2), mp(2,1), mp(-1, 2), mp(-2, 1)
};

int main() {
    scanf("%d", &n);
    while (n--) {
        scanf("%d%d%d%d%d%d", &r, &c, &pr, &pc, &kr, &kc);
        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= c; j++) {
                board[i][j]=-1;
            }
        }
        bag = queue< pair<int, int> >();
        fillRow=0;
        minS = MAX;
        minW = MAX;
        board[kr][kc] = 0;
        bag.push( mp(kr, kc) );
        while (!bag.empty() ) {
            pair<int,int> front = bag.front();
            bag.pop();
            if (front.second==pc && front.first > pr) {
                ++fillRow;
                int x=board[front.first][front.second], y=front.first-pr;
                if (x <= y) {
                    if (x%2==y%2 && front.first != r) {
                        minW = min(minW, y);
                    } else if (x%2 != y%2) {
                        minS = min(minS, y-1);
                    }
                }
            }

            if (fillRow==r-pr) break;

            for (auto move : kMoves) {
                int x = front.first+move.first, y=front.second+move.second;
                if (x < 0 || x > r || y<0 || y> c ) continue;
                if (board[x][y] != -1) continue;
                board[x][y] = board[front.first][front.second]+1;
                bag.push(mp(x, y));
            }
        }
        if (minW != MAX) {
            printf("Win in %d knight move(s).\n", minW);
        } else if (minS != MAX) {
            printf("Stalemate in %d knight move(s).\n", minS);
        } else {
            printf("Loss in %d knight move(s).\n", r-pr-1);
        }
    }
    return 0;
}