/*
	Kamil Mankowski / 2015
	v1.0-komendy
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

char stan = '0';

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
	
	if (code == '0')
	{
		stopAllMotors();
		stan = '0';
	}
	else if (code == '1')
	{
		setLeftPositionMotors(FULL_SPEED, UP);
		setRightPositionMotors(FULL_SPEED, UP);
		stan = '1';
	}
	else if (code == '2')
	{
		setLeftPositionMotors(THREE4_SPEED, UP);
		setRightPositionMotors(THREE4_SPEED, UP);
		stan = '2';
	}
	else if (code == '3')
	{
		setLeftPositionMotors(HALF_SPEED, UP);
		setRightPositionMotors(HALF_SPEED, UP);
		stan = '3';
	}
	else if (code == '4')
	{
		setLeftPositionMotors(QUARTER_SPEED, UP);
		setRightPositionMotors(QUARTER_SPEED, UP);
		stan = '4';
	}
	else if (code == '5')
	{
		setLeftPositionMotors(FULL_SPEED, DOWN);
		setRightPositionMotors(FULL_SPEED, DOWN);
		stan = '5';
	}
	else if (code == '6')
	{
		setLeftPositionMotors(THREE4_SPEED, DOWN);
		setRightPositionMotors(THREE4_SPEED, DOWN);
		stan = '6';
	}
	else if (code == '7')
	{
		setLeftPositionMotors(HALF_SPEED, DOWN);
		setRightPositionMotors(HALF_SPEED, DOWN);
		stan = '7';
	}
	else if (code == '8')
	{
		setLeftPositionMotors(QUARTER_SPEED, DOWN);
		setRightPositionMotors(QUARTER_SPEED, DOWN);
		stan = '8';
	}
	else if (code == '9')
	{
		setLeftPositionMotors(STOP);
		setRightPositionMotors(STOP);
		stan = '9';
	}
	else if (code == 'a')
	{
		setDriveMotors(FULL_SPEED, FRONT, FRONT);
		stan = 'a';
	}
	else if (code == 'b')
	{
		setDriveMotors(THREE4_SPEED, FRONT, FRONT);
		stan = 'b';
	}
	else if (code == 'c')
	{
		setDriveMotors(HALF_SPEED, FRONT, FRONT);
		stan = 'c';
	}
	else if (code == 'd')
	{
		setDriveMotors(QUARTER_SPEED, FRONT, FRONT);
		stan = 'd';
	}
	else if (code == 'e')
	{
		setDriveMotors(FULL_SPEED, BACK, BACK);
		stan = 'e';
	}
	else if (code == 'f')
	{
		setDriveMotors(THREE4_SPEED, BACK, BACK);
		stan = 'f';
	}
	else if (code == 'g')
	{
		setDriveMotors(HALF_SPEED, BACK, BACK);
		stan = 'g';
	}
	else if (code == 'h')
	{
		setDriveMotors(QUARTER_SPEED, BACK, BACK);
		stan = 'h';
	}
	else if (code == 'i')
	{
		setDriveMotors(FULL_SPEED, BACK, FRONT);
		stan = 'i';
	}
	else if (code == 'j')
	{
		setDriveMotors(THREE4_SPEED, BACK, FRONT);
		stan = 'j';
	}
	else if (code == 'k')
	{
		setDriveMotors(HALF_SPEED, BACK, FRONT);
		stan = 'k';
	}
	else if (code == 'l')
	{
		setDriveMotors(QUARTER_SPEED, BACK, FRONT);
		stan = 'l';
	}
	else if (code == 'm')
	{
		setDriveMotors(FULL_SPEED, FRONT, BACK);
		stan = 'm';
	}
	else if (code == 'n')
	{
		setDriveMotors(THREE4_SPEED, FRONT, BACK);
		stan = 'n';
	}
	else if (code == 'o')
	{
		setDriveMotors(HALF_SPEED, FRONT, BACK);
		stan = 'o';
	}
	else if (code == 'p')
	{
		setDriveMotors(QUARTER_SPEED, FRONT, BACK);
		stan = 'p';
	}
	else if (code == 'r')
	{
		setDriveMotors(STOP);
		stan = 'r';
	}
	else if (code == 's')
	{
		Serial.print(stan);
	}
	else if (code == 't')
	{
		testAllMotors();
		stan = 't';
	}
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

void setLeftPositionMotors(int speed, boolean r)
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

void setRightPositionMotors(int speed, boolean r)
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

void setDriveMotors(int speed, boolean r_right, boolean r_left)
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