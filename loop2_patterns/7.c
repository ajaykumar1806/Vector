#include <stdio.h>
int main() {
        int num;
        printf("Enter the number: ");
        scanf("%d",&num);
        for(int i = 1;i<=(num*2)+1;i++) {
                for(int j=1;j<num*2;j++) {
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

