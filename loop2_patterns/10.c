#include <stdio.h>
int main() {
        int num;
        printf("Enter the number: ");
        scanf("%d",&num);
	int flag;
        for(int i = num+1;i>=1;i--) {
                for(int j=-num;j<=num;j++) {
			flag = j; if(flag < 0) flag = -flag;
                        if(i+flag > num) {
                                printf("%d ",(num+1)-flag);
                        }
                        else {
                                printf("  ");
                        }
                }
                printf("\n");
        }
}

