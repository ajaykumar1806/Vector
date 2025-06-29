#include <stdio.h>
int main() {
        int num;
        printf("Enter the number: ");
        scanf("%d",&num);
        int ch = 5;
        for(int i = 1;i<=num;i++) {
                for(int j=1;j<=num;j++) {
                        if(i+j <= num+1) {
				if(i%2 == 1) {
                                	printf("%d ",ch);
				}
				else
					printf("* ");
                        }
                }
                printf("\n");
		ch -= 1;
        }
}

