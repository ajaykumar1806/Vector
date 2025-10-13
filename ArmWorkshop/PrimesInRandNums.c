#include <stdlib.h>
#include <math.h>
int isPrime(int);
signed int arr[5],num,i,seed,n;
int main() {
	n = 5;
	while(n)
	{
		num = (rand() % 100 ) ;
		srand(seed++);
		if(isPrime(num)) {
			arr[i] = num;
			i++;
		}
		n--;
	}
}

int isPrime(int num) {
	int i;
	for(i = 2;i<=(num / 2) + 1;i++) {
		if(num % i == 0) {
			return 0;
		}
	}
	return 1;
}
