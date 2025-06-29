#include <stdio.h>
int main() {
	int num;
	printf("Enter the number: ");
	scanf("%d",&num);
	for(int i = 1;i <= num;i++) {
		for(int j = 1;j <= num;j++) {
			if(j >= i) {
				printf("* ");
			}
			else {
				printf(" ");
			}
		}
		printf("\n");
	}
}
