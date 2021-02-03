#include "mbed.h"

#define dp23 P0_0 

DigitalOut pin14 = dp14;
BusOut diode(dp23, dp24, dp25, dp26, dp27, dp5, dp6, dp28);
DigitalIn taster1 = dp1;

int main() {
    pin14 = 0;
   int brojac = 0;
    while(1) {
        diode = brojac;
        if(taster1) {
            brojac--;
        }else {
            brojac++;
        }
        wait(1);
        
    }
}