#include "mbed.h"
#include "C12832.h"

C12832 lcd(SPI_MOSI, SPI_SCK, SPI_MISO, p8, p11);
AnalogIn ainOTPOR(p15);
AnalogIn ainNAPON(p16);
DigitalIn tasterNAPON(p8);
DigitalIn tasterOTPOR(p9);

int main() {
    float otpor = 0;
    float napon = 0;
    int kontrola = 0;
    float struja = 0.00033;
    while (1) {
        otpor = ainOTPOR.read()*3.3/struja;
        napon = ainNAPON.read()*3.3;
        lcd.locate(0,3);
        if(kontrola == 0){
            lcd.cls();
            lcd.printf("Napon na ulazu je %f V",napon);
        }else if(kontrola == 1){
            lcd.cls();
            lcd.printf("Otpor na ulazu je %f Ohma",otpor);
        }
        if(tasterNAPON) kontrola = 0;
        else if(tasterOTPOR) kontrola = 1;
        wait_ms(0.1);
    }
}
