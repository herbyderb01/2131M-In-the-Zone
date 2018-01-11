//-------------Motor Void Set-Up--------------//

void setDrivePower(int left, int right){   // Defining all of the motors for the -DRIVE-
motor[LDrive] = left;					//Define this motor as the left drive
motor[RDrive] = right;					//Define this motor as the right drive
}

void setLiftPower(int power){   // Defining all of the motors for the -LIFT-
motor[liftR] = power;
motor[liftL] = power;
}

void setChainPower(int cpower){		// Defining all of the motors for the -CHAIN BAR-
motor[chainR] = cpower;
motor[chainL] = cpower;
}

void setIntakePower(int Ipower){		// Defining all of the motors for the -INTAKE-
motor[INtake] = Ipower;
}

void setMobilePower(int Mpower){		// Defining all of the motors for the -MOBILE GOAL INTAKE-
motor[MobileL] = Mpower;
motor[MobileR] = Mpower;
}


//////////////////////////////////////////////////////////////////////////////////////////
void AutoStrait(int distance, int power) // Creating a function to make sure the robot drives forward
{
	while(SensorValue[rightEncoder]<distance) // telling it to do this while you are driving to the disired distance
	{
	if (abs(SensorValue[rightEncoder]) > (abs(SensorValue[leftEncoder]))) // Checking if the right drive is faster than the left drive
		{
				motor[LDrive] = power;
				motor[RDrive] = power-2; // if it is, decrease the right motor power by -2 power
		}
		if (abs(SensorValue[leftEncoder]) > (abs(SensorValue[rightEncoder]))) // Checking if the left drive is faster than the right drive
		{
				motor[LDrive] = power-2;// if it is, decrease the left motor power by -2 power
				motor[RDrive] = power;
		}
		if (abs(SensorValue[rightEncoder]) == (abs(SensorValue[leftEncoder]))) //if the values are the same, keeps motor powers equall
		{
				motor[LDrive] = power; //setting them equal to original power value
				motor[RDrive] = power;
		}
	}


		motor[LDrive] = 0; // stops motors when finished with function
		motor[RDrive] = 0;

}

int Nine = 750;
int full = 1750;
float  liftRSensorCurrentValue;


void Atondrive(int ticks, int power) //auton function to move forward by its self
{
	  //Clear Encoders
  SensorValue[rightEncoder] = 0;
  SensorValue[leftEncoder] = 0;

  //int LeftEncoderPos = abs(SensorValue[leftEncoder]); // this is test code we are currently not using

	while(abs(SensorValue[rightEncoder]) < ticks)
	{
		///forward

		  if(abs(SensorValue[rightEncoder]) < ticks*.6) // checking to see if the abs(of the encoder value) is less than 60% of the ticks
		  {
				AutoStrait(ticks, power); //set motors to full power
			}
			if(abs(SensorValue[rightEncoder]) < ticks*.8)// checking to see if the abs(of the encoder value) is less than 80% of the ticks
		  {
				AutoStrait(ticks, power/2); // set motors to half power
			}
			if(abs(SensorValue[rightEncoder]) < ticks)// checking to see if the abs(of the encoder value) is less than 100% of the ticks
		  {
				AutoStrait(ticks, power/4); //set motors to 25% power
			}
				motor[LDrive] = -5; //sudden stop to correct overshooting the value
				motor[RDrive] = -5;
	}

}

void AtondriveB (int ticks, int power) //auton function to move forward by its self
{
	  //Clear Encoders
  SensorValue[rightEncoder] = 0;
  SensorValue[leftEncoder] = 0;

  //int LeftEncoderPos = abs(SensorValue[leftEncoder]); // this is test code we are currently not using

	while(abs(SensorValue[rightEncoder]) > ticks)
	{
		///forward

		  if(SensorValue[rightEncoder] > ticks*.6) // checking to see if the abs(of the encoder value) is less than 60% of the ticks
		  {
				motor[LDrive] = -power; //setting them equal to original power value
				motor[RDrive] = -power;
			}
			if(SensorValue[rightEncoder] > ticks*.8)// checking to see if the abs(of the encoder value) is less than 80% of the ticks
		  {
				motor[LDrive] = -power; //setting them equal to original power value
				motor[RDrive] = -power;
			}
			if(SensorValue[rightEncoder] > ticks)// checking to see if the abs(of the encoder value) is less than 100% of the ticks
		  {
				motor[LDrive] = -power; //setting them equal to original power value
				motor[RDrive] = -power;
			}
				motor[LDrive] = -5; //sudden stop to correct overshooting the value
				motor[RDrive] = -5;
	}

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
	SensorValue[gyro] = 0;

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





//////////////////////////////////////////////////////////////////////////////////////////
task StartAton() //aton function to get robot ready to compete
{
	//--------------------------//

	liftRRequestedValue = 2700;

	chainRRequestedValue = 3360;


	setMobilePower(127);
	wait1Msec(1000);
	setMobilePower(0);

	chainRRequestedValue = 2950;
	setIntakePower(50);
	wait1Msec(1000);
	liftRRequestedValue = 3100;

	//seconed stage

	wait1Msec(600);

	setIntakePower(50);

	chainRRequestedValue = 1250;
	liftRRequestedValue = 2500;
  //--------------------------//
}

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
	Atondrive(5, 127);

	chainRRequestedValue = 2870;
	liftRRequestedValue = 3000;

	Atondrive(160, 127);

	wait1Msec(600);

	liftRRequestedValue = 2500;

	setDrivePower(-100, -100);
	wait1Msec(250);
	setDrivePower(0, 0);

	chainRRequestedValue = 1240;

	setMobilePower(127);
	wait1Msec(1000);
	setMobilePower(0);

	Atondrive(130, 100);

//////////////////////////////////Section 1 -score first mobile goal
	setMobilePower(-127);
	wait1Msec(1000);
	setMobilePower(0);

	setDrivePower(-100, -100);
	wait1Msec(1050);
	setDrivePower(0, 0);

	turnLeft(Nine+10);
	Atondrive(80, 100);

	turnLeft(Nine+100);
	Atondrive(100, 100);

	liftRRequestedValue = 2500;

	Atondrive(210, 100);

	setMobilePower(127);
	wait1Msec(1100);
	setMobilePower(0);

	Atondrive(10, 100);

	setDrivePower(-100, -100);
	wait1Msec(200);
	setDrivePower(0, 0);

	setMobilePower(-127);
	wait1Msec(1000);
	setMobilePower(0);

/////////////////////////////////////////Section 2 - Grab mobile goal 2
	setDrivePower(-100, -100);
	wait1Msec(500);
	setDrivePower(0, 0);

	turnLeft(Nine-20);

	Atondrive(560, 100);

	setDrivePower(-100, -100);
	wait1Msec(180);
	setDrivePower(0, 0);

	turnLeft(Nine+50);

	setMobilePower(127);
	wait1Msec(1000);
	setMobilePower(0);

	Atondrive(260, 100);

	setMobilePower(-127);
	wait1Msec(1000);
	setMobilePower(0);

	setDrivePower(-100, -100);
	wait1Msec(1500);
	setDrivePower(0, 0);

	turnRight(Nine+400);

	Atondrive(60, 100);


	setMobilePower(127);
	wait1Msec(1000);
	setMobilePower(0);

	setDrivePower(-100, -100);
	wait1Msec(250);
	setDrivePower(0, 0);

	setMobilePower(-127);
	wait1Msec(1000);
	setMobilePower(0);
////////////////////////////////////////////Section 3 - Score goal 3
	turnLeft(full+100);

	setMobilePower(127);
	wait1Msec(1000);
	setMobilePower(0);

	Atondrive(800, 100);

	setMobilePower(-127);
	wait1Msec(1000);
	setMobilePower(0);

	Atondrive(200, 100);

	turnLeft(Nine);

	Atondrive(200, 100);

	turnRight(Nine);

	Atondrive(300, 100);

	setMobilePower(127);
	wait1Msec(1100);
	setMobilePower(0);

	Atondrive(10, 100);

	setDrivePower(-100, -100);
	wait1Msec(200);
	setDrivePower(0, 0);

	setMobilePower(-127);
	wait1Msec(1000);
	setMobilePower(0);

	setDrivePower(-100, -100);
	wait1Msec(620);
	setDrivePower(0, 0);

	////////////////////////////////////////////////

	turnLeft(Nine);

	Atondrive(125, 100);

	turnLeft(Nine+200);

	setMobilePower(127);
	wait1Msec(1100);
	setMobilePower(0);

	Atondrive(280, 100);

	setMobilePower(-127);
	wait1Msec(1000);
	setMobilePower(0);

	turnRight(full);

	Atondrive(350, 100);

	setMobilePower(127);
	wait1Msec(1100);
	setMobilePower(0);

	Atondrive(10, 100);

	setDrivePower(-100, -100);
	wait1Msec(200);
	setDrivePower(0, 0);

	setMobilePower(-127);
	wait1Msec(1000);
	setMobilePower(0);

	setDrivePower(-100, -100);
	wait1Msec(500);
	setDrivePower(0, 0);
///////////////////////////////////////////////

	turnLeft(full+200);

	setMobilePower(127);
	wait1Msec(1100);
	setMobilePower(0);

	Atondrive(780, 100);

	setMobilePower(-127);
	wait1Msec(1000);
	setMobilePower(0);

	Atondrive(250, 100);

	setMobilePower(127);
	wait1Msec(1100);
	setMobilePower(0);

	Atondrive(10, 100);

	setDrivePower(-100, -100);
	wait1Msec(200);
	setDrivePower(0, 0);

	setMobilePower(-127);
	wait1Msec(1000);
	setMobilePower(0);

	setDrivePower(-100, -100);
	wait1Msec(500);
	setDrivePower(0, 0);
////////////////////////////////////////////////



}

task SkillsTwo ()
{

}

task LeftRed ()
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

	turnLeft(full-80);

	Atondrive(130, 100);

	setMobilePower(127);
	wait1Msec(1000);
	setMobilePower(0);

	setDrivePower(-100, -100);
	wait1Msec(100);
	setDrivePower(0, 0);

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

	wait1Msec(500);


	setMobilePower(127);
	wait1Msec(1000);
	setMobilePower(0);


	setDrivePower(-100, -100);
	wait1Msec(10000);
	setDrivePower(0, 0);

}

task DoNothing ()
{
	liftRRequestedValue = 3000;
}
