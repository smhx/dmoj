#include <cstdio>
#include <vector>
typedef long long ll;

using namespace std;

ll pow(int b, int e) {
    if (e) {
        int g = pow(b, e >> 1);
        return e%2 ? b * g * g : g * g;
    } 
    return 1;
}

ll powBottomUp(int b, int e) {
    // dp[i] := pow(b, e >> i).
    // dp[]
    // build e up from right to left.
    int build = 1;
}