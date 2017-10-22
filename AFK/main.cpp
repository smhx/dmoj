#include <cstdio>
#include <queue>
#include <utility>

using namespace std;

int t, fp[51][51];
const pair<int, int> corners[4] = {make_pair(0, 1), make_pair(1, 0), make_pair(0, -1), make_pair(-1, 0)};

int main() {
    scanf("%d", &t);
    while (t--) {
        int l, w;
        scanf("%d%d", &l, &w);
        pair<int, int> src, dest;
        char in;
        for (int i = 0; i < w; i++) {
            getchar();
            for (int j = 0; j < l; j++) {
                scanf("%c", &in);
                if (in == 'X') fp[i][j] = -1;
                else fp[i][j] = -2;
                if (in == 'C') src = make_pair(i, j);
                else if (in == 'W') dest = make_pair(i, j);
            }
        }
        queue< pair<int, int> > bag = queue< pair<int, int> >();
        bag.push(src);
        fp[src.first][src.second] = 0;
        while ( !bag.empty() ) {
            int x = bag.front().first, y = bag.front().second;
            if (bag.front() == dest) {
                if (fp[x][y] < 60) printf("%d\n", fp[x][y]);
                else printf("#notworth\n");
                break;
            }
            if (fp[x][y] >= 60) {
                printf("#notworth\n");
                break;
            }
            bag.pop();
            for (int i = 0; i < 4; i++) {
                int dx = corners[i].first, dy = corners[i].second;
                if (x + dx >= w || x + dx < 0 || y + dy >= l || y + dy < 0) continue;
                if (fp[x + dx][y + dy] > -2) continue;
                fp[x + dx][y + dy] = fp[x][y] + 1;
                bag.push( make_pair(x + dx, y + dy) );
            }
        }
        if (bag.empty()) {
            printf("#notworth\n");
        }
    }
}

