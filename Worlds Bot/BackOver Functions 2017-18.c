//#region motor set up
//-------------Motor Void Set-Up--------------//
void setDrivePower(int left, int right)
{// Defining all of the motors for the -DRIVE-
	motor[LDrive] = left;		//Define this motor as the left drive
	motor[RDrive] = right;	//Define this motor as the right drive
	motor[DriveL] = left;		//Define this motor as the left 3 motor drive
	motor[DriveR] = right;	//Define this motor as the right 3 motor drive
}

void setDrivePowerRight(int power)
{// Defining all of the motors for the -DRIVE-
	motor[RDrive] = power;	//Define this motor as the right drive
	motor[DriveR] = power;	//Define this motor as the right 3 motor drive
}

void setDrivePowerLeft(int power)
{// Defining all of the motors for the -DRIVE-
	motor[LDrive] = power;		//Define this motor as the left drive
	motor[DriveL] = power;		//Define this motor as the left 3 motor drive
}

void setLiftPower(int power)
{// Defining all of the motors for the -LIFT-
	motor[liftR] = power;
	motor[liftL] = power;
}

void setFourBarPower(int cpower)
{// Defining all of the motors for the -FourBar BAR-
	motor[FourBar] = cpower;
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
//#endregion
//#region Lift PID
//----------------------LIFT PID----------------------//

static float  liftR_Kp = 0.2; 	//Power Tuning Value
static float  liftRRequestedValue;
static float  liftR_Kd = 1;			// Requested Guess Value

float liftRD;
float liftRP;
float lastliftRError;
int waitLiftRerror = 80;
float liftRDF;
float liftRSensorCurrentValue;

task liftRController()
{
	float  liftRSensorCurrentValue;
	float  liftRError;
	float  liftRDrive;

	while( true )
	{
		// Read the sensor value and scale
		liftRSensorCurrentValue = SensorValue[ liftP ];

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

		motor[ liftL ] = liftRDrive;
		motor[ liftR ] = liftRDrive;

		lastliftRError = liftRError;

		// Don't hog cpu
		wait1Msec( 25 );
	}
}
//#endregion
//#region Mobile PID
//----------------------Mobile Bar PID----------------------//

static float  mobileR_Kp = 0.30; //Power Tuning Value
static float  mobileRRequestedValue;
static float  mobileR_Kd = 0.5; // Requested Guess Value

float mobileRD;						//Establishing variables
float mobileRP;
float lastmobileRError;
float mobileRDF;
int waitMobliERerror = 100;
float  mobileRSensorCurrentValue;

task mobileRController()
{
	//float  mobileRSensorCurrentValue;
	float  mobileRError;
	float  mobileRDrive;

	while( true )
	{
		// Read the sensor value and scale
		mobileRSensorCurrentValue = SensorValue[ mobileP ];
		// calculate error
		mobileRError =  mobileRRequestedValue - mobileRSensorCurrentValue;

		// calculate drive
		mobileRP = (mobileR_Kp * mobileRError);

		mobileRD = mobileRError- lastmobileRError;
		mobileRDF = (mobileR_Kd * mobileRD);

		mobileRDrive = mobileRP + mobileRDF;

		// limit drive
		if( mobileRDrive > 127 )
			mobileRDrive = 127;
		if( mobileRDrive < (-127) )
			mobileRDrive = (-127);

		// send to motor

		motor[ MobileL ] = mobileRDrive;
		motor[ MobileR ] = mobileRDrive;

		lastmobileRError = mobileRError;
		// Don't hog cpu
		wait1Msec( 25 );
	}
}
//#endregion
//#region WaityThing for mobilegoal and lift
void WaitieThing()
{
	while(mobileRSensorCurrentValue >= mobileRRequestedValue + waitMobliERerror
		|| mobileRSensorCurrentValue <= mobileRRequestedValue - waitMobliERerror)
		{}
}
/*
void WaitieThingLift()
{
	while(liftRSensorCurrentValue >= liftRRequestedValue + waitLiftRerror
		|| liftRSensorCurrentValue <= liftRRequestedValue - waitMobliERerror)
		{}
}
*/
//#endregion
