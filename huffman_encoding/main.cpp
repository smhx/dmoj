#include <cstdio>
#include <string>
#include <cstring>
#define KEY_SIZE 60
#define CODE_SIZE 300
#define MAP_SIZE 20
int N, skip[KEY_SIZE]; 

char code[CODE_SIZE];
char letter[MAP_SIZE];
char key[MAP_SIZE][KEY_SIZE];

int main() {
    // freopen("data.txt", "r", stdin);
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf(" %c %s", &letter[i], key[i]);
    }
    
    scanf(" %s", code);
    for (int i = 0; i < strlen(code); ) { 
        for (int k = 0; k < N; ++k) { 
            if (!skip[k] && i+strlen(key[k])-1 < strlen(code)) {
                bool matches = true;
                for (int j = 0; j < strlen(key[k]); ++j) { 
                    if (key[k][j] != code[i+j]) {
                        matches = false; 
                        skip[k] = 1;
                        break;
                    }
                }
                if (matches) {
                    printf("%c", letter[k]);
                    i += strlen(key[k]);
                    memset(skip, 0, sizeof skip);
                    break;
                }
            }
            
        }
    }
    printf("\n");

}