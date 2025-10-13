#include <LPC21XX.H>
void delayUs(int num) {
  int i;
  for(i = 1;i<= num*12000;i++);
}
#define BITPOS 7
int main() {
  IODIR0 |= 1<<BITPOS;
  while(1) {
  IOSET0 = 1<<BITPOS;
  delayUs(100);
  IOCLR0 = 1<<BITPOS;
  delayUs(100);
  }
}
