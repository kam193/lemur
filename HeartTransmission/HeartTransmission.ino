#include "HeartTransmission.h"

//Sensors part:

void SensorsDataPacket::print()
{
  Serial.println("\nZebrane dane:");
  for(int i=0;i<sensN;i++){
    Serial.print('\t');
    Serial.print(sensTAGs[i]);
    Serial.print(": ");
    Serial.print(data[i],DEC);
    Serial.print('\n');
  }
  Serial.print('\n');
}

void Sensors::begin(int baud)
{
  serial->begin(baud);
}

Sensors::Sensors(int rx,int tx) 
{
  timer = 5000;
  serial = new SoftwareSerial(rx,tx);
}

SensorsDataPacket Sensors::read()
{
  SensorsDataPacket data;
  serial->listen();
  serial->print(char(227));
  unsigned long time = millis();
  for(int i=0;i<sensN;i++){
    while(!serial->available())
      if(millis()-time>2){
        SensorError();
        return data;
      }
    data.data[i]=serial->read();
    time = millis();
    if(2==sensNBajt[i]){
      data.data[i]<<=8;
      while(!serial->available())
        if(millis()-time>2){
          SensorError();
          return data;
        }
      data.data[i]+=serial->read();
      time = millis();
    }
  }
  LastReceiveTime = millis();
  return data;
}

void SensorError(){
  Serial.println("utracono polaczenie z czujnikami!");
}

bool Sensors::ping()
{
  serial->listen();
  serial->print(char(255));
  unsigned long time = millis();
    while(255!=serial->read())
      if(millis()-time>2)
        return 0;
  return 1;
}

bool Sensors::time()
{
  return millis()-LastReceiveTime>timer;
}

Sensors::~Sensors()
{
  delete serial;
}

//Engine part:

void Engine::begin(int baud)
{
  serial->begin(baud);
}

Engine::Engine(int rx,int tx) 
{
  serial = new SoftwareSerial(rx,tx);
}

bool Engine::send(int cmmd)
{
  bool x=0;
  for(int i=0;i<2&&!x;i++)
  {
    x=1;
    serial->listen();
    serial->print(char(cmmd));
    unsigned long time = millis();
    while(!serial->available())
      if(millis()-time>2){
        x=0;
        break;
      }
    if(x){
      int ans = serial->read();
      if(ans!=cmmd)
        EngineError(2,cmmd,ans);
    }
  }
  if(!x)
    EngineError(1);
  return x;
}

void EngineError(int code,int val1,int val2){
  Serial.print("Blad polaczenia z silnikami [");
  Serial.print(code,DEC);
  Serial.print("]: ");
  switch(code){
    case 1:{
      Serial.print("brak odpowiedzi\n");
      break;
    }
    case 2:{
      Serial.print("przeslano ");
      Serial.print(val1,DEC);
      Serial.print(" ('");
      Serial.print(char(val1));
      Serial.print("'), otrzymano ");
      Serial.print(val2,DEC);
      Serial.print(" ('");
      Serial.print(char(val2));
      Serial.print("')\n");
      break;
    }
  }
  
}

bool Engine::ping()
{
  serial->listen();
  serial->print(char(255));
  int time = millis();
    while(255!=serial->read())
      if(millis()-time>90)
        return 0;
  return 1;
}

Engine::~Engine()
{
  delete serial;
}

//BlackBox part:

void BlackBox::begin(int baud)
{
  serial->begin(baud);
}

BlackBox::BlackBox(int rx,int tx) 
{
  serial = new SoftwareSerial(rx,tx);
}

void BlackBox::send(int cmmd,bool status,bool report)
{
  serial->listen();
  serial->print(char(227+status));
  serial->print(char(cmmd));
  if(report){
    if(status)
      Serial.print("Udane ");
    else
      Serial.print("Nieudane ");
    Serial.print(" przeslanie polecenia ");
    Serial.print(char(cmmd));
    Serial.print(" (");
    Serial.print(cmmd,DEC);
    Serial.print(") do silnikow\n");
  }
}

void BlackBox::send(SensorsDataPacket data)
{
  serial->listen();
  serial->print(char(92));
  
  for(int i=0;i<sensN;i++){
    if(sensNBajt[i]==2){
      serial->print(char(data.data[i]>>8));
      data.data[i]%=256;
    }
    serial->print(char(data.data[i]));
  }
}

void BlackBoxError(){
  Serial.println("utracono polaczenie z czujnikami!");
}

bool BlackBox::ping()
{
  serial->listen();
  serial->print(char(255));
  int time = millis();
    while(255!=serial->read())
      if(millis()-time>90)
        return 0;
  return 1;
}

BlackBox::~BlackBox()
{
  delete serial;
}

void setup()
{
  ;
}
void loop()
{
  ;
}

