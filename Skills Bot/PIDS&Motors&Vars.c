//#region Variables
//-----------------Variables-----------------//
int drivepower;
int drivepowerPID = 127;

int rightTurn = -900;
int leftTurn = 900;

int liftStillSpeed;
int liftWaityError = 50;

int clawWaityError = 50;

//#endregion
//#region Motor Port Voids
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

void setDrivePowerLeft(int power)
{// Defining all of the motors for the -DRIVE-
	motor[LexDrive] = power;		//Define this motor as the left drive
	motor[LDriveOne] = power;		//Define this motor as the left 3 motor drive
	motor[LDriveTwo] = power;	//Define this motor as the right 3 motor drive.
}

void setDrivePowerRight(int power)
{// Defining all of the motors for the -DRIVE-
	motor[RexDrive] = power;	//Define this motor as the right drive
	motor[RDriveOne] = power;		//Define this motor as the left 3 motor drive
	motor[RDriveTwo] = power;	//Define this motor as the right 3 motor drive
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
//#endregion
//#region Lift PID
//----------------------LIFT PID----------------------//


static float  liftR_Kp = 0.2750; 	//Power Tuning Value
static float  liftRRequestedValue;
static float  liftR_Kd = 0.6;			// Requested Guess Value

float liftRD;
float liftRP;
float lastliftRError;
float liftRDF;

task liftRController()
{
	float  liftRSensorCurrentValue;
	float  liftRError;
	float  liftRDrive;

	while( true )
	{
		// Read the sensor value and scale
		liftRSensorCurrentValue = SensorValue[ liftPot ];

		// calculate error
		liftRError =  liftRRequestedValue - liftRSensorCurrentValue;

		// calculate drive
		liftRP = (liftR_Kp * liftRError);

		liftRD = liftRError- lastliftRError;
		liftRDF = (liftR_Kd * liftRD);

		liftRDrive = liftRP + liftRDF;

		// limit drive
		if( liftRDrive > 127 )
			liftRDrive = 127;
		if( liftRDrive < (-127) )
			liftRDrive = (-127);

		// send to motor

		setLiftPower(liftRDrive);

		lastliftRError = liftRError;

		// Don't hog cpu
		wait1Msec( 25 );
	}
}

void LiftTo (int Height, bool waity = false)
{
	liftRRequestedValue = Height;

	if (waity)
	{
	//  distance = abs(distance); //help
		while( SensorValue[ liftPot ] >= liftRRequestedValue + liftWaityError
		|| SensorValue[ liftPot ] <= liftRRequestedValue - liftWaityError){}
		wait1Msec(200);
	}
	wait1Msec(25);
}
//#endregion
//#region CLaw PID
//----------------------Claw PID----------------------//

static float  calw_Kp = 0.30; //Power Tuning Value
static float  calwRequestedValue;
static float  calw_Kd = 0.5; // Requested Guess Value

float calwD;						//Establishing variables
float calwP;
float lastcalwError;
float calwDF;
int waitMobliERerror = 100;
float  calwSensorCurrentValue;

task calwController()
{
	//float  calwSensorCurrentValue;
	float  calwError;
	float  calwDrive;

	while( true )
	{
		// Read the sensor value and scale
		calwSensorCurrentValue = SensorValue[ clawp ];
		// calculate error
		calwError =  calwRequestedValue - calwSensorCurrentValue;

		// calculate drive
		calwP = (calw_Kp * calwError);

		calwD = calwError- lastcalwError;
		calwDF = (calw_Kd * calwD);

		calwDrive = calwP + calwDF;

		// limit drive
		if( calwDrive > 127 )
			calwDrive = 127;
		if( calwDrive < (-127) )
			calwDrive = (-127);

		// send to motor

		motor[ Claw ] = calwDrive;

		lastcalwError = calwError;
		// Don't hog cpu
		wait1Msec( 25 );
	}
}

void setClawTo (int position, bool waity = false)
{
	calwRequestedValue = position;

	if (waity)
	{
	//  distance = abs(distance); //help
		while( SensorValue[ liftPot ] >= calwRequestedValue + clawWaityError
		|| SensorValue[ liftPot ] <= calwRequestedValue - clawWaityError){}
		wait1Msec(200);
	}
	wait1Msec(25);
}
//#endregion
