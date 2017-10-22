#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>
#define MAXN 400005
typedef unsigned long long ll;
using namespace std;
int N; ll H[MAXN], f[MAXN], sum=0;
vector<ll> s;

int main() {
    // freopen("data.txt", "r", stdin);
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) scanf("%lld", H+i);
    for (int i = 0; i < N; ++i) {

        while (!s.empty() && s.back() < H[i]) s.pop_back(), ++f[i];

        if (!s.empty()) {
            if (s.back() != H[i]) ++f[i];
            else {
                pair<vector<ll>::iterator, vector<ll>::iterator> x = equal_range(s.begin(), s.end(), H[i], greater<int>() );
                f[i] += (x.second-x.first);
                if (x.first != s.begin()) ++f[i];
            }
        }

        sum += f[i];
        s.push_back(H[i]);
    }
    printf("%llu\n", sum);
    return 0;
}   

