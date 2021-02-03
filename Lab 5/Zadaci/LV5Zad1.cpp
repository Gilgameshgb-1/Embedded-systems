#include "mbed.h"
#include "C12832.h"
#include "stdio.h"

C12832 lcd(SPI_MOSI, SPI_SCK, SPI_MISO, p8, p11);

Ticker t1;

InterruptIn dugmeSS(p8);
InterruptIn dugmeR(p9);

int zastavica = 0;
float stopanje = 0;

void STARTSTOP() {
    zastavica = !(zastavica);
}

void RESET(){
    lcd.cls();
    stopanje = 0;
    zastavica = 0;
}

void BROJANJEPRIKAZ(){
    if(zastavica == 1) stopanje += 0.1;
    lcd.locate(0,3);
    lcd.printf("%04.1f",stopanje);
}

int main() {
    while(1) {
        dugmeSS.rise(&STARTSTOP);
        dugmeR.rise(&RESET);
        t1.attach(&BROJANJEPRIKAZ,0.1);
        wait_ms(100);
    }
}