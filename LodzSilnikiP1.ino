/*
	Kamil Mankowski / 2015
*/
#define STOP 0
#define QUARTER_SPEED 64
#define HALF_SPEED 128
#define THREE4_SPEED 192
#define FULL_SPEED 255

#define UP true
#define DOWN false

#define FRONT true
#define BACK false

void stopMotor(int no);
void setMotor(int no, int speed, boolean r);
void testAllMotors();

void stopAllMotors();
void setLeftPositionMotors(int speed, boolean r = UP);
void setRightPositionMotors(int speed, boolean r = UP);
void setDriveMotors(int speed, boolean r_right = FRONT, boolean r_left = FRONT);

void preprocess(int cmmd);
void Receive();

int enablePins[6] = { 3, 5, 6, 9, 10, 11 }; // PWM
int in1Pins[6] = { 2, 4, 7, 8, 12, 13 };
int in2Pins[6] = { 19, 18, 17, 16, 15, 14 };

int motorCount = 6;

int stan = -1;

void setup()
{
	for (int i = 0; i < motorCount; i++)
	{
		pinMode(enablePins[i], OUTPUT);
		pinMode(in1Pins[i], OUTPUT);
		pinMode(in2Pins[i], OUTPUT);
	}

	stopAllMotors();

	Serial.begin(9600);
}

void loop()
{
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
	char code = '0';

	if (cmmd >= 0 && cmmd <= 255)
		code = cmmd;
	
	

	if (code == 'F')
	{
		testAllMotors();
	}
	if (cmmd == 48) //0 - STOP
	{
		stan = -1;
		stopAllMotors();
		stan = 0;
	}
	
			//Serial.print(stan);
}

void stopMotor(int no)
{
	digitalWrite(enablePins[no], STOP);
}

void setMotor(int no, int speed, boolean r)
{
	analogWrite(enablePins[no], speed);
	digitalWrite(in1Pins[no], !r);
	digitalWrite(in2Pins[no], r);
}

void testAllMotors()
{
	for (int i = 0; i < motorCount; i++)
		setMotor(i, FULL_SPEED, true);

	delay(3000);

	stopAllMotors();
	delay(1000);

	for (int i = 0; i < motorCount; i++)
		setMotor(i, FULL_SPEED, false);

	delay(3000);

	stopAllMotors();
}

void stopAllMotors()
{
	for (int i = 0; i < motorCount; i++)
		stopMotor(i);
}

void setLeftPositionMotors(int speed, boolean r = UP)
{
	if (speed == STOP)
	{
		stopMotor(3);
		stopMotor(5);
	}
	else
	{
		setMotor(3, speed, r);
		setMotor(5, speed, r);
	}
}

void setRightPositionMotors(int speed, boolean r = UP)
{
	if (speed == STOP)
	{
		stopMotor(2);
		stopMotor(4);
	}
	else
	{
		setMotor(2, speed, r);
		setMotor(4, speed, r);
	}
}

void setDriveMotors(int speed, boolean r_right = FRONT, boolean r_left = FRONT)
{
	if (speed == STOP)
	{
		stopMotor(0);
		stopMotor(1);
	}
	else
	{
		setMotor(0, speed, r_right);
		setMotor(1, speed, r_left);
	}
}