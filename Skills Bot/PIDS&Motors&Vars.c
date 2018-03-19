//#region Variables
//-----------------Variables-----------------//
int drivepower;
int drivepowerPID = 127;

int rightTurn = -900;
int leftTurn = 900;

int MobileStillSpeed;
//int liftWaityError = 150;

int mobileWaityError = 50;

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

void setMobilePower(int power)
{
	motor[LMobile] = power;
	motor[RMobile] = power;
}
//#endregion
/*
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

		setLiftPower(-liftRDrive);

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
*/
//#region mobile PID
//----------------------Mobile PID----------------------//

static float  mobile_Kp = 0.30; //Power Tuning Value
static float  mobileRequestedValue;
static float  mobile_Kd = 0.5; // Requested Guess Value

float mobileD;						//Establishing variables
float mobileP;
float lastmobileError;
float mobileDF;
int waitMobliERerror = 100;
float  mobileSensorCurrentValue;

task mobileController()
{
	//float  calwSensorCurrentValue;
	float  mobileError;
	float  mobileDrive;

	while( true )
	{
		// Read the sensor value and scale
		mobileSensorCurrentValue = SensorValue[ MobileP ];
		// calculate error
		mobileError =  mobileRequestedValue - mobileSensorCurrentValue;

		// calculate drive
		mobileP = (mobile_Kp * mobileError);

		mobileD = mobileError- lastmobileError;
		mobileDF = (mobile_Kd * mobileD);

		mobileDrive = mobileP + mobileDF;

		// limit drive
		if( mobileDrive > 127 )
			mobileDrive = 127;
		if( mobileDrive < (-127) )
			mobileDrive = (-127);

		// send to motor

		motor[ LMobile ] = mobileDrive;
		motor[ RMobile ] = mobileDrive;

		lastmobileError = mobileError;
		// Don't hog cpu
		wait1Msec( 25 );
	}
}

void setMobileTo (int position, bool waity = false)
{
	mobileRequestedValue = position;

	if (waity)
	{
	//  distance = abs(distance); //help
		while( SensorValue[ MobileP ] >= mobileRequestedValue + mobileWaityError
		|| SensorValue[ MobileP ] <= mobileRequestedValue - mobileWaityError){}
		wait1Msec(200);
	}
	wait1Msec(25);
}
//#endregion
