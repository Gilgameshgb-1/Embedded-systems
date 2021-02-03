#include "mbed.h"

DigitalIn taster1(dp1);
DigitalIn taster2(dp2);
DigitalOut digit1(dp23);
DigitalOut digit2(dp24); // cifre
DigitalOut digit3(dp25);

BusOut segment(dp18,dp4,dp28,dp6,dp5,dp27,dp26);

/*unsigned char lookupTabela(unsigned char num){
    switch(num){
        case 0 : num = 0x3F ; break;
        case 1 : num = 0x06 ; break;
        case 2 : num = 0x5B ; break;
        case 3 : num = 0x4F ; break;
        case 4 : num = 0x66 ; break; // basically lookup tabela, fazon je samo kad dobijemo neki broj pretvorimo u hex i vratimo nazad
        case 5 : num = 0x6D ; break; // u principu dosta brze nego da pisemo upali mi segment A,B,C,D sto bi bilo svakako potrebno za 9 cifri uraditi
        case 6 : num = 0x7D ; break; // ovo je lookup ukoliko je u pitanju zajednicka katoda
        case 7 : num = 0x27 ; break;
        case 8 : num = 0x7F ; break;
        case 9 : num = 0x6F ; break;
    }
    return num;    
}*/

unsigned char lookupTabela(unsigned char num){
    switch(num){
        case 0 : num = 0xC0 ; break;
        case 1 : num = 0xF9 ; break;
        case 2 : num = 0xA4 ; break;
        case 3 : num = 0xB0 ; break;
        case 4 : num = 0x99 ; break; // basically lookup tabela, fazon je samo kad dobijemo neki broj pretvorimo u hex i vratimo nazad
        case 5 : num = 0x92 ; break; // u principu dosta brze nego da pisemo upali mi segment A,B,C,D sto bi bilo svakako potrebno za 9 cifri uraditi
        case 6 : num = 0x82 ; break; // ovo je lookup ukoliko je u pitanju zajednicka ANODA
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
            case 1 : digit2 = 0; break; // u principu palimo digit po digit, zasto? iz razloga jer ljudsko oko prima ~25 frejmova po sekundi mi samo brzo
            case 2 : digit1 = 0; break; // palimo ove segmente, palimo ih 0 zbog (common anode) tipa dekodera
        }
        if(broj>=10){
        segment = lookupTabela(broj%10);//palimo cifru
            broj/=10;
        }else{
	 segment = lookupTabela(broj);
	}
        wait(0.041); // holdamo cifru imamo otprilike neki 100ms dok primijetimo neko titranje
        digit3 = 1;
        digit2 = 1; // resetujemo na off
        digit1 = 1;
    }
    
}

int main() {
    int t1 = 0; // pomocu t1 i t2 trackamo koje su nam uzlazne ivice
    int t2 = 0;
    int c = 0;
    
    while(1){
        if(t1 == 0 && dp1 == 1){
            t1 = 1;
            c++; 
            if(c <= 999) {PrikazBroja(c);}// if t1 = 0 && dp = 1 je u biti provjera uzlazne ivice kao u smislu prethodna je bila 0 a sad je 1  to je uzlazno onda radi ispis cifre
            else{
                c = 1;
                PrikazBroja(c);
            }
            }else if(t2 == 0 && dp2 == 1){ // if uvjeti oko broja  <=999 i < 0 su granicni slucajevi cisto da se ne bi cudno ponasao nas display, iako bismo mogli reci da je ovo cudno ponasanje 
                t2 = 1;
                c--;
                if(c<0) {c = 999; PrikazBroja(c);} else {PrikazBroja(c);}
            }
        if(dp1 == 0) t1 = 0; // resetujemo "brojac ivice"
        if(dp2 == 0) t2 = 0;
        PrikazBroja(c); // cisto onako prikazujemo broj (just in case da nije niko nista pritisnuo)
    }
}
