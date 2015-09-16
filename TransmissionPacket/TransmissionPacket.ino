#include "HeartTransmission.h"

Engine engine(2,3);
Sensors sensors(4,5);
SensorsDataPacket LastSensReceive;
BlackBox blackBox(6,7);

bool CheckConnection();

void setup() {
  Serial.begin(9600);
  engine.begin(9600);
  sensors.SetTimer(5000);
  sensors.begin(9600);
  blackBox.begin(9600);
  
  bool x = CheckConnection();
  while(!x){
    Serial.println("Wpisz I by zignorowac blad, P by sprobowac polaczyc ponownie");
    while(!Serial.available());
    char in = Serial.read();
    if(in == 'I'||in == 'i')
      x = 1;
    else
      x = CheckConnection();
  }
  
}

void loop() {
  while(Serial.available()) {
    int command = Serial.read();
    blackBox.send(command,engine.send(command),1);
  }
    
  if(sensors.time()){
    LastSensReceive = sensors.read();
    LastSensReceive.print();
    blackBox.send(LastSensReceive);
  }
  delay(1000);
}

bool CheckConnection(){
  bool x = 1;
  Serial.println("Sprawdzanie podzespolow...");
    if(engine.ping())
      Serial.println("\tSilniki podlaczone.");
    else {
      Serial.println("\tSilniki nie odpowiadja!");
      x=0;
    }
    if(sensors.ping())
      Serial.println("\tCzujniki podlaczone.");
    else {
      Serial.println("\tCzujniki nie odpowiadja!");
      x=0;
    }
    if(blackBox.ping())
      Serial.println("\tCzarna szkrzynka podloczona.");
    else {
      Serial.println("\tCzarna skrzynka nie odpowiada!");
      x=0;
    }
    if(x)
      Serial.println("Udane polaczenie wszystkich podzespolow!");
    else
      Serial.println("Nieudane polaczenie podzespolow.");
    return x;
}

