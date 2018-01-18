#include "PIDS.c"

//-----------------Variables-----------------//
int drivepower;
int drivepowerPID;

int liftStillSpeed;

//-------------Motor Void Set-Up--------------//
void setDrivePower(int left, int right)
{// Defining all of the motors for the -DRIVE-
	motor[LexDrive] = left;		//Define this motor as the left drive
	motor[RexDrive] = right;	//Define this motor as the right drive
	motor[LDriveOne] = left;		//Define this motor as the left 3 motor drive
	motor[LDriveTwo] = left;	//Define this motor as the right 3 motor drive.
	motor[RDriveOne] = right;		//Define this motor as the left 3 motor drive
	motor[RDriveTwo] = right;	//Define this motor as the right 3 motor drive
}

void setClawPower(int Cpower)
{
	motor[Claw] = Cpower;
}

void setLiftPower(int Lpower)
{
	motor[LOne] = Lpower;
	motor[LTwo] = Lpower;
	motor[LThree] = Lpower;
}


//_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_//
//--------------------Autonomous Voids-----------------------//
void AutoStrait(int distance, int power)
 // Creating a function to make sure the robot drives forward
{
	int direction = sgn(distance);
	distance = abs(distance);

 // telling it to do this while you are driving to the disired distance
	while(abs(SensorValue[rightEncoder])<distance)
	{
		 // Checking if the right drive is faster than the left drive
		if (abs(SensorValue[rightEncoder]) > abs(SensorValue[leftEncoder]))
		{
			setDrivePower(direction * power, direction * (power - 4));
		}
		// Checking if the left drive is faster than the right drive
		else if (abs(SensorValue[leftEncoder]) > abs(SensorValue[rightEncoder]))
		{
			setDrivePower(direction * (power - 2), direction * power);
		}
		else //if the values are the same, keeps motor powers equall
		{
			setDrivePower(direction * power, direction * power);
		}
	}
	motor[LexDrive] = 0;
	motor[RexDrive] = 0;
}

void Atondrive(int ticks, int power)
{ //auton function to move forward by its self
	  //Clear Encoders
  SensorValue[rightEncoder] = 0;
  SensorValue[leftEncoder] = 0;
		///forward
	AutoStrait(ticks*0.6, power);
	AutoStrait(ticks*0.8, power/2);
	AutoStrait(ticks, power/3);
//sudden stop to correct overshooting the value
	motor[LexDrive] = -20 * sgn(ticks);
	motor[RexDrive] = -20 * sgn(ticks);
	wait1Msec(100);
}

void turnRight(int ticks) // void to turn the robot right as much as you want
{
	//Clear Gyro
	SensorValue[clawP] = 0;

	while(abs(SensorValue[clawP]) < ticks) //while the sensor value is less than the amount of turing
  {
		setDrivePower(60, -60); //set drive power to turn robot right
	}
	setDrivePower(-10,10); //then stop
}

void turnLeft(int ticks) // void to turn the robot left as much as you want
{
	//Clear Gyro
	SensorValue[clawP] = 0;

	while(abs(SensorValue[clawP]) < ticks) //while the sensor value is less than the amount of turing
	{
		setDrivePower(-60, 60); //set drive power to turn robot right
	}
	setDrivePower(10,-10); //then stop}
}
