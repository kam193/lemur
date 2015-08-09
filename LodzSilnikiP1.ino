/*
	Kamil Mankowski / 2015
*/
void stopMotor(int no);
void stopAllMotors();
void setMotor(int no, int speed, boolean r);
void testAllMotors();

//Zestawy zadan
void PionNaMaxaG();
void Silnik1Max();

//Komunikacja
void preprocess(int cmmd);
void Receive();

int enablePins[6]; // !PWM
int in1Pins[6];
int in2Pins[6];

int motorCount = 2;

int stan = -1;

void setup()
{
	enablePins[0] = 11;
	in1Pins[0] = 9;
	in2Pins[0] = 10;

	enablePins[1] = 6;
	in1Pins[1] = 7;
	in2Pins[1] = 8;

	for (int i = 0; i < motorCount; i++)
	{
		pinMode(enablePins[i], OUTPUT);
		pinMode(in1Pins[i], OUTPUT);
		pinMode(in2Pins[i], OUTPUT);
	}

	pinMode(13, OUTPUT);

	stopAllMotors();

	Serial.begin(9600);
}

void loop()
{
	/*testAllMotors();
	digitalWrite(13, HIGH);
	delay(3000);
	digitalWrite(13, LOW);*/

	Receive();
}

void Receive(){
	while (Serial.available()){
		int command = Serial.read();
		Serial.print(char(command));
		if (command != 255)
			preprocess(command);
	}
}

void preprocess(int cmmd){
	// Miejsce na tresc funkcji 
	// przetwrzajacej otrzymane komendy

	if (cmmd == 48) //0
	{
		stan = -1;
		stopAllMotors();
		stan = 0;
	}
	else if (cmmd == 49) //1
	{
		stan = -1;
		testAllMotors();
		stopAllMotors();
		stan = 0;
	}
	else if (cmmd == 50) //2
	{
		stan = -1;
		stopAllMotors();
		PionNaMaxaG();
		stan = 2;
	}
	else if (cmmd == 51) //3
	{
		stan = -1;
		stopAllMotors();
		Silnik1Max();
		stan = 3;
	}
	else if (cmmd == 57) //9
	{
		Serial.print(stan);
	}
}

void stopMotor(int no)
{
	digitalWrite(enablePins[no], LOW);
}

void stopAllMotors()
{
	for (int i = 0; i < motorCount; i++)
		stopMotor(i);
}

void setMotor(int no, int speed, boolean r)
{
	analogWrite(enablePins[no], speed);
	digitalWrite(in1Pins[no], !r);
	digitalWrite(in2Pins[no], r);
}

void testAllMotors()
{
	stan = 1;
	//wszystkie stop
	stopAllMotors();
	delay(100);

	//wszystkie max
	for (int i = 0; i < motorCount; i++)
		setMotor(i, 255, true);

	delay(2000);

	//wszystkie max w drug¹ stronê
	for (int i = 0; i < motorCount; i++)
		setMotor(i, 255, false);

	delay(2000);

	//wszystkie polowa
	for (int i = 0; i < motorCount; i++)
		setMotor(i, 128, true);

	delay(2000);

	//kazdy po kolei max
	stopAllMotors();
	for (int i = 0; i < motorCount; i++)
	{
		setMotor(i, 255, true);
		delay(1000);
		stopMotor(i);
		delay(1000);
	}
}

void PionNaMaxaG()
{
	setMotor(0, 255, true);
	setMotor(1, 255, true);
}

void Silnik1Max()
{
	setMotor(1, 255, true);
}