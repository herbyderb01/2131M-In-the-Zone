#include "BackOver Functions 2017-18.c"
//-------------Variables--------------//
int Nine = 750;
int full = 1750;
int drivepower = 127;
float  liftRSensorCurrentValue;

// PID CHAIN Variables
int StraitUpChain = 1225;
int OutPositionChain = 3050;
int StationaryPositionChain = 1930;
int InPositionChain = 420;

// PID Mobile Variables
int mobileIn = 955;
int mobileOut = 3260;
int mobileMid = 1860;
int mobileSMid = 2770;

//-------------Motor Void Set-Up--------------//

void setDrivePower(int left, int right)
{// Defining all of the motors for the -DRIVE-
	motor[LDrive] = left;		//Define this motor as the left drive
	motor[RDrive] = right;	//Define this motor as the right drive
	motor[DriveL] = left;		//Define this motor as the left 3 motor drive
	motor[DriveR] = right;	//Define this motor as the right 3 motor drive
}

void setLiftPower(int power)
{// Defining all of the motors for the -LIFT-
	motor[liftR] = power;
	motor[liftL] = power;
}

void setChainPower(int cpower)
{// Defining all of the motors for the -CHAIN BAR-
	motor[chain] = cpower;
}

void setIntakePower(int Ipower)
{// Defining all of the motors for the -INTAKE-
	motor[INtake] = Ipower;
}

void setMobilePower(int Mpower)
{// Defining all of the motors for the -MOBILE GOAL INTAKE-
	motor[MobileL] = Mpower;
	motor[MobileR] = Mpower;
}

//_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_//
//--------------------Autonomous Voids-----------------------//
void AutoStrait(int distance, int power)
 // Creating a function to make sure the robot drives forward
{
	int direction = sgn(distance);
	distance = abs(distance);

	while(abs(SensorValue[rightEncoder])<distance) // telling it to do this while you are driving to the disired distance
	{
		if (abs(SensorValue[rightEncoder]) > abs(SensorValue[leftEncoder])) // Checking if the right drive is faster than the left drive
		{
			setDrivePower(direction * power, direction * (power - 4));
		}
		else if (abs(SensorValue[leftEncoder]) > abs(SensorValue[rightEncoder])) // Checking if the left drive is faster than the right drive
		{
			setDrivePower(direction * (power - 2), direction * power);
		}
		else //if the values are the same, keeps motor powers equall
		{
			setDrivePower(direction * power, direction * power);
		}
	}


		motor[LDrive] = 0; // stops motors when finished with function
		motor[RDrive] = 0;

}



void Atondrive(int ticks, int power) //auton function to move forward by its self
{
	  //Clear Encoders
  SensorValue[rightEncoder] = 5;
  SensorValue[leftEncoder] = 0;

  //int LeftEncoderPos = abs(SensorValue[leftEncoder]); // this is test code we are currently not using

		///forward
	AutoStrait(ticks*0.6, power);
	AutoStrait(ticks*0.8, power/2);
	AutoStrait(ticks, power/3);

	motor[LDrive] = -20 * sgn(ticks); //sudden stop to correct overshooting the value
	motor[RDrive] = -20 * sgn(ticks);
	wait1Msec(100);
}


void turnRight(int ticks) // void to turn the robot right as much as you want
{
	//Clear Gyro
	SensorValue[Gyro] = 0;

	while(abs(SensorValue[Gyro]) < ticks) //while the sensor value is less than the amount of turing
  {
		setDrivePower(60, -60); //set drive power to turn robot right
	}

	setDrivePower(-10,10); //then stop
}

void turnLeft(int ticks) // void to turn the robot left as much as you want
{
	//Clear Gyro
	SensorValue[Gyro] = 0;

	while(abs(SensorValue[Gyro]) < ticks) //while the sensor value is less than the amount of turing
	{
		setDrivePower(-60, 60); //set drive power to turn robot right
	}

	setDrivePower(10,-10); //then stop}
}

//_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_//
//--------------------Special Auto Stack Voids-----------------------//

void AutoStackUp()									// Simple Auto stack cone up
{

	//Atondrive(1000, 100);

}

void AutoStackDown()									// Simple Auto stack cone down
{

//	Atondrive(1000, -100);

}

//_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_//
//--------------------Autonomous Programs----------------------------//

task RightBlue () // Auton task to grab moble base on the right and score it
{
	//--------------------------//

	chainRRequestedValue = 1240;
	liftRRequestedValue = 3000;

	Atondrive(480, 127);
	chainRRequestedValue = 2870;

	wait1Msec(600);

	liftRRequestedValue = 2500;

	setDrivePower(-100, -100);
	wait1Msec(250);
	setDrivePower(0, 0);

	chainRRequestedValue = 1240;

	setMobilePower(127);
	wait1Msec(1000);
	setMobilePower(0);

	Atondrive(200, 100);

	setMobilePower(-127);
	wait1Msec(1000);
	setMobilePower(0);

	setDrivePower(-100, -100);
	wait1Msec(1100);
	setDrivePower(0, 0);

  //--------------------------//

	turnRight(full-80);

	Atondrive(130, 100);

	setMobilePower(127);
	wait1Msec(1000);
	setMobilePower(0);

	setDrivePower(-100, -100);
	wait1Msec(100);
	setDrivePower(0, 0);
}

task LeftBlue ()
{

	//--------------------------//

	chainRRequestedValue = 1240;
	liftRRequestedValue = 3000;

	Atondrive(750, 127);

	setDrivePower(-100, -100);
	wait1Msec(600);
	setDrivePower(0, 0);

	turnLeft(240);

	setDrivePower(-100, -100);
	wait1Msec(100);
	setDrivePower(0, 0);


	chainRRequestedValue = 2870;

	wait1Msec(600);

	liftRRequestedValue = 2500;

	setDrivePower(-100, -100);
	wait1Msec(250);
	setDrivePower(0, 0);

	chainRRequestedValue = 1240;

	setMobilePower(127);
	wait1Msec(1000);
	setMobilePower(0);

	Atondrive(200, 100);

	setMobilePower(-127);
	wait1Msec(1000);
	setMobilePower(0);

	setDrivePower(-100, -100);
	wait1Msec(1100);
	setDrivePower(0, 0);

  //--------------------------//

	turnLeft(full-500);

	Atondrive(500, 100);

	setMobilePower(127);
	wait1Msec(1000);
	setMobilePower(0);

	setDrivePower(-100, -100);
	wait1Msec(100);
	setDrivePower(0, 0);

}

task SkillsOne ()
{

			chainRRequestedValue = StraitUpChain; //
			liftRRequestedValue = 2600;           // PRESETS
			mobileRRequestedValue = mobileIn;     //

			mobileRRequestedValue = mobileOut;
			WaitieThing();

			liftRRequestedValue = 3000;

			Atondrive(380, 127);

			wait1Msec(200);

			liftRRequestedValue = 3000;
			chainRRequestedValue = 2800; //score pre-load

			wait1Msec(550);

			chainRRequestedValue = StraitUpChain;
			liftRRequestedValue = 2600;


		//////////////////////////////////Section 1 -score first mobile goal
			mobileRRequestedValue = mobileIn;
			WaitieThing();

			Atondrive(-250, drivepower);

			turnLeft(Nine+50);

			Atondrive(200, drivepower);

			turnLeft(Nine+100);

			Atondrive(90, drivepower);

			setDrivePower(20,20);

			liftRRequestedValue = 2500;

			Atondrive(225, drivepower);

			setDrivePower(20,20);

			mobileRRequestedValue = mobileOut;
			WaitieThing();

			Atondrive(-50, drivepower);

			mobileRRequestedValue = mobileIn;
			WaitieThing();

		/////////////////////////////////////////Section 2 - Grab mobile goal 2
			Atondrive(-190, drivepower);

			wait1Msec(250);

			turnLeft(Nine);

			Atondrive(190, drivepower);

			wait1Msec(240);

			turnLeft(295);

			mobileRRequestedValue = mobileOut;
			WaitieThing();

			Atondrive(630, drivepower);

			mobileRRequestedValue = mobileIn;
			WaitieThing();

			Atondrive(-550, drivepower);

			turnRight(Nine+400);

			Atondrive(60, drivepower);


			mobileRRequestedValue = mobileOut;
			WaitieThing();

			Atondrive(-50, drivepower);

			mobileRRequestedValue = mobileIn;
			WaitieThing();

		////////////////////////////////////////////Section 3 - Score goal 3

			turnLeft(full+100);

			setDrivePower(-40, -40);
			wait1Msec(1200);
			setDrivePower(0, 0);

			mobileRRequestedValue = mobileOut;

			Atondrive(850, drivepower);

			mobileRRequestedValue = mobileMid;
			WaitieThing();

			Atondrive(600, drivepower);

			turnLeft(Nine);

			Atondrive(150, drivepower);

			turnRight(Nine+10);

			Atondrive(350, drivepower);

			setDrivePower(70, 70);
			wait1Msec(250);
			setDrivePower(15, 15);

			mobileRRequestedValue = mobileOut;
			WaitieThing();

			Atondrive(-50, drivepower);

			mobileRRequestedValue = mobileMid;
			WaitieThing();

			Atondrive(-150, drivepower);

			//////////////////////////////////////////////// Score 4rd

			turnLeft(Nine);

			Atondrive(125, drivepower);

			turnLeft(Nine+120);

			setDrivePower(-40, -40);
			wait1Msec(1100);
			setDrivePower(0, 0);

			mobileRRequestedValue = mobileOut;
			WaitieThing();

			Atondrive(420, drivepower);

			mobileRRequestedValue = mobileMid;
			WaitieThing();

			turnRight(full+200);

			Atondrive(400, drivepower);

			mobileRRequestedValue = mobileOut;
			WaitieThing();

			Atondrive(-40, drivepower);

			Atondrive(-200, drivepower);
		/////////////////////////////////////////////// Score 5th

			turnLeft(full+180);

			mobileRRequestedValue = mobileOut;
			WaitieThing();

			Atondrive(510, drivepower);

			mobileRRequestedValue = mobileMid;
			WaitieThing();

			Atondrive(700, drivepower);

			mobileRRequestedValue = mobileOut;
			WaitieThing();

			Atondrive(10, drivepower);

			Atondrive(-10, 100);

			mobileRRequestedValue = mobileIn;
			WaitieThing();

			turnRight(Nine+200);
		////////////////////////////////////////////////
}

task SkillsTwo ()
{

		chainRRequestedValue = StraitUpChain; //
		liftRRequestedValue = 2600;           // PRESETS
		mobileRRequestedValue = mobileIn;     //

		mobileRRequestedValue = mobileOut;
		WaitieThing();

		liftRRequestedValue = 3000;

		Atondrive(380, 127);

		wait1Msec(200);

		liftRRequestedValue = 2910;
		chainRRequestedValue = OutPositionChain; //score pre-load

		wait1Msec(550);

		chainRRequestedValue = StraitUpChain;
		liftRRequestedValue = 2600;


	//////////////////////////////////Section 1 -score first mobile goal
		mobileRRequestedValue = mobileIn;
		WaitieThing();

		Atondrive(-250, drivepower);

		turnLeft(Nine+50);

		Atondrive(190, drivepower);

		turnLeft(Nine+100);

		Atondrive(100, drivepower);

		liftRRequestedValue = 2500;

		Atondrive(225, drivepower);

		setDrivePower(20,20);

		mobileRRequestedValue = mobileOut;
		WaitieThing();

		Atondrive(-50, drivepower);

		mobileRRequestedValue = mobileIn;
		WaitieThing();

	/////////////////////////////////////////Section 2 - Grab mobile goal 2
		Atondrive(-190, drivepower);

		turnLeft(Nine+50);

		Atondrive(210, drivepower);

		turnLeft(Nine+50);

		setDrivePower(-40, -40);
		wait1Msec(1200);
		setDrivePower(0, 0);

		mobileRRequestedValue = mobileOut;

		Atondrive(850, drivepower);

		mobileRRequestedValue = mobileMid;
		WaitieThing();

		Atondrive(600, drivepower);

		turnLeft(Nine);

		Atondrive(180, drivepower);

		turnRight(Nine+10);

		Atondrive(300, drivepower);

		setDrivePower(70, 70);
		wait1Msec(250);
		setDrivePower(15, 15);

		mobileRRequestedValue = mobileOut;
		WaitieThing();

		Atondrive(-50, drivepower);

		mobileRRequestedValue = mobileMid;
		WaitieThing();

		Atondrive(-150, drivepower);

		//////////////////////////////////////////////// Score 3rd

		turnLeft(Nine);

		Atondrive(210, drivepower);

		turnLeft(Nine+120);

		setDrivePower(-40, -40);
		wait1Msec(1100);
		setDrivePower(0, 0);

		mobileRRequestedValue = mobileOut;
		WaitieThing();

		Atondrive(420, drivepower);

		mobileRRequestedValue = mobileMid;
		WaitieThing();

		turnRight(full+100);

		Atondrive(400, drivepower);

		mobileRRequestedValue = mobileOut;
		WaitieThing();

		Atondrive(-40, drivepower);

		Atondrive(-200, drivepower);
	/////////////////////////////////////////////// Score 4th

		turnLeft(full+180);

		mobileRRequestedValue = mobileOut;
		WaitieThing();

		Atondrive(510, drivepower);

		mobileRRequestedValue = mobileMid;
		WaitieThing();

		Atondrive(530, drivepower);

		mobileRRequestedValue = mobileOut;
		WaitieThing();

		Atondrive(10, drivepower);

		Atondrive(-10, 100);

		mobileRRequestedValue = mobileIn;
		WaitieThing();

		turnRight(Nine+200);
	////////////////////////////////////////////////
}

task LeftRed ()
{
	chainRRequestedValue = StraitUpChain; //
	liftRRequestedValue = 2600;           // PRESETS
	mobileRRequestedValue = mobileIn;     //


}
task RightRed ()
{
	//--------------------------//

	chainRRequestedValue = 1240;
	liftRRequestedValue = 3000;

	Atondrive(750, 127);

	setDrivePower(-100, -100);
	wait1Msec(600);
	setDrivePower(0, 0);

	turnRight(300);

	setDrivePower(-100, -100);
	wait1Msec(100);
	setDrivePower(0, 0);


	chainRRequestedValue = 2870;

	wait1Msec(600);

	liftRRequestedValue = 2500;

	setDrivePower(-100, -100);
	wait1Msec(250);
	setDrivePower(0, 0);

	chainRRequestedValue = 1240;

	setMobilePower(127);
	wait1Msec(1000);
	setMobilePower(0);

	Atondrive(200, 100);

	setMobilePower(-127);
	wait1Msec(1000);
	setMobilePower(0);

	setDrivePower(-100, -100);
	wait1Msec(1100);
	setDrivePower(0, 0);

  //--------------------------//

	turnRight(full-500);

	Atondrive(500, 100);

	setMobilePower(127);
	wait1Msec(1000);
	setMobilePower(0);

	setDrivePower(-100, -100);
	wait1Msec(100);
	setDrivePower(0, 0);
}

task Defensive ()
{
	chainRRequestedValue = 1240;
	liftRRequestedValue = 2500;
	mobileRRequestedValue = mobileIn;


	wait1Msec(1500);
	mobileRRequestedValue = mobileOut;

	wait1Msec(1500);
	mobileRRequestedValue = mobileIn;

	wait1Msec(1500);
	mobileRRequestedValue = 2000;
}

task DoNothing ()
{
	chainRRequestedValue = 1240;
	liftRRequestedValue = 2500;
	mobileRRequestedValue = mobileIn;

	Atondrive(10000, 127);
}
//_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_//
