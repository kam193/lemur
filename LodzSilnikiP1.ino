/*
	Kamil Mankowski / 2015
*/

int enablePins[6]; // !PWM
int in1Pins[6];
int in2Pins[6];

int motorCount = 2;

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
}

void loop()
{
	testAllMotors();
	digitalWrite(13, HIGH);
	delay(3000);
	digitalWrite(13, LOW);
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