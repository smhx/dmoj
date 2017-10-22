#include <cstdio>
#include <cstring>

char str[3][1000];

int N;

int main() {
    scanf("%d", &N);
    
    while (N--) {
        scanf(" %s %s %s", str[0], str[1], str[2]);
        if (strcmp(str[0], str[1])==0 || strcmp(str[0], str[2])==0) 
            printf("%s\n", str[0]);
        else if (strcmp(str[1], str[2])==0)
            printf("%s\n", str[1]);
        else printf("???\n");
    }
}