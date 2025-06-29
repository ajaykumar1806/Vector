#include <stdio.h>
int main() {
    int i, j;
    int num;
    printf("Enter the number: ");
    scanf"%d",&num);
    for(i = 1; i <= n; i++) {
        for(j = 1; j <= n - i; j++) {
            printf(" ");
        }

        // Print characters with '*'
        for(j = 1; j <= i; j++) {
            printf("%c", 'A' + j - 1);
            if(j != i) {
                printf("*");
            }
        }

        printf("\n");
    }

    return 0;
}i

