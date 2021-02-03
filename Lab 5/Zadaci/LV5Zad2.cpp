#include "mbed.h"

Ticker t1;

BusOut prikaz1 (p8, p7, p6, p5);
BusOut prikaz2 (p12, p11, p10, p9);

InterruptIn taster(BUTTON1);

const float T(2);
int brojac1(0);
int brojac2(0);

int zastavica = 0;

void STARTSTOP(){
    zastavica = !(zastavica);
}

void PromjenaPrikaz(){
    if(zastavica == 1){
        brojac2 = (brojac2 +1)%16;
        prikaz2 = brojac2;
    }
    brojac1 = (brojac1 +1)%16;
    prikaz1 = brojac1;
}

int main () {
    prikaz1 = brojac1 ;
    prikaz2 = brojac2 ;
    taster.rise(&STARTSTOP);
    taster.fall(&STARTSTOP);
    t1.attach(&PromjenaPrikaz, T);
    wait(T);
}