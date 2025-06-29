#include <stdio.h> 
int main() {
	int num;
	printf("Enter the input: ");
	scanf("%d",&num);
	for(int i = 1;i <= num; i++) {
		for(int j = 1;j <= num;j++) {
			if(i >= j) {
				if((i + j) % 2 == 0) {
					printf("1");
				}
				else {
					printf("0");
				}
			}
			else {
				printf(" ");
			}
		}
		printf("\n");
	}
}

