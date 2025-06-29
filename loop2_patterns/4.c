#include <stdio.h>
int main() {
	int num;
	char ch = 'A';
	printf("Enter the number: ");
	scanf("%d",&num);
	for(int i = 1;i<=num;i++) {
		for(int j=1;j<=num;j++) {
			if(i >= j) {
				printf("%c ",ch++);
			}
			else {
				printf(" ");
			}
		}
		printf("\n");
	}
}
