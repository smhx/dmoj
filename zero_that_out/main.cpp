#include <cstdio>
#include <stack>
int K;
std::stack<int> s;
int main() {
    freopen("s1/s1.5.in", "r", stdin);
    scanf("%d", &K);
    while (K--) {
        int x;
        scanf("%d", &x);
        if (x==0) s.pop();
        else s.push(x);
    }
    int sum = 0;
    while (!s.empty() ){
        sum += s.top(); s.pop();
    }
    printf("%d\n", sum);
}