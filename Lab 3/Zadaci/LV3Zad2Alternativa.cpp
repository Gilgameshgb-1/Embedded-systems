#include "mbed.h"
#include "stm32f413h_discovery_ts.h"
#include "stm32f413h_discovery_lcd.h"
#include "string"
#include "sstream"

AnalogIn LM35(p15);

int main() {
    int NAPON;
    int tempC;
    int vrijeme = 0;
    int xnovo = 0;
    int ynovo = 0;
    int xstaro = 10;
    int ystaro = 220;
    while(1) {
        BSP_LCD_SetFont(&Font12);
        BSP_LCD_DisplayStringAt(40, 5, (uint8_t *)"Temperatura(C)", LEFT_MODE);
        BSP_LCD_DisplayStringAt(170, 225, (uint8_t *)"Sekunde(s)", LEFT_MODE);
        BSP_LCD_DisplayChar (10, 10, 51);
        BSP_LCD_DisplayChar (18, 10, 51);
        BSP_LCD_DisplayChar (26, 10, 48);
        BSP_LCD_DisplayChar (10, 120, 49);
        BSP_LCD_DisplayChar (18, 120, 53);
        BSP_LCD_DisplayChar (26, 120, 48);
        std::string napSTR = "Napon: ";
        std::string tempSTR = "Temp: ";
        std::string vrijemeSTR = "Vrijeme: ";
        BSP_LCD_Init();
        tempC = LM35.read()*100*3.3;
        NAPON = LM35.read()*1000*3.3;
        //ispisivanje napona
        napSTR+=std::to_string(NAPON);
        napSTR+=" mV";
        unsigned char *val=new unsigned char[napSTR.length()+1];
        strcpy((char *)val,napSTR.c_str());
        BSP_LCD_SetFont(&Font12);
        BSP_LCD_DisplayStringAt(70, 5, val, CENTER_MODE);
        //ispisivanje temperature
        tempSTR+=std::to_string(tempC);
        tempSTR+=" C";
        unsigned char *val1=new unsigned char[tempSTR.length()+1];
        strcpy((char *)val1,tempSTR.c_str());
        BSP_LCD_DisplayStringAt(75, 15, val1, CENTER_MODE);
        //timer
        vrijemeSTR+=std::to_string(vrijeme);
        vrijemeSTR+=" s";
        unsigned char *val2=new unsigned char[vrijemeSTR.length()+1];
        strcpy((char *)val2,vrijemeSTR.c_str());
        BSP_LCD_DisplayStringAt(75, 25, val2, CENTER_MODE);
        //grafik
        BSP_LCD_DrawHLine (0, 220, 220);
        BSP_LCD_DrawVLine (10, 10, 220);
        xnovo = 10 + vrijeme * 5;
        ynovo = 220 - tempC * 2/(3.3); 
        BSP_LCD_DrawLine (xstaro, ystaro,xnovo,ynovo);
        if(ynovo!=ystaro) BSP_LCD_FillCircle(xstaro, ystaro, 2);
        xstaro = xnovo;
        ystaro = ynovo;
        //wait-ovi
        wait_ms(1000);
        vrijeme++;
    }
}
