#include "mbed.h"

BusIn kolone(dp9,dp10,dp11,dp13);
BusOut redovi(dp18,dp17,dp15,dp16);

DigitalOut digit1(dp27);
DigitalOut digit2(dp24);
DigitalOut digit3(dp25);

BusOut segment(dp23,dp24,dp25,dp26,dp27,dp5,dp6,dp28,dp1,dp2,dp4);

unsigned char tastatura[4][4] = {
    '1','2','3','A',
    '4','5','6','B',
    '7','8','9','C',
    '*','0','#','D',   
};

unsigned char lookupTabela(unsigned char num){
    switch(num){
        case 0 : num = 0xC0 ; break;
        case 1 : num = 0xF9 ; break;
        case 2 : num = 0xA4 ; break;
        case 3 : num = 0xB0 ; break;
        case 4 : num = 0x99 ; break; 
        case 5 : num = 0x92 ; break; 
        case 6 : num = 0x82 ; break; 
        case 7 : num = 0xF8 ; break;
        case 8 : num = 0x80 ; break;
        case 9 : num = 0x98 ; break;
    }
    return num;    
}

void PrikazBroja(int broj){
    for(int i =2;i>=0;i--){
        switch(i){
            case 0 : digit3 = 0; break;
            case 1 : digit2 = 0; break; 
            case 2 : digit1 = 0; break; 
        }
        if(broj>=10 && broj <=999){
            segment = lookupTabela(broj\%10);
            broj/=10;
        }else if(broj<10 && broj<=999){
            segment = lookupTabela(broj);
        }
        wait(0.041);
        digit3 = 1;
        digit2 = 1; 
        digit1 = 1;
    }
    
}

int main() {
    unsigned char broj = 0;
while(1){
    for(int i = 0;i<=3;i++){
        redovi[i] = 1;
            for(int j = 0;j<=3;j++){
                if(kolone[j]==1){
                    if(i<=2 && j<=2){
                        broj += tastatura[i][j];
                        PrikazBroja(broj); 
                        broj*=10; 
                    }else if(i == 3 && j == 1){
                        PrikazBroja(broj); 
                        broj*=10;
                    }else if(i == 2 && j == 3){
                        broj = 0;
                        PrikazBroja(broj);
                    }
                }
            }
redovi[i]=0;
    }
}
}