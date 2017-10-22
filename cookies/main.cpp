#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#define MAXN 10

int N;

struct frac {
    int a, b;
    frac() : a(0), b(1) {}
    frac(int x) : a(x), b(1) {}
    bool operator<(const frac& f) const {
        return a*f.b < b * f.a;
    }
    double evaluate() {
        return double(a)/double(b);
    }
} diasqrd, side[3];

struct point {
    int x, y;
} pnts[MAXN];


int dsqrd(point a, point b) {return (a.x-b.x)*(a.x-b.x) + (a.y-b.y) * (a.y-b.y);}

int area(point x, point y, point z) {
    return abs( ( (y.x-x.x) * (z.y-x.y) ) - ( (z.x-x.x) * (y.y-x.y) ) );
}

int main() {
    freopen("data.txt", "r", stdin);
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) 
        scanf("%d%d", &pnts[i].x, &pnts[i].y);

    if (N==2) {
        printf("%.2f\n", sqrt(dsqrd(pnts[0], pnts[1])) );
        return 0;
    }
    for (int i = 0; i < N-2; ++i) {
        for (int j = i + 1; j < N-1; ++j) {
            for (int k = j + 1; k < N; ++k) {
                side[0] = frac(dsqrd(pnts[i], pnts[j]) );
                side[1]= frac(dsqrd(pnts[i], pnts[k]));
                side[2] = frac(dsqrd(pnts[j], pnts[k]));
                
                std::sort(side, side+3);
                // for (int u = 0; u < 3; ++u) printf("side[%d]=%d\n", u, side[u].a);
                
                if (-side[2].a+side[1].a+side[0].a <= 0 && diasqrd < side[2]) {
                    diasqrd = side[2];
                    // printf("setting to side[2] diasqrd\n");
                }
                else {
                    // printf("in circum\n");
                    frac dsqaured;
                    dsqaured.a = side[0].a * side[1].a * side[2].a;
                    int A = area(pnts[i], pnts[j], pnts[k]);
                    // printf("area=%d\n", A);
                    dsqaured.b = A*A ;
                    if ( diasqrd < dsqaured) {
                        // printf("setting to diasqrd\n");
                        diasqrd = dsqaured;
                    }
                } 
            }
        }
    }
    double ans = sqrt( diasqrd.evaluate() );
    // if (ans==0) {
    //     printf("%d", N);
    //     for (int i = 0; i < N; ++i) printf(":%d,%d", pnts[i].x, pnts[i].y);
    // }
    printf("%.2f\n", sqrt( diasqrd.evaluate() ) );
}