/*input
10
Infront
2
*/
#include <cstdio>

char in[50];
int N1, N2;

int main() {
	scanf("%d %s %d", &N1, in, &N2);

	if (in[0]=='I') {
		printf("%d\n", N1-N2);
	} else {
		printf("%d\n", N1+N2);
	}
}