#include "mbed.h"
#include "stm32f413h_discovery_ts.h"
#include "stm32f413h_discovery_lcd.h"
#include "string"
#include "sstream"
#include <cstdlib>
#include <vector>
 
TS_StateTypeDef TS_State = { 0 };
 
DigitalIn igrac1F(p5);
DigitalIn igrac2F(p6);
 
DigitalIn igrac1B(p7);
DigitalIn igrac2B(p8);
 
 
class Brod{
    int x,y,r,vel;
    int score;
public:
    Brod(int x){
        this->x = x;
        this->score = 0;
        this->respawn();
        this->r = 11;
        this->vel = 3;
    }
    void respawn(){
        this->y = 220;
    }
    void gore(){
        this->y-=5;
    }
    void dole(){
        this->y+=5;
    }
    void addingPoint(){
        score++;
    }
    void display(){
        if(y>=12){
    //desni dio broda        
    BSP_LCD_DrawVLine(x+vel,y+r,vel);
    BSP_LCD_DrawHLine(x+vel,y+r+vel,vel);
    BSP_LCD_DrawVLine(x+vel*2,y+r,vel);
    BSP_LCD_DrawHLine(x+vel*2,y+r,vel);
    BSP_LCD_DrawLine(x+vel*3,y+r,x+vel,y+(r-vel*2));
    BSP_LCD_DrawVLine(x+vel,y-(r-vel*2),r);
    BSP_LCD_DrawHLine(x+vel,y-(r-vel*2),vel);
    BSP_LCD_DrawLine(x+vel*2,y-(r-vel*2),x,y-r);
   
    //lijevi dio broda
    BSP_LCD_DrawHLine(x-vel,y+r,vel);
    BSP_LCD_DrawVLine(x-vel,y+r,vel);
    BSP_LCD_DrawHLine(x-vel*2,y+r+vel,vel);
    BSP_LCD_DrawVLine(x-vel*2,y+r,vel);
    BSP_LCD_DrawHLine(x-vel*3,y+r,vel);
    BSP_LCD_DrawLine(x-vel*3,y+r,x-vel,y+(r-vel*2));
    BSP_LCD_DrawVLine(x-vel,y-(r-vel*2),r);
    BSP_LCD_DrawHLine(x-vel*2,y-(r-vel*2),vel);
    BSP_LCD_DrawLine(x-vel*2,y-(r-vel*2),x,y-r);
 
    //pocetak bojenja trapeza    
    Point* point1 = new Point();
    Point* point2 = new Point();
    Point* point3 = new Point();
    Point* point4 = new Point();
   
    point1->X = x+vel*3;
    point1->Y = y+r;
    point2->X = x+vel;
    point2->Y = y+r-vel*2;
    point3->X = x-vel;
    point3->Y = y+r-vel*2;
    point4->X = x - vel*3;
    point4->Y = y+r;
   
    Point Trapez[] = {*point1, *point2, *point3, *point4};
    BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
    BSP_LCD_FillPolygon(Trapez,4);
   
    //unutarne bojenje
    point1->X = x+vel*3-3;
    point1->Y = y+r-2;
    point2->X = x+vel-2;
    point2->Y = y+r-vel*2+2;
    point3->X = x-vel+2;
    point3->Y = y+r-vel*2+2;
    point4->X = x - vel*3+3;
    point4->Y = y+r-2;
   
    Point Trapez1[] = {*point1, *point2, *point3, *point4};
    BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
    BSP_LCD_FillPolygon(Trapez1,4);
   
    //kraj bojenja trapeza
 
    //pocetak bojenja trougla
    point1->X = x-vel*2;
    point1->Y = y-(r-vel*2);
    point2->X = x+vel*2;
    point2->Y = y-(r-vel*2);
    point3->X = x;
    point3->Y = y-r;
   
    Point Trougao[] = {*point1, *point2, *point3};
    BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
    BSP_LCD_FillPolygon(Trougao,3);
   
    //manji trougao
    point1->X = x-vel*2+4;
    point1->Y = y-(r-vel*2)-2;
    point2->X = x+vel*2-4;
    point2->Y = y-(r-vel*2)-2;
    point3->X = x;
    point3->Y = y-r+2;
   
    Point Trougao1[] = {*point1, *point2, *point3};
    BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
    BSP_LCD_FillPolygon(Trougao1,3);
    //kraj bojenja trougla
 
    //pocetak bojenja velikog pravougaonika
    point1->X = x-vel;
    point1->Y = y-(r-vel*2)+r;
    point2->X = x+vel;
    point2->Y = y-(r-vel*2)+r;
    point3->X = x+vel;
    point3->Y = y-(r-vel*2);
    point4->X = x-vel;
    point4->Y = y-(r-vel*2);
   
    Point Pravougaonik[] = {*point1, *point2, *point3, *point4};
    BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
    BSP_LCD_FillPolygon(Pravougaonik,4);
 
    //kraj bojenja velikog prevougaonika
   
    //pocetak bojenja manjih kvadratica prvog i drugog
    //prvi
    point1->X = x+vel;
    point1->Y = y+r;
    point2->X = x+vel;
    point2->Y = y+vel+r;
    point3->X = x+vel*2;
    point3->Y = y+vel+r;
    point4->X = x+vel*2;
    point4->Y = y+r;
   
    Point Kvadrat1[] = {*point1, *point2, *point3, *point4};
    BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
    BSP_LCD_FillPolygon(Kvadrat1,4);
    BSP_LCD_SetTextColor(LCD_COLOR_RED);
    BSP_LCD_FillRect(x+vel*2-2,y+vel+r,2,2);
   
    //drugi
    point1->X = x-vel;
    point1->Y = y+r;
    point2->X = x-vel;
    point2->Y = y+vel+r;
    point3->X = x-vel*2;
    point3->Y = y+vel+r;
    point4->X = x-vel*2;
    point4->Y = y+r;
   
    Point Kvadrat2[] = {*point1, *point2, *point3, *point4};
    BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
    BSP_LCD_FillPolygon(Kvadrat2,4);
    BSP_LCD_SetTextColor(LCD_COLOR_RED);
    BSP_LCD_FillRect(x-vel*2+1,y+vel+r,2,2);
    //kraj bojenja manjih kvadratica    
   
   
//dodatak
    BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
    BSP_LCD_FillCircle(x, y, 2);
    }
}
    int Dajscore() const{
        return this->score;
    }
    void resetujScore(){
        this->score=0;
    }
    int Dajx() const{
        return this->x;
    }
    int Dajy() const{
        return this->y;
    }
    int DajR() const{
        return this->r;
    }
};
 
 
float distance(int x1, int y1, int x2, int y2){
    return sqrt(pow(x2 - x1, 2) +  pow(y2 - y1, 2) * 1.0);
};
 
bool randomBool() {
   return rand() > (RAND_MAX / 2);
}  
 
class Debris{
    int x,y,r,vel=2;
    bool isGoingLeft;
public:
 
    Debris(){
        this->r = 9;
        this->resetDebris();
    }
    void resetDebris(){
        this->y = rand() % 120+60;
       
        bool spawnLijevo = randomBool();
       
        //sa lijeve strane
        if(spawnLijevo){
            this->x = -(rand()%150);
            //this->x=0;
            this->isGoingLeft = false;
        }
        else{
            this->x = rand()%240 + 180;
            //this->x=240;
            this->isGoingLeft = true;
        }
    }
   
    void update(){
        if(this->isGoingLeft){
            this->x -= 5;
            }
        else{
            this->x += 5;
            }
       
        if(this->isOffScreen()){
            this->resetDebris();    
        }
    }
   
    bool isOffScreen(){
        if(this->isGoingLeft && this->x < 0){
            return true;
        }
        else if(!this->isGoingLeft && this->x > 239){
            return true;
        }
        return false;
    }
   
    void Display(){
       
    //gornji dio
   
   if(this->isGoingLeft){
       if(x>=r){
    //prednji kraj
    BSP_LCD_DrawLine(x-r,y,x-(r-4),y-(r-5));
    //vertikalna linija
    BSP_LCD_DrawLine(x-(r-5),y-(r-5), x-(r-5),y);
    //duga linija
    BSP_LCD_DrawLine(x-(r-5),y-(r-5), x+(r-3),y-(r-5));
    //vertikalna zadnja
    BSP_LCD_DrawLine(x+(r-3),y-(r-5), x+(r-3), y);
    //rep
    BSP_LCD_DrawLine(x+(r-3),y-3, x+r, y-3);
    BSP_LCD_DrawLine(x+r, y-3, x+r, y);
    // //krilo
    BSP_LCD_DrawLine(x-(r-6),y-(r-5), x+(r-6), y-r);
    BSP_LCD_DrawLine(x+(r-6), y-r, x+(r-2), y-r);
    BSP_LCD_DrawLine(x+(r-2), y-r, x+r-3, y-(r-5));
   
    //donji dio
   
    //prednji kraj
    BSP_LCD_DrawLine(x-r,y,x-(r-4),y+(r-5));
    //vertikalna linija
    BSP_LCD_DrawLine(x-(r-5),y+(r-5), x-(r-5),y);
    //duga linija
    BSP_LCD_DrawLine(x-(r-5),y+(r-5), x+(r-3),y+(r-5));
    //vertikalna zadnja
    BSP_LCD_DrawLine(x+(r-3),y+(r-5), x+(r-3), y);
    //rep
    BSP_LCD_DrawLine(x+(r-3),y+3, x+r, y+3);
    BSP_LCD_DrawLine(x+r, y+3, x+r, y);
    // //krilo
    BSP_LCD_DrawLine(x-(r-6),y+(r-5), x+(r-6), y+r);
    BSP_LCD_DrawLine(x+(r-6), y+r, x+(r-2), y+r);
    BSP_LCD_DrawLine(x+(r-2), y+r, x+r-3, y+(r-5));
   
   
    //bojimo nos
    Point* point1 = new Point();
    Point* point2 = new Point();
    Point* point3 = new Point();
    Point* point4 = new Point();
    point1->X=x-r;
    point1->Y=y;
    point2->X=x-(r-4);
    point2->Y=y-(r-5);
    point3->X=x-(r-4);
    point3->Y=y+(r-5);
    Point curvePoints []= {*point1, *point2, *point3};
    BSP_LCD_SetTextColor(LCD_COLOR_RED);
    BSP_LCD_FillPolygon(curvePoints, 3);
   
   //bojimo tijelo
    point1->X=x-(r-4);
    point1->Y=y-(r-5);
    point2->X=x-(r-4);
    point2->Y=y+(r-5);
    point3->X=x+(r-3);
    point3->Y=y+(r-5);
    point4->X=x+(r-3);
    point4->Y=y-(r-5);
   
    Point curvePoints2 []= {*point1, *point2, *point3, *point4};
    BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
    BSP_LCD_FillPolygon(curvePoints2, 4);
   
    //bojimo prozorcic
    BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
    BSP_LCD_FillCircle(x-vel, y, 2);
   
   
    //krila
    point1->X=x-(r-6);
    point1->Y=y-(r-5);
    point2->X=x+(r-6);
    point2->Y=y-r;
    point3->X=x+r-2;
    point3->Y=y-r;
    point4->X=x+(r-5);
    point4->Y=y+(r-5);
   
    Point curvePoints3 []= {*point1, *point2, *point3, *point4};
    BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
    BSP_LCD_FillPolygon(curvePoints3, 4);
   
    point1->X=x-(r-6);
    point1->Y=y+(r-5);
    point2->X=x+(r-6);
    point2->Y=y+r;
    point3->X=x+r-2;
    point3->Y=y+r;
    point4->X=x+(r-5);
    point4->Y=y+(r-5);
   
    Point curvePoints4 []= {*point1, *point2, *point3, *point4};
    BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
    BSP_LCD_FillPolygon(curvePoints4, 4);
   
    //rep
    point1->X=x+(r-3);
    point1->Y=y-3;
    point2->X=x+r;
    point2->Y=y-3;
    point3->X=x+r;
    point3->Y=y+3;
    point4->X=x+(r-3);
    point4->Y=y+3;
   
    Point curvePoints5 []= {*point1, *point2, *point3, *point4};
    BSP_LCD_SetTextColor(LCD_COLOR_DARKRED);
    BSP_LCD_FillPolygon(curvePoints5, 4);
 }
        }
       
        else{ //s desne strane dolazi
        if(x>=r){    
    //prednji kraj
    BSP_LCD_DrawLine(x+r,y,x+(r-4),y-(r-5));
    //vertikalna linija
    BSP_LCD_DrawLine(x+(r-5),y-(r-5), x+(r-5),y);
    //duga linija
    BSP_LCD_DrawLine(x+(r-5),y-(r-5), x-(r-3),y-(r-5));
    //vertikalna zadnja
    BSP_LCD_DrawLine(x-(r-3),y-(r-5), x-(r-3), y);
    //rep
    BSP_LCD_DrawLine(x-(r-3),y-3, x-r, y-3);
    BSP_LCD_DrawLine(x-r, y-3, x-r, y);
    // //krilo
    BSP_LCD_DrawLine(x+(r-6),y-(r-5), x-(r-6), y-r);
    BSP_LCD_DrawLine(x-(r-6), y-r, x-(r-2), y-r);
    BSP_LCD_DrawLine(x-(r-2), y-r, x-(r-3), y-(r-5));
   
   
    //donji dio
   
    //prednji kraj
    BSP_LCD_DrawLine(x+r,y,x+(r-4),y+(r-5));
    //vertikalna linija
    BSP_LCD_DrawLine(x+(r-5),y+(r-5), x+(r-5),y);
    //duga linija
    BSP_LCD_DrawLine(x+(r-5),y+(r-5), x-(r-3),y+(r-5));
    //vertikalna zadnja
    BSP_LCD_DrawLine(x-(r-3),y+(r-5), x-(r-3), y);
    //rep
     BSP_LCD_DrawLine(x-(r-3),y+3, x-r, y+3);
     BSP_LCD_DrawLine(x-r, y+3, x-r, y);
    // //krilo
    BSP_LCD_DrawLine(x+(r-6),y+(r-5), x-(r-6), y+r);
    BSP_LCD_DrawLine(x-(r-6), y+r, x-(r-2), y+r);
    BSP_LCD_DrawLine(x-(r-2), y+r, x-(r-3), y+(r-5));
   
   
    //bojimo nos
    Point* point1 = new Point();
    Point* point2 = new Point();
    Point* point3 = new Point();
    Point* point4 = new Point();
    point1->X=x+r;
    point1->Y=y;
    point2->X=x+(r-4);
    point2->Y=y-(r-5);
    point3->X=x+(r-4);
    point3->Y=y+(r-5);
    Point curvePoints []= {*point1, *point2, *point3};
    BSP_LCD_SetTextColor(LCD_COLOR_RED);
    BSP_LCD_FillPolygon(curvePoints, 3);
   
    //bojimo tijelo
    point1->X=x+(r-4);
    point1->Y=y-(r-5);
    point2->X=x+(r-4);
    point2->Y=y+(r-5);
    point3->X=x-(r-3);
    point3->Y=y+(r-5);
    point4->X=x-(r-3);
    point4->Y=y-(r-5);
   
    Point curvePoints2 []= {*point1, *point2, *point3, *point4};
    BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
    BSP_LCD_FillPolygon(curvePoints2, 4);
   
    //bojimo prozorcic
    BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
    BSP_LCD_FillCircle(x+vel, y, 2);
   
   
    //krila
    point1->X=x+(r-6);
    point1->Y=y-(r-5);
    point2->X=x-(r-6);
    point2->Y=y-r;
    point3->X=x-(r-2);
    point3->Y=y-r;
    point4->X=x-(r-5);
    point4->Y=y+(r-5);
   
    Point curvePoints3 []= {*point1, *point2, *point3, *point4};
    BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
    BSP_LCD_FillPolygon(curvePoints3, 4);
   
 
   
    point1->X=x+(r-6);
    point1->Y=y+(r-5);
    point2->X=x-(r-6);
    point2->Y=y+r;
    point3->X=x-(r-2);
    point3->Y=y+r;
    point4->X=x-(r-5);
    point4->Y=y+(r-5);
   
    Point curvePoints4 []= {*point1, *point2, *point3, *point4};
    BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
    BSP_LCD_FillPolygon(curvePoints4, 4);
   
   //rep
    point1->X=x-(r-3);
    point1->Y=y-3;
    point2->X=x-r;
    point2->Y=y-3;
    point3->X=x-r;
    point3->Y=y+3;
    point4->X=x-(r-3);
    point4->Y=y+3;
   
    Point curvePoints5 []= {*point1, *point2, *point3, *point4};
    BSP_LCD_SetTextColor(LCD_COLOR_DARKRED);
    BSP_LCD_FillPolygon(curvePoints5, 4);
   
 }
        }
        }
       
   
    bool udariloBrod(Brod b){
        if(distance(this->x,this->y,b.Dajx(),b.Dajy()) < this->r + b.DajR()) return true;
        return false;
    }
};
 
// const int NUM_DEBRIS = 15;
 
    int x11=0;
    int y11=0;
    int x22=0;
    int y22=0;
    int trajanje1=0;
    int trajanje2=0;
    bool prvi=false;
    bool drugi=false;
 
void updateDebrisAndCheckCollisions(std::vector<Debris*> allDebris,Brod &leftShip, Brod &rightShip) {
    for (int i = 0; i < allDebris.size(); i++) {
    allDebris[i]->update();
    allDebris[i]->Display();
    if (allDebris[i]->udariloBrod(leftShip)) {
        trajanje1=3;
        x11=leftShip.Dajx();
        y11=leftShip.Dajy();
        prvi=true;
        leftShip.respawn();
    }
    else if (allDebris[i]->udariloBrod(rightShip)) {
        trajanje2=3;
        x22=rightShip.Dajx();
        y22=rightShip.Dajy();
        drugi=true;
        rightShip.respawn();
    }
  }
}
 
 
 
void crtanjeVatre(int x, int y, bool prvak, int a=9){
    int r=9;
    int trajanje=0;
    if(prvak)
        trajanje=trajanje1;
    else
        trajanje=trajanje2;
       
    BSP_LCD_DrawHLine(x,y+a,a);
    Point* point1 = new Point();
    Point* point2 = new Point();
    Point* point3 = new Point();
    Point* point4 = new Point();
 
    point1->X = x-4;
    point1->Y = y+r;
    point2->X = x+4;
    point2->Y = y+r;
    point3->X = x;
    point3->Y = y-r;
   
   
    Point Veliki[] = {*point1, *point2, *point3};
    BSP_LCD_SetTextColor(LCD_COLOR_RED);
    BSP_LCD_FillPolygon(Veliki,3);
   
    point1->X = x-r;
    point1->Y = y+r;
    point2->X = x-4;
    point2->Y = y+r;
    point3->X = x-2;
    point3->Y = y-2;
   
    Point Trapez[] = {*point1, *point2, *point3};
    BSP_LCD_SetTextColor(LCD_COLOR_RED);
    BSP_LCD_FillPolygon(Trapez,3);
   
    point1->X = x+r;
    point1->Y = y+r;
    point2->X = x+4;
    point2->Y = y+r;
    point3->X = x+4;
    point3->Y = y-2;
   
    Point Zadnji[] = {*point1, *point2, *point3};
    BSP_LCD_SetTextColor(LCD_COLOR_RED);
    BSP_LCD_FillPolygon(Zadnji,3);
   
    point1->X = x+r;
    point1->Y = y+r;
    point2->X = x+4;
    point2->Y = y+r;
    point3->X = x+4;
    point3->Y = y+4;
   
    Point M[] = {*point1, *point2, *point3};
    BSP_LCD_SetTextColor(LCD_COLOR_ORANGE);
    BSP_LCD_FillPolygon(M,3);
   
   
    point1->X = x-4;
    point1->Y = y+r;
    point2->X = x+4;
    point2->Y = y+r;
    point3->X = x;
    point3->Y = y;
   
    Point Manji[] = {*point1, *point2, *point3};
    BSP_LCD_SetTextColor(LCD_COLOR_ORANGE);
    BSP_LCD_FillPolygon(Manji,3);
   
    point1->X = x-r;
    point1->Y = y+r;
    point2->X = x-3;
    point2->Y = y+r;
    point3->X = x-(2);
    point3->Y = y+5;
   
    Point Narandza[] = {*point1, *point2, *point3};
    BSP_LCD_SetTextColor(LCD_COLOR_ORANGE);
    BSP_LCD_FillPolygon(Narandza,3);
   
    if(prvak)
        trajanje1--;
    else
        trajanje2--;
       
    if(trajanje1==0)
        prvi=false;
   
    if(trajanje2==0)
        drugi=false;
   
}
 
void upute(){
    while(1){
    std::string s("Space Race");    
    unsigned char *ime=new unsigned char[s.length()+1];
    strcpy((char*)ime,s.c_str());
    BSP_LCD_Init();
    BSP_LCD_SetFont(&Font24);
    BSP_LCD_SetTextColor(100);
    BSP_LCD_DisplayStringAt(30, 50, ime, LEFT_MODE);    
    delete []ime;
       
    s="Pokreni igru?";
    unsigned char *start=new unsigned char[s.length()+1];
    strcpy((char*)start,s.c_str());
    BSP_LCD_Init();
    BSP_LCD_SetFont(&Font20);
    BSP_LCD_SetTextColor(989);
    BSP_LCD_DisplayStringAt(29, 90, start, LEFT_MODE);  
    delete []start;    
   
    {s="(Pritisnite bilo koji taster)";
    unsigned char *c=new unsigned char[s.length()+1];
    strcpy((char*)c,s.c_str());
    BSP_LCD_Init();
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_SetTextColor(145);
    BSP_LCD_DisplayStringAt(18, 120, c, LEFT_MODE);
    delete []c;}
   
    {s="Upute:";
    unsigned char *c=new unsigned char[s.length()+1];
    strcpy((char*)c,s.c_str());
    BSP_LCD_Init();
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_SetTextColor(155);
    BSP_LCD_DisplayStringAt(5, 135, c, LEFT_MODE);
    delete []c;}
   
    {s="Tasteri pomjeraju brod naprijed";
    unsigned char *c=new unsigned char[s.length()+1];
    strcpy((char*)c,s.c_str());
    BSP_LCD_Init();
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_SetTextColor(145);
    BSP_LCD_DisplayStringAt(5, 150, c, LEFT_MODE);
    delete []c;}
   
    {s="ili nazad. Cilj je skupiti vise";
    unsigned char *c=new unsigned char[s.length()+1];
    strcpy((char*)c,s.c_str());
    BSP_LCD_Init();
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_SetTextColor(145);
    BSP_LCD_DisplayStringAt(5, 165, c, LEFT_MODE);
    delete []c;}    
   
   
    {s="poena nego protivik prije isteka";
    unsigned char *c=new unsigned char[s.length()+1];
    strcpy((char*)c,s.c_str());
    BSP_LCD_Init();
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_SetTextColor(145);
    BSP_LCD_DisplayStringAt(5, 180, c, LEFT_MODE);
    delete []c;}
   
    {s="vremena. Poen se dobije kada brod";
    unsigned char *c=new unsigned char[s.length()+1];
    strcpy((char*)c,s.c_str());
    BSP_LCD_Init();
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_SetTextColor(145);
    BSP_LCD_DisplayStringAt(5, 195, c, LEFT_MODE);
    delete []c;}
   
    {s="dospije na vrh ekrana. Pazite na";
    unsigned char *c=new unsigned char[s.length()+1];
    strcpy((char*)c,s.c_str());
    BSP_LCD_Init();
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_SetTextColor(145);
    BSP_LCD_DisplayStringAt(5, 210, c, LEFT_MODE);
    delete []c;}
   
    {s="prepreke, inace idete na pocetak.";
    unsigned char *c=new unsigned char[s.length()+1];
    strcpy((char*)c,s.c_str());
    BSP_LCD_Init();
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_SetTextColor(145);
    BSP_LCD_DisplayStringAt(5, 225, c, LEFT_MODE);
    delete []c;}
   
    //uslov da igra krene
   if(igrac1F==1 || igrac2F==1 || igrac1B==1 || igrac2B==1)
        break;
       
   wait_ms(1);
    }
   
}
 
int level()
{
    BSP_LCD_Clear(LCD_COLOR_WHITE);
    wait(1);
    while(1){
    BSP_LCD_Clear(LCD_COLOR_WHITE);
    std::string s("Odaberite tezinu:");    
    unsigned char *ime=new unsigned char[s.length()+1];
    strcpy((char*)ime,s.c_str());
    BSP_LCD_Init();
    BSP_LCD_SetFont(&Font16);
    BSP_LCD_SetTextColor(100);
    BSP_LCD_DisplayStringAt(30, 50, ime, LEFT_MODE);    
    delete []ime;
   
    {s="p5 - easy";
    unsigned char *c=new unsigned char[s.length()+1];
    strcpy((char*)c,s.c_str());
    BSP_LCD_Init();
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_SetTextColor(145);
    BSP_LCD_DisplayStringAt(18, 90, c, LEFT_MODE);
    delete []c;}
   
    {s="p6 - medium";
    unsigned char *c=new unsigned char[s.length()+1];
    strcpy((char*)c,s.c_str());
    BSP_LCD_Init();
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_SetTextColor(155);
    BSP_LCD_DisplayStringAt(18, 110, c, LEFT_MODE);
    delete []c;}
   
    {s="p7 - hard";
    unsigned char *c=new unsigned char[s.length()+1];
    strcpy((char*)c,s.c_str());
    BSP_LCD_Init();
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_SetTextColor(155);
    BSP_LCD_DisplayStringAt(18, 130, c, LEFT_MODE);
    delete []c;}
   
    if(igrac1F == 1)
        return 1;
    else if (igrac2F ==1)
        return 2;
    else if (igrac1B == 1)
        return 3;
   
   wait_ms(10);
    }
   return 0;
}
 
std::vector<Debris*> formirajDebris(int NUM_DEBRIS){
    std::vector<Debris*> allDebris;
 
    for (int i = 0; i < NUM_DEBRIS; i++) {
        allDebris.push_back(new Debris());
    }
    return allDebris;
}
 
void zvijezde(std::vector<std::pair<int,int> > v){  
    BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
    for(int i = 0;i<20;i++){
        BSP_LCD_FillRect(v[i].first,v[i].second,4,4);
    }
}
 
 
void Pehar(int p){
    int x = 95;
    int y = 150;
    int h = 8;
    int w = 48;
   
    p = p + '0';
   
    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_FillRect(0, 0, BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
   
    BSP_LCD_SetFont(&Font24);
    BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
    BSP_LCD_FillRect(x,y,w,h);
    BSP_LCD_FillRect(x+h,y-h,w-2*h,h);
    BSP_LCD_FillRect(x+h*2,y-h*4,w-4*h,h*3);
    BSP_LCD_FillRect(x+h,y-h*5,w-2*h,h);
    BSP_LCD_FillRect(x,y-h*10,w,h*5);
    BSP_LCD_FillRect(x+w,y-h*9,w-h*4,h);
    BSP_LCD_FillRect(x+w+h,y-h*8,h,h*3);
    BSP_LCD_FillRect(x+w,y-h*6,h,h);
    BSP_LCD_FillRect(x-h*2,y-h*9,w-h*4,h);
    BSP_LCD_FillRect(x-h*2,y-h*8,h,h*3);
    BSP_LCD_FillRect(x-h*2,y-h*6,h*2,h);
   
    std::string s = "Pobjednik je igrac ";
    s+=p;
    s+="!";
    unsigned char *poruka=new unsigned char[s.length()+1];
    strcpy((char*)poruka,s.c_str());
    BSP_LCD_SetFont(&Font16);
    BSP_LCD_DisplayStringAt(0, 170, poruka, CENTER_MODE);  
    std::string ex = "Pritisnite bilo koje";
    unsigned char *exporuka=new unsigned char[ex.length()+1];
    strcpy((char*)exporuka,ex.c_str());
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_DisplayStringAt(0, 190, exporuka, CENTER_MODE);  
    ex = "dugme da se vratite na pocetak.";
    strcpy((char*)exporuka,ex.c_str());
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_DisplayStringAt(0, 210, exporuka, CENTER_MODE);
    while(1){
        if(igrac1F==1 || igrac2F==1 || igrac1B==1 || igrac2B==1) return;
        wait_ms(5);
    }
}
 
 
int main() {
    Brod igrac1(60);
    Brod igrac2(180);
    int tezina=0;
   
    upute();
    tezina= level();
    int NUM_DEBRIS=0;
    if(tezina == 1)
        NUM_DEBRIS=5;
    else if(tezina==2)
        NUM_DEBRIS=20;
    else
        NUM_DEBRIS=30;
    BSP_LCD_Clear(LCD_COLOR_WHITE);
    wait_ms(500); //wait je da ne bi odmah brod krenuo naprijed kad se stisne taster
   
   
   
    std::vector<Debris*> allDebris = formirajDebris(NUM_DEBRIS);
   
   //generisanje zvijezda
    std::vector<std::pair<int,int> > v;
    for(int i = 0;i<20;i++){
        int x,y;
        x = rand()%230;
        y = rand()%200;
        v.push_back(make_pair(x,y));
    }//random je i dogadja se samo jednom
   
   
    double brojac(0);
   
    while(1){
 
        std::string s1 = std::to_string(igrac1.Dajscore());
        std::string s2 = std::to_string(igrac2.Dajscore());
       
        unsigned char *score1=new unsigned char [s1.length()+1];
        strcpy((char *)score1, s1.c_str());
       
        unsigned char *score2=new unsigned char [s2.length()+1];
        strcpy((char *)score2, s2.c_str());
       
       
            BSP_LCD_Init();
            BSP_LCD_SetFont(&Font24);
            //bojanje ekrana
            BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
            BSP_LCD_FillRect(0, 0, BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
            //kraj bojanja ekrana
            BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
            BSP_LCD_FillRect(110,brojac,8,240);
            zvijezde(v); //crtanje zvijezda
            BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
           
            BSP_LCD_DisplayStringAt(10, 210, score1, LEFT_MODE);
            BSP_LCD_DisplayStringAt(210, 210, score2, LEFT_MODE);
           
            igrac1.display();
            igrac2.display();
           
            updateDebrisAndCheckCollisions(allDebris,igrac1,igrac2);
            if(prvi)
                crtanjeVatre(x11, y11, true);
            if(drugi)
                crtanjeVatre(x22, y22, false);
           
           
           
            //kontrola
            if(igrac1F == 1){
                igrac1.gore();
                igrac1.display();
                igrac2.display();
            }
            if(igrac1B == 1 && igrac1.Dajy() !=230){
                igrac1.dole();
                igrac1.display();
                igrac2.display();
            }
            if(igrac2F == 1){
                igrac2.gore();
                igrac1.display();
                igrac2.display();
            }
            if(igrac2B == 1 && igrac2.Dajy() !=230){
                igrac2.dole();
                igrac1.display();
                igrac2.display();
            }
            if(igrac1.Dajy() <= 12){
                igrac1.respawn();
                igrac1.addingPoint();
            }
            if(igrac2.Dajy() <= 12) {
                igrac2.respawn();
                igrac2.addingPoint();
            }
            brojac+=3; //za 10ms se visina poveca za 0.01px, znaci za 1s imamo povecanje od 1px
                                                    //nasa igra bi onda trebala trajati 240s odnosno 4min i onda se prekida
            if(brojac>=240){
                if(igrac1.Dajscore() > igrac2.Dajscore()) Pehar(1);
                else if(igrac1.Dajscore() < igrac2.Dajscore()) Pehar(2);
                else{
                    brojac=0;
                    continue;
                };
                brojac=0;
                igrac1.respawn();
                igrac1.resetujScore();
                igrac2.respawn();
                igrac2.resetujScore();
                BSP_LCD_Clear(LCD_COLOR_WHITE);
                upute();
                tezina=level();
                if(tezina == 1)
                    NUM_DEBRIS=10;
                else if(tezina==2)
                    NUM_DEBRIS=20;
                else
                    NUM_DEBRIS=30;
                BSP_LCD_Clear(LCD_COLOR_WHITE);
                wait_ms(500);
                allDebris = formirajDebris(NUM_DEBRIS);
            }
               
            wait_ms(5);
            BSP_LCD_Clear(LCD_COLOR_WHITE);
     }
   }