#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>
using namespace std;
typedef pair<int, int> ii;
int F, N;
ii food[1005];
unordered_map<string, int> s;
int main() {
    cin >> F;
    for (int i = 0; i < F; ++i) {
        string str; int energy;
        cin >> str >> energy;
        s[str] = energy;
    }
    cin >> N;
    for (int i = 0; i < N; ++i) {
        string str; int dist;
        cin >> str >> dist;
        food[i] = ii(dist, s[str]);
    }

    sort(food, food+N);
    int x = 0, energy = 0, eaten = 0;
    for (int i = 0; i < N; ++i) {
        int go = (energy > 0) ? energy : 0;
        if (food[i].first <= x+go) {
            ++eaten;
            energy = energy-(food[i].first-x) + food[i].second;
            x = food[i].first;
        }
    }
    printf("%d\n", eaten);
}