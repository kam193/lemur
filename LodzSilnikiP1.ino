int enablePins[6]; // !PWM
int in1Pins[6];
int in2Pins[6];

int motorCount = 1;

void setup()
{
	enablePins[0] = 11;
	in1Pins[0] = 9;
	in2Pins[0] = 10;

	for (int i = 0; i < motorCount; i++)
	{
		pinMode(enablePins[i], OUTPUT);
		pinMode(in1Pins[i], OUTPUT);
		pinMode(in2Pins[i], OUTPUT);
	}
}

void loop()
{
	setMotor(254, false);io how to 

}

void stopAllMotors()
{
	for (int i = 0; i < motorCount; i++)
	{

	}
}

void setMotor(int speed, boolean reverse)
{
	/*analogWrite(enablePin, speed);
	digitalWrite(in1Pin, !reverse);
	digitalWrite(in2Pin, reverse);*/
}
