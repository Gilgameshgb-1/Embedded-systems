#include "mbed.h"

#define dp23 P0_0 

DigitalOut pin14 = dp14;
BusOut diode(dp23, dp24, dp25, dp26, dp27, dp5, dp6, dp28);

int main() {
    pin14 = 0;
    int brojac = 1;
    while(1) {
        diode = brojac;
        wait(1);
        brojac *= 2;
        if(brojac >= 256)
            brojac = 1;
    }
}