#include <cstdio>

int main() {
    int r, g, b;
    scanf("%d%d%d", &r, &g, &b);
    int hex = 0xffffff ^ ( (r << 16) + (g << 8) + b);
    int newr = (hex & ((1<<24)-1)) >> 16;
    int newg = (hex & ((1<<16)-1) ) >> 8;
    int newb = hex & ( (1<<8)-1);
    printf("(%d, %d, %d)\n", newr, newg, newb);
}