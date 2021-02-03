#include "mbed.h"

DigitalOut led = LED1;

int main() {
    double epsilon = 0.0001;
    double t = 1;
    double k = 0.9/30;
    double duzinaon = t;
    double duzinaoff = t;
    while(1) {
        duzinaon += t*k;
        duzinaoff += -t*k;
        led = 0;
        wait(duzinaon);
        if(fabs(1.9-duzinaon) < epsilon || fabs(0.1 - 			duzinaon) < epsilon) {
            k = -k;
        }
        led = 1;
	wait(duzinaoff);
    }
}