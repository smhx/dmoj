#include <iostream>

double p = 1;
int main() {
    int G;
    scanf("%d", &G);
    for (int i = 0; i < G; ++i) {
        int e, ppl; scanf("%d%d", &e, &ppl);
        p *= double(ppl-e) / double(ppl);
    }
    std::cout << p << std::endl;
}