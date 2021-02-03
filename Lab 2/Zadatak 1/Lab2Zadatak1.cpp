#include "mbed.h"

BusIn kolone(dp9,dp10,dp11,dp13);
BusOut redovi(dp16,dp15,dp17,dp18);
BusOut myleds(LED1,LED2,LED3,LED4,LED5,LED6,LED7,LED8);

int main() {
    int brojac = 0; 
    for(int i = 0;i<4;i++) myleds[i]=1;
    while(1){
        for(int i = 0;i<=3;i++){
            redovi[i]=1;u
            for(int j = 0;j<=3;j++){
                if(kolone[j]==1){
                        if(i<2 && j<=2){
                        while(kolone[j]==1)myleds[brojac] = 0; 
                        myleds[brojac] = 1; 
                        }else if(i == 2 && j<2){
                            while(kolone[j]==1)myleds[brojac]=0;
                            myleds[brojac]=1;
                        }
                    }
                }
                if (j<=2) brojac++
            }
	if(i==3){
            brojac = 0;
redovi[i] = 0 // resetujemo red na 0}
    }
}