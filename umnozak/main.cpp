#include <cstdio>
typedef long long ll;
ll A, B; int cnt=0;
ll digp(int x) {
    ll p=1; ll tenpow = 10;
    while (x != 0) {
        p *= x%10;
        x/=10;
    }
    return p;
}
inline ll sp(int x) {
    return x*digp(x);
}
int main() {
    scanf("%lld%lld", &A, &B);
    for (int i = 1; i <= B; ++i) {
        ll s = sp(i);
        if (A <= s && s <= B) cnt++;
    }
    printf("%d\n", cnt);
}