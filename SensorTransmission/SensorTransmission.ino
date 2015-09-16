#include "dht.h"

dht11 DHT;

#define PIN_TEMP 5
#define PIN_WM A0
//miejsce na funkcje (lub prototypy)
int funct1();  //obslugujace poszczegolne czujniki
int funct2();  //i zwracajace pomiar jako int
int funct3();  //aczkolwiek sama zwracana wartosc 

const int sensN = 3;  //liczba obslugiwanych czujnikow
const int sensNBajt[sensN] = {1,1,2}; //liczba bajtow zjmowanych przez pomiary (1 lub 2)
int (*(sensFunct[sensN]))(void) = {funct1,funct2,funct3};  //tabela wskaznikow na 
                                                  //funcje obslugujace kolejne czuniki
void send();

void setup() {
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()){
    int receive = Serial.read();
    switch(receive){
      case 227:{
        send();
        f1();
        f2();
        f3();
        break;
      }
      case 255:{
        Serial.print(char(255));
        break;
      }
    }
  }
}

void send(){
  for(int i=0;i<sensN;i++){
    int tmp = (sensFunct[i])();
    if(sensNBajt[i] == 2){
      Serial.print(char(tmp>>8));
      //tmp%=256;
    }
    Serial.print(char(tmp));
  }
}
int v1=1,v2=1,v3=1;
int funct1() { 

return v1;
}
int funct2() {
return v2;
  
} 
int funct3() {
return v3;
}
int f1() { 
  int chk = DHT.read(PIN_TEMP);
switch (chk)
{
case DHTLIB_OK:
//ok
break;
case DHTLIB_ERROR_CHECKSUM:
return 0;
break;
case DHTLIB_ERROR_TIMEOUT:
return 0;
break;
default:
return 0;
break;
}
v1=DHT.humidity;
return v1; //int - wilgotnosc %
}
int f2() {
  v2=DHT.temperature;
  return  1;//int - temperatura C
  
} 
int f3() {
  v3 = analogRead(PIN_WM);
  return  1;//int - przepływ prądu
}
/*#include "dht.h"

dht11 DHT;

#define PIN_TEMP 5
#define PIN_WM A0
//miejsce na funkcje (lub prototypy)
int funct1();  //obslugujace poszczegolne czujniki
int funct2();  //i zwracajace pomiar jako int
int funct3();  //aczkolwiek sama zwracana wartosc 
//int funct4();  //nie powinna przekroczyc tej deklarowanej
               //ponizej w tablei sensNBajt

const int sensN = 3;  //liczba obslugiwanych czujnikow
const int sensNBajt[sensN] = {1,1,2}; //liczba bajtow zjmowanych przez pomiary (1 lub 2)
int (*(sensFunct[sensN]))(void) = {funct1,funct2,funct3};  //tabela wskaznikow na 
                                                  //funcje obslugujace kolejne czuniki
void send();

void setup() {
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()){
    int receive = Serial.read();
    switch(receive){
      case 227:{
        send();
        break;
      }
      case 255:{
        Serial.print(char(255));
        break;
      }
    }
  }
}

void send(){
  for(int i=0;i<sensN;i++){
    int tmp = (sensFunct[i])();
    if(sensNBajt[i] == 2){
      Serial.print(char(tmp>>8));
      tmp%=256;
    }
    Serial.print(char(tmp));
  }
}


int funct1() { 
  int chk = DHT.read(PIN_TEMP);
switch (chk)
{
case DHTLIB_OK:
//ok
break;
case DHTLIB_ERROR_CHECKSUM:
return 0;
break;
case DHTLIB_ERROR_TIMEOUT:
return 0;
break;
default:
return 0;
break;
}

return DHT.humidity; //int - wilgotnosc %
}
int funct2() {
  return  DHT.temperature;//int - temperatura C
  
} 
int funct3() {
  int current = analogRead(PIN_WM);

  return  current;//int - przepływ prądu
} */
