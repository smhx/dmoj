#include <cstdio>

int main() {
	int a, b;
	scanf("%d %d", &a, &b);
	
	for (int k = 1; k < b; k++) {
		if (a*k % b==1) {
			printf("%d\n", k);
			return 0;
		}
	}
	printf("No such integer exists.\n");
	return 0;
}