/*input
3
10
20
30
99
1
50
88
3
88
2
77
*/
#include <cstdio>
#include <list>
using namespace std;

inline int round(double x) {
    return (x-(double)(int)x >= 0.5) ? (int)x+1 : (int)x;
}

int main() {
    list<double> l;
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        double x; scanf("%lf", &x);
        l.push_back(x);
    }

    while (1) {
        int cmd; scanf("%d", &cmd);
        if (cmd==77) {
            for (auto x : l) printf("%d ", round(x));
            printf("\n");
            return 0;
        }
        int pos; scanf("%d", &pos);
        auto it = l.begin();
        for (int i = 0; i < pos-1; ++i) ++it;

        if (cmd==99) {
            // split
            double percent; scanf("%lf", &percent);
            double lft = percent / 100.0 * (*it);
            double rt = *it - lft;
            l.insert(it, lft);
            *it = rt;
        } else {
            if (it==l.end()) return !printf("ERROR END\n");
            double sum = *it+*(++it);
            l.erase(it);
            *(--it)=sum;
        }
    }
}