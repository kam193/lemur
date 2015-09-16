void preprocess(int cmmd);
void Receive();


void setup() {
  //miejsce na inicjalizacje
  Serial.begin(9600);
}

void loop() {
  //miejsce na obsluge silnikow
  //czy tam cokolwiek innego...
  Receive();
}

void Receive(){
  while(Serial.available()){
    int command = Serial.read();
    Serial.print(char(command));
    if(command!=255)
      preprocess(command);
  }
}

void preprocess(int cmmd){
  // Miejsce na tresc funkcji 
  // przetwrzajacej otrzymane komendy
  
}

