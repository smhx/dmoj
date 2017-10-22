#include <cstdio>
#include <cmath>

using namespace std;

bool matches(int a, int b) {
    if (a==0 && b==0) return true;
    if (a==6 && b==9) return true;
    if (a==9 && b==6) return true;
    if (a==1 && b==1) return true;
    if (a==8 && b==8) return true;
    return false;
}

bool rot(int k) {
    int n = (int)log10(k);
    // number of digits is n+1
    int low = 0;
    int high = n;
    
    while (low <= high) {
        int a = (int) (k % (int)pow(10, low+1) ) / pow(10, low);
        int b = (int) (k % (int)pow(10, high+1) ) / pow(10, high);
        if (!matches(a, b)) return false;
        low++;
        high--;
    }
    return true;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    int n = 0;
    for (int i = N; i <= M; i++) {
        if (rot(i)) n++;
    }
    printf("%d\n", n);
    return 0;
}