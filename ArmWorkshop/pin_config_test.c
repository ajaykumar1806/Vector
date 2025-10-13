#include "pin_func_defines.h"
#include "pin_config_defines.h"
int main() {
while(1) {
//cfg port0 pin0 as func 2
cfgpinfunc(0,0,PIN_FUNC2);
//cfg port0 pin5 as func 4
cfgpinfunc(0,5,PIN_FUNC4);
//cfg port0 pin15 as func 3
cfgpinfunc(0,15,PIN_FUNC3);
//cfg port0 pin9 as func 4
cfgpinfunc(0,9,PIN_FUNC4);
}
}
