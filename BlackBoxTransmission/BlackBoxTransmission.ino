const int sensN = 4;  //ilość czujnikow
const char sensTAGs[sensN][30] = {"TEMPERATURA (st. C)","CISNIENIE (hPa)","ODlEGLOSC OD TAFLI (cm)","ODLEGLOSC OD DNA (cm)"}; //ich etykiety
const int sensNBajt[sensN] = {1,2,2,2}; //liczba bajtów zajmowanych przez pomiary z poszczególnych czujników, chwilowo jedynymi możliwościami będzie 1 lub 2

void Receive();

int LastReceiveSensors[sensN]; //dane z czujnikow

void PreprocessSensors(int interrupt = -1); //funkcja przetwarzajaca znajdujace sie w tablicy LastReceiveSensors dane z czujnikow;
         //argument to indeks od ktorego nastapilo przerwanie pobierania danych (-1 oznacza udane przechwycenie wszystkich danych)
void PreprocessEngine(int cmmd,bool succesfull); //funkcja przetwarzajaca polecenia (argument cmmd) wydane silnikom;
                                 //argument succesfull informuje czy komenda zostala poprawnie przeslana do silnikow

void setup() {

  Serial.begin(9600);
}

void loop() {
   Receive();
}

void Receive() {
  while(Serial.available()){
    int type = Serial.read();
    switch(type){
      case 255:{
        Serial.print(char(255));
        break;
      }
      case 52: {
        PreprocessEngine(Serial.read(),0);
        break;
      }
      case 53: {
        PreprocessEngine(Serial.read(),1);
        break;
      }
      case 92: {
        unsigned long time = millis();
        for(int i=0;i<sensN;i++){
          while(!Serial.available())
            if(millis()-time>2){
              //SensorError();
              for(int j=i;j<sensN;j++)
                LastReceiveSensors[j]=-1;
              PreprocessSensors(i);
              return;
            }
          LastReceiveSensors[i]=Serial.read();
          time = millis();
          if(2==sensNBajt[i]){
            LastReceiveSensors[i]<<=8;
            while(!Serial.available())
              if(millis()-time>2){
                //SensorError();
                for(int j=i;j<sensN;j++)
                  LastReceiveSensors[j]=-1;
                PreprocessSensors(i);
                return;
              }
            LastReceiveSensors[i]+=Serial.read();
            time = millis();
          }
        }
        PreprocessSensors();
        break;
      }
    }
  }
}

