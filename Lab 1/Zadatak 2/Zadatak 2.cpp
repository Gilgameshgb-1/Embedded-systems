  #include "mbed.h"

DigitalOut myled1 = LED1;
DigitalOut myled2 = LED2;
DigitalOut myled3 = LED3;

int main() {
    int t = 1000;
	int kontrola = 1;
    while(1) {
        myled3 = 1;
        myled1 = 0;
        wait_ms(t);
        myled1=1;
        myled2=0;
        wait_ms(t);
        myled2=1;
        myled3=0;
        wait_ms(t);
        if(kontrola == 1){
		t = t-100;
	if(t < 100){
		t= 100;
		kontrola = 0;
		}
	}
    }
}